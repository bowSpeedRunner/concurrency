#include <iostream>
#include <future>
#include <thread>

int multiply10(int);

int main() {
  std::packaged_task<int(int)> task(multiply10);
  auto ret = task.get_future();
  std::thread t(std::move(task), 10);
  auto res = std::async(multiply10, 10);
  auto val1 = ret.get();
  auto val2 = res.get();
  std::cout << "value by packaged_task = " << val1 << std::endl;
  std::cout << "value by asyns = " << val2 << std::endl;
  t.join();
  std::cin.get();
}

int multiply10(int number) {
  auto res = number * 10;
  std::cout << "finished!" << std::endl;
  return res;
}