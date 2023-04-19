#include <iostream>
#include <eigen3/Eigen/Dense>
#include <string>

void solvesystem(int size);

int main(int argc, char ** argv)
{
  // read params
  if (argc != 3) {
    std::cerr << "Error. Usage: \n" << argv[0] << " M S\n";
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


  Eigen::MatrixXd A = Eigen::MatrixXd::Random(size, size);
  Eigen::MatrixXd b = Eigen::MatrixXd::Random(size, 1);
  // crono star
  //Eigen::MatrixXd x = A.fullPivLu().solve(b);
  Eigen::MatrixXd x = A.lu().solve(b);
  // crono end
  // print some results to use the expression and force computation
  std::clog << x(0) << std::endl;
}

// usar chrono para medir el tiempo
// gprof
// remove printing
// modify testing
