#include <iostream>
#include <future>
#include <thread>

using namespace std::literals;
void send(std::promise<int>&);
void receive(std::future<int>&);

int main() {
  std::promise<int> p;
  auto fut = p.get_future();
  std::thread t1(send, std::ref(p));
  std::thread t2(receive, std::ref(fut));
  t1.join();
  t2.join();
  std::cin.get();
}

void send(std::promise<int>& p) {
  std::cout << "activate, sleep for 2s" << std::endl;
  std::this_thread::sleep_for(2s);
  std::cout << "start send value" << std::endl;
  p.set_value(5);
}

void receive(std::future<int>& fut) {
  std::cout << "activate, sleep for 5s" << std::endl;
  std::this_thread::sleep_for(5s);
  auto val = fut.get();
  std::cout << "received number, number is " << val << std::endl;
}