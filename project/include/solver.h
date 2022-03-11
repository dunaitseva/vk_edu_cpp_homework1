#ifndef PROJECT_INCLUDE_SOLVER_H_
#define PROJECT_INCLUDE_SOLVER_H_

#include "include/point.h"

typedef enum {
  SOLUTION_FOUND,
  NON_INDEPENDENT_SYSTEM,
  WRONG_INPUT
} solver_status_t;

int find_quadratic_coefficients(const point_t *p1, const point_t *p2,
                                const point_t *p3, double *coef_a,
                                double *coef_b, double *coef_c);

#endif  // PROJECT_INCLUDE_SOLVER_H_
