#include <memory>
#include <mutex>

template <typename T>
class threadSafe_list {
 private:
  struct node {
    std::mutex m;
    std::shared_ptr<T> data;
    std::unique_ptr<node> next;
    node() : next() {
    }
    node(const T& value) : data(std::make_shared<T>(value)) {
    }
  };
  node head;

 public:
  template <typename Function>
  void for_each(Function f) {
    node* current = &head;
    std::unique_lock<std::mutex> lk(head.m);
    while (node* const next = current->next.get()) {
      std::unique_lock<std::mutex> next_lk(next->m);
      lk.unlock();
      f(*next->data);
      current = next;
      lk = std::move(next_lk);
    }
  }

  template <typename Predicate>
  std::shared_ptr<T> find_first_if(Predicate p) {
    node* current = &head;
    std::unique_lock<std::mutex> lk(head.m);
    while (node* const next = current->next.get()) {
      std::unique_lock<std::mutex> next_lk(next->m);
      lk.unlock();
      if (p(*next->data)) {
        return next->data;
      }
      current = next;
      lk = std::move(next_lk);
    }
    return std::shared_ptr<T>();
  }

  template <typename Predicate>
  void remove_if(Predicate p) {
    node* current = &head;
    std::unique_lock<std::mutex> lk(head.m);
    while (node* const next = current->next.get()) {
      std::unique_lock<std::mutex> next_lk(next->m);
      if (p(*next->data)) {
        std::unique_ptr<node> old_next = std::move(current->next);
        current->next = std::move(next->next);
        next_lk.unlock();
      } else {
        lk.unlock();
        current = next;
        lk = std::move(next_lk);
      }
    }
  }

  threadSafe_list() {
  }
  ~threadSafe_list() {
    remove_if([](const node&) { return true; });
  }
  threadSafe_list(const threadSafe_list&) = delete;
  threadSafe_list& operator=(const threadSafe_list&) = delete;

  void push_front(const T& value) {
    std::unique_ptr<node> new_node = std::make_unique<node>(value);
    std::lock_guard<std::mutex> lk(head.m);
    new_node->next = std::move(head.next);
    head.next = std::move(new_node);
  }
};