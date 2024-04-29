#include "threadSafe_list.hpp"
#include <iostream>
#include <functional>
#include <vector>
#include <thread>

auto f = [](int& data) { data += 1; };
auto f_print = [](int data) {
  static int index = 0;
  std::cout << data;
  ++index;
  if (index % 6 == 0) {
    std::cout << std::endl;
  }
};
auto p = [](int data) {
  if (data == 5) {
    return true;
  }
  return false;
};

const std::vector<int> nums = {0, 1, 2, 3, 4, 5};

void push(threadSafe_list<int>& list, const std::vector<int>& nums) {
  for (const auto& num : nums) {
    list.push_front(num);
  }
}

void add(threadSafe_list<int>& list) {
  list.for_each(f);
  list.for_each(f_print);
}

void find(threadSafe_list<int>& list, std::shared_ptr<int> res) {
  res = list.find_first_if(p);
}

void rm(threadSafe_list<int>& list) {
  list.for_each(f_print);
  std::cout << std::endl << "start remove" << std::endl;
  list.remove_if(p);
  list.for_each(f_print);
}

int main() {
  threadSafe_list<int> list;
  std::shared_ptr<int> first_find;
  std::thread push1(push, std::ref(list), std::ref(nums));
  std::thread push2(push, std::ref(list), std::ref(nums));
  // std::thread add1(add, std::ref(list));
  // std::thread add2(add, std::ref(list));
  std::thread fd(find, std::ref(list), first_find);
  std::thread rmv1(rm, std::ref(list));
  std::thread rmv2(rm, std::ref(list));
  push1.join();
  push2.join();
  // add1.join();
  // add2.join();
  fd.join();
  rmv1.join();
  rmv2.join();
  std::cin.get();
}