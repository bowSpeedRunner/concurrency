#ifndef _HIERARCHICAL_MUTEX_H_
#define _HIERARCHICAL_MUTEX_H_
#include <mutex>
#include <iostream>
#include <climits>

class hierarchical_mutex {
 public:
  explicit hierarchical_mutex(uint64_t);
  ~hierarchical_mutex() = default;
  void lock();
  void unlock();
  bool try_lock();

 private:
  mutable std::mutex internal_mutex;
  uint64_t hierarchy_value;
  uint64_t previous_hierarchy_value;
  static thread_local uint64_t this_thread_hierarchy_value;
  void check_for_hierarchy_violation();
  void update_hierarchy_value();
};

thread_local uint64_t hierarchical_mutex::this_thread_hierarchy_value(ULLONG_MAX);

void hierarchical_mutex::check_for_hierarchy_violation() {
  if (this_thread_hierarchy_value <= hierarchy_value) {
    std::cout << "value not expect!" << std::endl;
    throw std::logic_error("mutex hierarchy violated!");
  }
}

void hierarchical_mutex::update_hierarchy_value() {
  previous_hierarchy_value = this_thread_hierarchy_value;
  this_thread_hierarchy_value = hierarchy_value;
}

hierarchical_mutex::hierarchical_mutex(uint64_t value) : hierarchy_value(value), previous_hierarchy_value(0) {
}

void hierarchical_mutex::lock() {
  check_for_hierarchy_violation();
  internal_mutex.lock();
  update_hierarchy_value();
}

void hierarchical_mutex::unlock() {
  if (this_thread_hierarchy_value != hierarchy_value) {
    std::cout << "value haven't change!" << std::endl;
    throw std::logic_error("mutex hierarchy violated!");
  }
  this_thread_hierarchy_value = previous_hierarchy_value;
  internal_mutex.unlock();
}

bool hierarchical_mutex::try_lock() {
  check_for_hierarchy_violation();
  if (!internal_mutex.try_lock()) {
    return false;
  }
  update_hierarchy_value();
  return true;
}

#endif  // !_HIERARCHICAL_MUTEX_H_