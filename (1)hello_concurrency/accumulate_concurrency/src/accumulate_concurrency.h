#include <numeric>
#include <thread>
#include <vector>

template <typename Iterator, typename T>
struct accumulate_block {
  void operator()(Iterator first, Iterator last, T& result) {
    result = std::accumulate(first, last, result);
  }
};

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
  const uint64_t length = std::distance(first, last);
  if (!length) {
    return init;
  }
  const uint64_t min_per_threads = 25;
  const uint64_t max_threads = (length + min_per_threads - 1) / min_per_threads;
  const uint64_t hardware_threads = std::thread::hardware_concurrency();
  const uint64_t nums_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
  const uint64_t block_size = length / nums_threads;
  std::vector<T> results(nums_threads);
  std::vector<std::thread> threads(nums_threads - 1);
  Iterator block_start = first;
  for (uint64_t i = 0; i < (nums_threads - 1); ++i) {
    Iterator block_end = block_start;
    std::advance(block_end, block_size);
    threads[i] = std::thread(accumulate_block<Iterator, T>(), block_start, block_end, std::ref(results[i]));
    block_start = block_end;
  }
  accumulate_block<Iterator, T>()(block_start, last, results[nums_threads - 1]);
  for (auto& entry : threads) {
    entry.join();
  }
  return std::accumulate(results.begin(), results.end(), init);
}