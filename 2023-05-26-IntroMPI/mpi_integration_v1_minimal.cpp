#include <cstdio>
#include <mpi.h>
#include <iostream>
#include <string>

/* Problem parameters */
double f(double x);
double integral_serial(double xmin, double xmax, double n);

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);
  int pid, np;
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  std::cout << pid << " " << np << "\n";

  // TODO : Check argc==4
  const double lowerLimit = std::stod(argv[1]);
  const double upperLimit = std::stod(argv[2]);
  const int numberRects = std::stoi(argv[3]);;

  double integral = integral_serial(lowerLimit, upperLimit, numberRects);
  printf("The area from %lf to %lf is : %lf\n", lowerLimit, upperLimit, integral);

  MPI_Finalize();
  return 0;
}

double f(double x) {
  return x*x;
}

double integral_serial(double xmin, double xmax, double n)
{
  double area = 0.0;
  double width = (xmax - xmin)/n;

  for (int i = 0; i < n; ++i) {
    double at = xmin + i*width + width/2.0; // center in the middle
    double heigth = f(at);
    area = area + width*heigth;
  }
  return area;
}
