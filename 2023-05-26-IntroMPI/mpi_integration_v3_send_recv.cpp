#include <cstdio>
#include <mpi.h>
#include <iostream>
#include <string>
#include <cmath>

/* Problem parameters */
double f(double x);
double integral_serial(double xmin, double xmax, int n);
double integral_parallel(double xmin, double xmax, int n, int pid, int np);

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);
  int pid, np;
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);

  // TODO : Check argc==4
  const double lowerLimit = std::stod(argv[1]);
  const double upperLimit = std::stod(argv[2]);
  const int numberRects = std::stoi(argv[3]);;

  /*
    cada pid calcula su integral
    si soy el pid 0: comienzo a recibir y a sumar las integrales parciales
    si no soy el pid 0, envio mi integral
   */
  // cada pid calcula la integral
  double integral = integral_parallel(lowerLimit, upperLimit, numberRects, pid, np);
  // communication
  if (0 == pid) {
    // recv
    double buffer;
    for (int opid = 1; opid < np; ++opid) {
      MPI_Recv(&buffer, 1, MPI_DOUBLE, opid , 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      integral += buffer;
    }
    printf("The area from %lf to %lf is : %lf\n", lowerLimit, upperLimit, integral);
  } else {
    // send
    MPI_Send(&integral, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}

double f(double x) {
  return x*x*std::sin(x*std::sin(x))+x*std::sin(x*std::sqrt(std::fabs(x)));
}

double integral_serial(double xmin, double xmax, int n)
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

double integral_parallel(double xmin, double xmax, int n, int pid, int np)
{
  // WARNING TODO: Fix n%np != 0
  int nlocal = n/np;
  double wlocal = (xmax-xmin)/np;
  double xminlocal = xmin + pid*wlocal;
  double xmaxlocal = xminlocal + wlocal;
  return integral_serial(xminlocal, xmaxlocal, nlocal);
}
