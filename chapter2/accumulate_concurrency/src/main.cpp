#include "accumulate_concurrency.h"
#include <iostream>

using namespace std;

const vector<int> nums = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int main() {
  auto res = parallel_accumulate(nums.begin(), nums.end(), 0);
  cout << "acumulate = " << res << endl;
  cin.get();
}