#include <memory>
#include <mutex>
#include <condition_variable>

template <typename T>
class threadSafe_queue {
 private:
  struct node {
    std::shared_ptr<T> data;
    std::unique_ptr<node> next;
  };
  std::mutex head_mutex;
  std::mutex tail_mutex;
  std::unique_ptr<node> head;
  node* tail;
  std::condition_variable cv;

  node* get_tail() {
    std::lock_guard<std::mutex> tail_lock(tail_mutex);
    return tail;
  }

  std::unique_ptr<node> pop_head() {
    std::unique_ptr<node> old_head = std::move(head);
    head = std::move(old_head->next);
    return old_head;
  }

  std::unique_lock<std::mutex> wait_for_data() {
    std::unique_lock<std::mutex> head_lock(head_mutex);
    cv.wait(head_lock, [&] { return head.get() != get_tail(); });
    return head_lock;
  }

  std::unique_ptr<node> wait_pop_head() {  // real pop
    std::unique_lock<std::mutex> head_lock(wait_for_data());
    return pop_head();
  }

  std::unique_ptr<node> wait_pop_head(T& value) {  // pop head_ptr and value
    std::unique_lock<std::mutex> head_lock(wait_for_data());
    value = std::move(*head->data);
    return pop_head();
  }

  std::unique_ptr<node> try_pop_head() {
    std::lock_guard<std::mutex> head_lock(head_mutex);
    if (head.get() == get_tail()) {
      return std::unique_ptr<node>();
    }
    return pop_head();
  }

  std::unique_ptr<node> try_pop_head(T& value) {
    std::lock_guard<std::mutex> head_lock(head_mutex);
    if (head.get() == get_tail()) {
      return std::unique_ptr<node>();
    }
    value = std::move(*head->data);
    return pop_head();
  }

 public:
  threadSafe_queue() : head(new node), tail(head.get()) {
  }
  threadSafe_queue(const threadSafe_queue&) = delete;
  threadSafe_queue& operator=(const threadSafe_queue&) = delete;
  std::shared_ptr<T> try_pop() {
    std::unique_ptr<node> old_head = try_pop_head();
    return old_head ? old_head->data : std::shared_ptr<T>();
  }

  bool try_pop(T& value) {
    const std::unique_ptr<node> old_head = try_pop_head(value);
    return old_head != nullptr;
  }

  std::shared_ptr<T> wait_and_pop() {
    const std::unique_ptr<node> old_head = wait_pop_head();
    return old_head->data;
  }

  void wait_and_pop(T& value) {
    const std::unique_ptr<node> old_head = wait_pop_head(value);
  }

  void push(T new_value) {
    std::shared_ptr<T> new_data = std::make_shared<T>(std::move(new_value));
    std::unique_ptr<node> p = std::make_unique<node>();
    {
      std::lock_guard<std::mutex> tail_lock(tail_mutex);
      tail->data = new_data;
      node* new_tail = p.get();
      tail->next = std::move(p);
      tail = new_tail;
    }
    cv.notify_one();
  }

  bool empty() {
    std::lock_guard<std::mutex> head_lock(head_mutex);
    return (head.get() == get_tail());
  }
};
