#include "thSafeMap.hpp"
#include <thread>
#include <iostream>
#include <assert.h>

void setValue(threadSafe_lookuptable<int, int>& table, std::vector<std::pair<int, int>>& nums, int default_value) {
  for (auto& [key_, val_] : nums) {  // C17 STANDARD
    val_ = table.value_for(key_, default_value);
  }
}

void update(threadSafe_lookuptable<int, int>& table, const std::vector<std::pair<int, int>>& nums) {
  for (const auto& [key_, val_] : nums) {  // C17 STANDARD
    table.add_or_updata_mapping(key_, val_);
  }
}

void rm(threadSafe_lookuptable<int, int>& table, const std::vector<std::pair<int, int>>& nums) {
  for (const auto& [key_, val_] : nums) {  // C17 STANDARD
    table.remove_mapping(key_);
  }
}

const std::vector<std::pair<int, int>> nums = {{13, 0}, {19, 1}, {32, 2}, {38, 3}, {33, 4}};

std::vector<std::pair<int, int>> update_nums = {{13, -1}, {19, -1}, {32, -1}, {38, -1}, {33, -1}};

int main() {
  threadSafe_lookuptable<int, int> table;
  std::thread ud1(update, std::ref(table), std::ref(nums));  // add or update
  std::thread ud2(update, std::ref(table), std::ref(nums));
  std::thread change_nums(setValue, std::ref(table), std::ref(update_nums), -1);  // make update_nums the same as nums
  std::thread rmv(rm, std::ref(table), std::ref(update_nums));                    // use update_nums erase table
  ud1.join();
  ud2.join();
  change_nums.join();
  rmv.join();
  auto m = table.get_map();
  if (!m.empty()) {
    std::cout << "update is failed." << std::endl;
  } else {
    std::cout << "Here is the new update_nums" << std::endl;
    for (const auto& [key, val] : update_nums) {
      std::cout << "key: " << key << " "
                << "val: " << val << std::endl;
    }
  }
  std::cin.get();
}