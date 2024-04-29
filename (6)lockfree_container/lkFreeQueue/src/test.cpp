#include "lock_free_queue.hpp"
#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <queue>

const std::vector<int> input = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
std::vector<int> output;

void TPush(lock_free_queue<int>& q) {
  for (const auto& x : input) {
    q.push(x);
  }
}

void TPop(lock_free_queue<int>& q) {
  while (!q.empty()) {
    auto p = q.pop();
    if (!p) {
      continue;
    }
    output.emplace_back(*p);
  }
}

// std::vector<int> TPop(std::queue<int>& q) {
//   std::vector<int> local_output;
//   while (true) {
//     auto p = q.front();
//     q.pop();
//     if (!p) {
//       break;
//     }
//     local_output.emplace_back(p);
//   }
//   return local_output;
// }

int main() {
  lock_free_queue<int> q;
  std::thread push1(TPush, std::ref(q));
  std::thread push2(TPush, std::ref(q));
  std::thread pop1(TPop, std::ref(q));
  std::thread pop2(TPop, std::ref(q));
  push1.join();
  push2.join();
  pop1.join();
  pop2.join();
  for (const auto& x : output) {
    std::cout << x << " ";
  }
  std::cin.get();

  // std::queue<int> q;
  // std::thread push1(TPush, std::ref(q));
  // std::thread push2(TPush, std::ref(q));

  // std::packaged_task<std::vector<int>(std::queue<int>&)> task1(TPop);
  // std::packaged_task<std::vector<int>(std::queue<int>&)> task2(TPop);
  // std::future<std::vector<int>> pop1_future = task1.get_future();
  // std::future<std::vector<int>> pop2_future = task2.get_future();

  // std::thread pop1(std::move(task1), std::ref(q));
  // std::thread pop2(std::move(task2), std::ref(q));

  // push1.join();
  // push2.join();
  // std::vector<int> output1 = pop1_future.get();
  // std::vector<int> output2 = pop2_future.get();

  // pop1.join();
  // pop2.join();

  // std::vector<int> output;
  // output.reserve(output1.size() + output2.size());
  // output.insert(output.end(), output1.begin(), output1.end());
  // output.insert(output.end(), output2.begin(), output2.end());

  // for (const auto& x : output) {
  //   std::cout << x << " ";
  // }
  // std::cin.get();
}