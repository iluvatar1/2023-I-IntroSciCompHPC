#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <execution>

int main() {
    const long ARRAY_SIZE = 400000000;
    std::vector<double> myArray(ARRAY_SIZE);
    std::iota(myArray.begin(), myArray.end(), 0); // fill array with 0, 1, 2, ..., ARRAY_SIZE-1

    // sequential execution
    auto sum_seq = std::accumulate(myArray.begin(), myArray.end(), 0.0);
    std::cout << "Sequential sum: " << sum_seq << std::endl;

    // parallel execution
    auto sum_par = std::reduce(std::execution::par, myArray.begin(), myArray.end());
    std::cout << "Parallel sum: " << sum_par << std::endl;

    return 0;
}
