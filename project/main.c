#include "stdio.h"
#include "stdlib.h"

#include "solver.h"

int main() {
  point_t p1 = {0, 0.02};
  point_t p2 = {0.3, 0.4};
  point_t p3 = {0.6, 0.07};
  double a = 0.0;
  double b = 0.0;
  double c = 0.0;
  if (find_quadratic_coefficients(&p1, &p2, &p3, &a, &b, &c) != SOLUTION_FOUND) {
	printf("Something went wrong!!!\n");
  }
  printf("%f %f %f", a, b, c);
  return EXIT_SUCCESS;
}
