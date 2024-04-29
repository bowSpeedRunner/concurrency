#include "hierarchical_mutex.h"
#include <iostream>
#include <thread>
int do_low_level_stuff();
int low_level_func();
void do_mid_level_stuff();
void mid_level_func();
void do_high_level_stuff(int);
void high_level_func();
void test_thread_a();  // correct one
void test_thread_b();  // error one
hierarchical_mutex high_level_mutex(10000);
hierarchical_mutex mid_level_mutex(5000);
hierarchical_mutex low_level_mutex(1000);
int main() {
  std::thread test_correct(test_thread_a);
  test_correct.join();
  std::thread test_error(test_thread_b);
  test_error.join();
  std::cin.get();
}

int do_low_level_stuff() {
  std::cout << "this is low, and the number is 0" << std::endl;
  return 0;
}

int low_level_func() {
  std::lock_guard<hierarchical_mutex> lk(low_level_mutex);
  return do_low_level_stuff();
}

void do_mid_level_stuff() {
  std::cout << "this is mid, and the number is 1" << std::endl;
}

void mid_level_func() {
  high_level_func();
  do_mid_level_stuff();
}

void do_high_level_stuff(int) {
  std::cout << "this is high, and the number is 2" << std::endl;
}

void high_level_func() {
  std::lock_guard<hierarchical_mutex> lk(high_level_mutex);
  do_high_level_stuff(low_level_func());
}

void test_thread_a() {
  high_level_func();
}

void test_thread_b() {
  std::lock_guard<hierarchical_mutex> lk(mid_level_mutex);
  mid_level_func();
}