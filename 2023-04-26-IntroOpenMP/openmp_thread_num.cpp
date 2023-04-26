#include <iostream>
#include <omp.h>

int main(int argc, char *argv[]) {
  std::cout << "BEFORE\n";
#pragma omp parallel
  {
    std::cout << "Hola mundo, desde el thread " << omp_get_thread_num() << "\n";
  }
  std::cout << "AFTER\n";
    
  return 0;
}
