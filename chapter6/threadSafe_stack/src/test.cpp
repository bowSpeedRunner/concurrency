#include "thSafeStk.hpp"
#include <iostream>
#include <vector>
#include <thread>

std::mutex m;
const std::vector<int> nums = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

void thPush(thSafeStk<int>& stk) {
  for (const auto& num : nums) {
    stk.push(num);
  }
}

void thPop(thSafeStk<int>& stk, std::vector<int>& ouput) {
  while (!stk.empty()) {
    auto p = stk.pop();
    {
      std::lock_guard<std::mutex> lock(m);
      ouput.emplace_back(*p);
    }
  }
}

int main() {
  thSafeStk<int> stk;
  std::vector<int> res;
  std::thread push1(thPush, std::ref(stk));
  std::thread push2(thPush, std::ref(stk));
  std::thread pop1(thPop, std::ref(stk), std::ref(res));
  std::thread pop2(thPop, std::ref(stk), std::ref(res));
  push1.join();
  push2.join();
  pop1.join();
  pop2.join();
  int cnt = 0;
  for (const auto& num : res) {
    std::cout << num << " ";
    ++cnt;
    if (cnt == 10) {
      std::cout << std::endl;
    }
  }
  std::cin.get();
}