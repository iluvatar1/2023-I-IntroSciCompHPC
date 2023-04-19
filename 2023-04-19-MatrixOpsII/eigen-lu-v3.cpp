#include <iostream>
#include <eigen3/Eigen/Dense>
#include <string>
#include <chrono>
#include <ctime>

void solvesystem(int size);

int main(int argc, char ** argv)
{
  // read params
  if (argc != 3) {
    std::cerr << "Error. Usage: \n" << argv[0] << "M S\n";
    std::cerr << "M: Matrix size\n";
    std::cerr << "S: Random generator seed\n";
    return 1;
  }
  const int M = std::stoi(argv[1]); // Matrix size
  const int S = std::stoi(argv[2]); // Matrix size

  // set seed
  srand(S);

  // solve system
  solvesystem(M);

  return 0;
}

void solvesystem(int size)
{
  // declare matrices
  Eigen::MatrixXd A = Eigen::MatrixXd::Random(size, size);
  Eigen::MatrixXd b = Eigen::MatrixXd::Random(size, 1);
  // perform the actual copmputation and measure time
  auto start = std::chrono::steady_clock::now();
  std::clock_t c1 = std::clock();
  //Eigen::MatrixXd x = A.fullPivLu().solve(b);
  Eigen::MatrixXd x = A.lu().solve(b);
  auto end = std::chrono::steady_clock::now();
  std::clock_t c2 = std::clock();

  // print some results to use the expression and force computation
  std::clog << x(0) << std::endl;

  // print time
  double cpu_time = 1.0*(c2-c1)/CLOCKS_PER_SEC;
  std::chrono::duration<double> elapsed_seconds = end-start;
  double wall_time = elapsed_seconds.count();
  std::cout << size << "  " << wall_time << "  " << cpu_time << "\n";
}
