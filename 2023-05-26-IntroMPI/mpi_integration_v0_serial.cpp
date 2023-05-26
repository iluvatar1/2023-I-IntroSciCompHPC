#include <cstdio>

/* Problem parameters */
double f(double x);
double integral_serial(double xmin, double xmax, double n);

int main(int argc, char **argv)
{
  const int numberRects = 50;
  const double lowerLimit = 2.0;
  const double upperLimit = 5.0;

  double integral = integral_serial(lowerLimit, upperLimit, numberRects);
  printf("The area from %lf to %lf is : %lf\n", lowerLimit, upperLimit, integral);

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
