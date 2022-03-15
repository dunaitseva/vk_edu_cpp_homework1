#include "include/solver.h"

#include <stddef.h>

static int is_independent(const point_t *p1, const point_t *p2,
                          const point_t *p3);

/* To search for the coefficients of a quadratic function passing through three
 * points, it makes sense to use the theoretical base of interpolation by the
 * Lagrange polynomial. Using this interpolation polynomial for three points, we
 * get a parabola that, according to the definition of interpolation, passes
 * through three given points. In order to find the required coefficients a, b
 * and c, we give the resulting interpolation polynomial to the usual form for a
 * quadratic function, thus we obtain expressions for the corresponding
 * coefficients.
 */
int find_quadratic_coefficients(const point_t *p1, const point_t *p2,
                                const point_t *p3, double *coef_a,
                                double *coef_b, double *coef_c) {
  if (p1 == NULL || p2 == NULL || p3 == NULL) {
    return WRONG_INPUT;
  }

  if (!is_independent(p1, p2, p3)) {
    return NON_INDEPENDENT_SYSTEM;
  }

  // In desired form of Lagrange polynom for
  // every coefficient uses the same denominators
  double diff1 = (p1->x - p2->x) * (p1->x - p3->x);
  double diff2 = (p2->x - p1->x) * (p2->x - p3->x);
  double diff3 = (p3->x - p1->x) * (p3->x - p2->x);

  double tmp_coef_a = p1->y / diff1 + p2->y / diff2 + p3->y / diff3;
  double tmp_coef_b =
      ((p1->y * (p3->x + p2->x)) / diff1 + (p2->y * (p1->x + p3->x)) / diff2 +
       (p3->y * (p1->x + p2->x)) / diff3) *
      -1.0;
  double tmp_coef_c = (p1->y * p2->x * p3->x) / diff1 +
                      (p2->y * p1->x * p3->x) / diff2 +
                      (p3->y * p1->x * p2->x) / diff3;

  if (coef_a != NULL) {
    *coef_a = tmp_coef_a;
  }

  if (coef_b != NULL) {
    *coef_b = tmp_coef_b;
  }

  if (coef_c != NULL) {
    *coef_c = tmp_coef_c;
  }

  return SOLUTION_FOUND;
}

/* The following function assumes that the system that lies under the Lagrange
 * polynomial interpolation method is linearly independent, that is, it has
 * exactly one solution. To do this, you need to make sure that all points are
 * different.
 */
static int is_independent(const point_t *p1, const point_t *p2,
                          const point_t *p3) {
  if (p1->x == p2->x && p1->y == p2->y) {
    return 0;
  }

  if (p1->x == p3->x && p1->y == p3->y) {
    return 0;
  }

  if (p2->x == p3->x && p2->y == p3->y) {
    return 0;
  }

  return 1;
}
