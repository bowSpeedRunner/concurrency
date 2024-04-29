#include "dns_cache.h"
#include <iostream>
#include <thread>
#include <vector>
dns_cache test_cahce;
void read_thread();
void write_thread();
const std::vector<std::string> domins{"192.168.1.1", "1.1.1.1", "2.2.2.2", "3.3.3.3", "4.4.4.4", "5.5.5.5"};
using namespace std::literals;
int main() {
  std::thread test_read(read_thread);
  std::thread test_write(write_thread);
  test_read.join();
  test_write.join();
  std::cin.get();
}
void read_thread() {
  for (int i = 1; i < 10; ++i) {
    for (const auto& domin : domins) {
      auto res = test_cahce.find_entry(domin);
      if (!res) {
        std::cout << "not exist yet!" << std::endl;
      } else {
        std::cout << "find it! domin_entry is " << res << std::endl;
      }
    }
  }
}

void write_thread() {
  //std::this_thread::sleep_for(1ms);
  for (std::size_t i = 0; i < domins.size(); ++i) {
    auto details = i + 1;
    std::string domin = domins[i];
    test_cahce.update_or_add_entry(domin, details);
  }
}