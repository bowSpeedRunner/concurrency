#include <memory>
#include <atomic>

template <typename T>
class lock_free_stk_with_Sptr {
 private:
  struct node {
    std::shared_ptr<T> data;
    std::shared_ptr<node> next;
    node(const T& data_) : data(std::make_shared<T>(data_)) {
    }
  };
  std::shared_ptr<node> head;

 public:
  void push(const T& data) {
    std::shared_ptr<node> const new_node = std::make_shared<node>(data);
    new_node->next = std::atomic_load(&head);
    while (!std::atomic_compare_exchange_weak(&head, &new_node->next, new_node))
      ;
  }

  std::shared_ptr<T> pop() {
    std::shared_ptr<node> old_head = std::atomic_load(&head);
    while (old_head && !std::atomic_compare_exchange_weak(&head, &old_head, std::atomic_load(&old_head->next)))
      ;
    if (old_head) {
      std::atomic_store(&old_head->next, std::shared_ptr<node>());
      return old_head->data;
    }
    return std::shared_ptr<T>();
  }

  ~lock_free_stk_with_Sptr() {
    while (pop())
      ;
  }

  bool empty() const {
    return std::atomic_load(&head) == nullptr;
  }
};