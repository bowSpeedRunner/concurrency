#include <memory>
#include "someFuncImpl.h"

template <typename T>
class lock_free_stack_with_hp {
 private:
  struct node {
    std::shared_ptr<T> data;
    node* next;
    node(const T& data_) : data(std::make_shared<T>(data_)) {
    }
  };
  std::atomic<node*> head;

 public:
  void push(const T& data) {
    node* new_node = new node(data);
    new_node->next = head.load();
    while (!head.compare_exchange_weak(new_node->next, new_node))
      ;
  }

  std::shared_ptr<T> pop() {
    std::atomic<void*>& hp = get_hazard_pointer_for_current_thread();
    node* old_head = head.load();
    do {
      node* temp;
      do {
        temp = old_head;
        hp.store(old_head);
        old_head = head.load();
      } while (old_head != temp);
    } while (old_head && !head.compare_exchange_strong(old_head, old_head->next));
    hp.store(nullptr);
    std::shared_ptr<T> res;
    if (old_head) {
      res.swap(old_head->data);
      if (outstanding_hazrd_pointers_for(old_head)) {
        reclaim_later(old_head);
      } else {
        delete old_head;
      }
      delete_nodes_with_no_hazards();
    }
    return res;
  }
};
