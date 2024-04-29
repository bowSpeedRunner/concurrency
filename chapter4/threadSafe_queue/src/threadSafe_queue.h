#ifndef _threadSafe_queue_h
#define _threadSafe_queue_h
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
template <typename T>
class threadSafe_queue {
 public:
  threadSafe_queue() = default;
  ~threadSafe_queue() = default;
  threadSafe_queue& operator=(const threadSafe_queue&) = delete;
  threadSafe_queue(const threadSafe_queue&);
  void push(T);
  void wait_and_pop(T&);
  std::shared_ptr<T> wait_and_pop();
  bool try_pop(T&);
  std::shared_ptr<T> try_pop();
  bool empty() const;

 private:
  mutable std::mutex mtx;
  std::queue<T> data_queue;
  std::condition_variable data_cond;
};

#endif  // !_threadSafe_queue_h