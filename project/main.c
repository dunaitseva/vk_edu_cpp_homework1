#include "stdio.h"
#include "stdlib.h"

#include "parabola_builder.h"

typedef struct {
  double x;
  double y;
} point_t;

int build_parabola(const point_t *p1,
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

int main() {
  fprintf(stdout, "Hello, World!\n");
  point_t p1 = {1, 12.3};
  point_t p2 = {18, 1.3};
  point_t p3 = {25, 1};
  double a;
  double b;
  double c;
  build_parabola(&p1, &p2, &p3, &a, &b, &c);
  printf("%f %f %f", a, b, c);
  return EXIT_SUCCESS;
}
