#include <exception>
#include <memory>
#include <mutex>
#include <stack>
struct empty_stack : std::exception {
  const char* what() const throw() {
    return "stk is empty";
  }
};

template <typename T>
class thSafeStk {
 private:
  std::stack<T> data;
  mutable std::mutex m;

 public:
  thSafeStk() {
  }

  thSafeStk(const thSafeStk& other) {
    std::lock_guard<std::mutex> lock(other.m);
    data = other.data;
  }

  thSafeStk& operator=(const thSafeStk&) = delete;

  void push(T new_value) {
    std::lock_guard<std::mutex> lock(m);
    data.push(std::move(new_value));
  }

  std::shared_ptr<T> pop() {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) {
      throw empty_stack();
    }
    const std::shared_ptr<T> res = std::make_shared<T>(std::move(data.top()));
    data.pop();
    return res;
  }

  void pop(T& value) {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) {
      throw empty_stack();
    }
    value = std::move(data.top());
    data.pop();
  }

  bool empty() const {
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
  }
};
