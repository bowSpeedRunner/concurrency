#include "threadSafe_queue.cpp"
#include <iostream>
#include <thread>
#include <vector>
void push_thread(threadSafe_queue<int>&, int);
int main() {
  threadSafe_queue<int> q;
  std::vector<std::thread> threads;
  for (int i = 0; i < 40; ++i) {
    threads.emplace_back(push_thread, std::ref(q), i);
  }
  // for (int j = 100; j < 120; ++j) {
  //   threads.emplace_back(push_thread, std::ref(q), j);
  // }
  for (auto& t : threads) {
    t.join();
  }
  while (!q.empty()) {
    int top;
    q.wait_and_pop(top);
    std::cout << top << std::endl;
  }
  std::cin.get();
}
void push_thread(threadSafe_queue<int>& q, int i) {
  q.push(i);
}