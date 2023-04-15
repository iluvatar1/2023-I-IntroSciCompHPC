#include <iostream>
#include <eigen3/Eigen/Dense>

void solvesystem(int size);

int main(int argc, char ** argv)
{
  const int M = atoi(argv[1]); // Matrix size
  solvesystem(M);
}

void solvesystem(int size)
{
  Eigen::MatrixXd A = Eigen::MatrixXd::Random(size, size);
  Eigen::MatrixXd b = Eigen::MatrixXd::Random(size, 1);
  Eigen::MatrixXd x = A.fullPivLu().solve(b);
  double relative_error = (A*x - b).norm() / b.norm(); // norm() is L2 norm
  std::cout << A << std::endl;
  std::cout << b << std::endl;
  std::cout << "The relative error is:\n" << relative_error << std::endl;
}
