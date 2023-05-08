#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <execution>
#include <chrono>

#include <tbb/task_scheduler_init.h>

template<typename Func>
void time_function(Func func);

int main() {
  const long ARRAY_SIZE = 100000000;
  std::vector<double> myArray(ARRAY_SIZE);
  std::iota(myArray.begin(), myArray.end(), 0); // fill array with 0, 1, 2, ..., ARRAY_SIZE-1

  tbb::task_scheduler_init init(8);
  
  // sequential execution
  auto serial = [&myArray](){return std::accumulate(myArray.begin(), myArray.end(), 0.0);};
  time_function(serial);

  // parallel execution
  auto parallel = [&myArray](){return std::reduce(std::execution::par, myArray.begin(), myArray.end());};
  time_function(parallel);

  return 0;
}

template<typename Func>
void time_function(Func func) {
  auto start = std::chrono::high_resolution_clock::now();
  func();
  auto end = std::chrono::high_resolution_clock::now();
  auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << "Elapsed time: " << duration_ms/1000.0 << "  s" << std::endl;
}
