#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <execution>
#include <chrono>

int main() {
    const long ARRAY_SIZE = 100000000;
    std::vector<double> myArray(ARRAY_SIZE);
    std::iota(myArray.begin(), myArray.end(), 0); // fill array with 0, 1, 2, ..., ARRAY_SIZE-1

    // sequential execution
    auto start_time = std::chrono::high_resolution_clock::now();
    auto sum_seq = std::accumulate(myArray.begin(), myArray.end(), 0.0);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto seq_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Sequential sum: " << sum_seq << "( took : " << seq_duration.count()/1000.0 << " s)" << std::endl;

    // parallel execution
    start_time = std::chrono::high_resolution_clock::now();
    auto sum_par = std::reduce(std::execution::par, myArray.begin(), myArray.end());
    end_time = std::chrono::high_resolution_clock::now();
    seq_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Parallel sum: " << sum_par << "( took : " << seq_duration.count()/1000.0 << " s)" << std::endl;

    return 0;
}
