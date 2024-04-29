#include <iostream>
#include <thread>

void print() {
  std::cout << "hello world with thread!" << std::endl;
  std::cout << "thread id is : " << std::this_thread::get_id() << std::endl;
}
int main() {
  std::thread t1(print);
  std::thread t2(print);
  t1.join();
  t2.join();
  std::cin.get();
}