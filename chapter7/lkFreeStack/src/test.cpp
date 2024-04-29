#include "lock_free_stack.hpp"
#include <iostream>
#include <vector>
#include <thread>

using namespace std::literals;

const std::vector<int> input = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
std::vector<int> output;
static int number = 0;

void TPush(lock_free_stack<int>& stk) {
  for (const auto& x : input) {
    stk.push(x);
  }
}

void TPop(lock_free_stack<int>& stk) {
  std::this_thread::sleep_for(1ms);
  while (number < 20) {
    auto p = *stk.pop();
    output.emplace_back(p);
    ++number;
  }
}

int main() {
  lock_free_stack<int> stk;
  std::thread push1(TPush, std::ref(stk));
  std::thread push2(TPush, std::ref(stk));
  std::thread pop1(TPop, std::ref(stk));
  std::thread pop2(TPop, std::ref(stk));
  push1.join();
  push2.join();
  pop1.join();
  pop2.join();
  for (const auto& x : output) {
    std::cout << x << " ";
  }
  std::cin.get();
}