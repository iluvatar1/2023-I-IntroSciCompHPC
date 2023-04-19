#include <iostream>
#include <eigen3/Eigen/Dense>
#include <string>
#include <chrono>
#include <ctime>

void solvesystem(int size, int nreps);

int main(int argc, char ** argv)
{
  // read params
  if (argc != 4) {
    std::cerr << "Error. Usage: \n" << argv[0] << " M S R\n";
    std::cerr << "M: Matrix size\n";
    std::cerr << "S: Random generator seed\n";
    std::cerr << "R: Number of repetitions\n";
    return 1;
  }
  const int M = std::stoi(argv[1]); // Matrix size
  const int S = std::stoi(argv[2]); // Seed
  const int R = std::stoi(argv[3]); // Reps

  // set seed
  srand(S);

  // solve system
  solvesystem(M, R);

  return 0;
}

void solvesystem(int size, int nreps)
{
  // cummulate time
  double wall_time = 0.0;
  double wall_time2 = 0.0;
  double cpu_time = 0.0;
  double cpu_time2 = 0.0;

  for (int ii = 0; ii < nreps; ++ii) {
    // set a new seed
    srand(ii);
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

    // measure time
    double aux_cpu_time = 1.0*(c2-c1)/CLOCKS_PER_SEC;
    std::chrono::duration<double> elapsed_seconds = end-start;
    double aux_wall_time = elapsed_seconds.count();
    wall_time += aux_wall_time;
    wall_time2 += aux_wall_time*aux_wall_time;
    cpu_time += aux_cpu_time;
    cpu_time2 += aux_cpu_time*aux_cpu_time;
  }
  // print results
  double mean_wall_time = wall_time/nreps;
  double mean_cpu_time = cpu_time/nreps;
  double std_wall_time = std::sqrt((wall_time2/nreps - mean_wall_time*mean_wall_time)/nreps);
  double std_cpu_time = std::sqrt((cpu_time2/nreps - mean_cpu_time*mean_cpu_time)/nreps);
  std::cout.precision(15);
  std::cout.setf(std::ios::scientific);
  std::cout << size << "  "
            << mean_wall_time << "  " << std_wall_time << "  "
            << mean_cpu_time << "  " << std_cpu_time << "\n";
}
