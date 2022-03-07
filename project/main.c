#include "stdio.h"
#include "stdlib.h"

#include "solver.h"

/*
typedef struct {
  double x;
  double y;
} point_t;

int find_quadratic_coefficients(const point_t *p1,
				   const point_t *p2,
				   const point_t *p3,
				   double *coef_a,
				   double *coef_b,
				   double *coef_c) {
  if (coef_a != NULL) {
	*coef_a = p1->y / ((p1->x - p2->x) * (p1->x - p3->x)) +
		      p2->y / ((p2->x - p1->x) * (p2->x - p3->x)) +
			  p3->y / ((p3->x - p1->x) * (p3->x - p2->x));
  }

  if (coef_b != NULL) {
	*coef_b = (p1->y * (p3->x + p2->x)) / ((p1->x - p2->x) * (p1->x - p3->x)) +
		      (p2->y * (p1->x + p3->x)) / ((p2->x - p1->x) * (p2->x - p3->x)) +
		      (p3->y * (p1->x + p2->x)) / ((p3->x - p1->x) * (p3->x - p2->x));
	*coef_b *= -1.0;
  }

  if (coef_c != NULL) {
	*coef_c = (p1->y * p2->x * p3->x) / ((p1->x - p2->x) * (p1->x - p3->x)) +
		      (p2->y * p1->x * p3->x) / ((p2->x - p1->x) * (p2->x - p3->x)) +
		      (p3->y * p1->x * p2->x) / ((p3->x - p1->x) * (p3->x - p2->x));
  }

  return 1;
}
*/

int main() {
  point_t p1 = {0, -3.5};
//  point_t p2 = {0, -3.5};
  point_t p2 = {0.3, 3.4};
  point_t p3 = {0.6, 0.7};
  double a = 0.0;
  double b = 0.0;
  double c = 0.0;
  if (find_quadratic_coefficients(&p1, &p2, &p3, &a, &b, &c) != SOLUTION_FOUND) {
	printf("Something went wrong!!!\n");
  }
  printf("%f %f %f", a, b, c);
  return EXIT_SUCCESS;
}
