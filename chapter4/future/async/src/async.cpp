#include <iostream>
#include <future>
int find_answer();
void do_things();
int main() {
  std::future<int> number = std::async(find_answer);
  do_things();
  std::cout << "the number find is " << number.get() << std::endl;
  std::cin.get();
}

int find_answer() {
  return 17;
}

void do_things() {
  std::cout << "now do other things" << std::endl;
}