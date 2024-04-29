#include "threadSafe_queue.h"
template <typename T>
threadSafe_queue<T>::threadSafe_queue(const threadSafe_queue& other) {
  std::lock_guard<std::mutex> lk(other.mtx);
  data_queue = other.data_queue;
}

template <typename T>
void threadSafe_queue<T>::push(T new_value) {
  std::lock_guard<std::mutex> lk(mtx);
  data_queue.push(new_value);
  data_cond.notify_one();
}

template <typename T>
void threadSafe_queue<T>::wait_and_pop(T& value) {
  std::unique_lock<std::mutex> lk(mtx);
  data_cond.wait(lk, [this] { return !data_queue.empty(); });
  value = data_queue.front();
  data_queue.pop();
}

template <typename T>
std::shared_ptr<T> threadSafe_queue<T>::wait_and_pop() {
  std::unique_lock<std::mutex> lk(mtx);
  data_cond.wait(lk, [this] { return !data_queue.empty(); });
  std::shared_ptr<T> SPtr(std::make_shared<T>(data_queue.front()));
  data_queue.pop();
  return SPtr;
}

template <typename T>
bool threadSafe_queue<T>::try_pop(T& value) {
  std::lock_guard<std::mutex> lk(mtx);
  if (data_queue.empty()) {
    return false;
  }
  value = data_queue.front();
  data_queue.pop();
  return true;
}

template <typename T>
std::shared_ptr<T> threadSafe_queue<T>::try_pop() {
  std::lock_guard<std::mutex> lk(mtx);
  if (data_queue.empty()) {
    return std::make_shared<T>();
  }
  std::shared_ptr<T> SPtr(std::make_shared<T>(data_queue.front()));
  data_queue.pop();
  return SPtr;
}

template <typename T>
bool threadSafe_queue<T>::empty() const {
  std::lock_guard<std::mutex> lk(mtx);
  return data_queue.empty();
}