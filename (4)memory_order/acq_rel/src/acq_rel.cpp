#include <atomic>
#include <thread>
#include <iostream>
#include <assert.h>

std::atomic<bool> x, y;
std::atomic<int> z;

void write_x_then_y() {
  x.store(true, std::memory_order_relaxed);
  y.store(true, std::memory_order_release);  // Any operation in front of it must not be rearranged after it
}

void read_y_then_x() {
  while (!y.load(std::memory_order_acquire)) {  // Any operation after it must not be rearranged before it
  };
  if (x.load(std::memory_order_relaxed)) {
    ++z;
  }
}

int main() {
  x = false;
  y = false;
  z = 0;
  std::thread a(write_x_then_y);
  std::thread b(read_y_then_x);
  a.join();
  b.join();
  assert(z.load() != 0);
  std::cout << "TRUE!" << std::endl;
  std::cin.get();
}