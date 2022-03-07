#ifndef PARABOLA_SOLVER_H_
#define PARABOLA_SOLVER_H_

typedef struct {
  double x;
  double y;
} point_t;

typedef enum {
  SOLUTION_FOUND,
  NON_INDEPENDENT_SYSTEM,
  WRONG_INPUT
} solver_status_t;

int find_quadratic_coefficients(const point_t *p1, const point_t *p2,
                                const point_t *p3, double *coef_a,
                                double *coef_b, double *coef_c);

#endif  // PARABOLA_SOLVER_H_
