#include "thSafeQ.hpp"
#include <iostream>
#include <vector>
#include <thread>

const std::vector<int> nums = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

std::mutex m;

void push(threadSafe_queue<int>& q, const std::vector<int>& nums) {
  for (const auto& num : nums) {
    q.push(num);
  }
}

void pop(threadSafe_queue<int>& q, std::vector<int>& nums) {
  while (!q.empty()) {
    int value;
    q.wait_and_pop(value);
    {
      std::lock_guard<std::mutex> lock(m);
      nums.emplace_back(value);
    }
  }
}

int main() {
  threadSafe_queue<int> q;
  std::vector<int> output;
  std::thread push1(push, std::ref(q), std::ref(nums));
  std::thread push2(push, std::ref(q), std::ref(nums));
  std::thread pop1(pop, std::ref(q), std::ref(output));
  std::thread pop2(pop, std::ref(q), std::ref(output));
  push1.join();
  push2.join();
  pop1.join();
  pop2.join();
  for (const auto& num : output) {
    std::cout << num << " ";
    if (num == 9) {
      std::cout << std::endl;
    }
  }
  std::cin.get();
}