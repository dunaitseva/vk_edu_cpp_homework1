#include <gtest/gtest.h>

#include <cstddef>

extern "C" {
#include "../project/include/solver.h"
}

constexpr double ABS_SOL_ERROR = 1e-5;

struct SolverTestsSolution : public testing::Test {
 protected:
  point_t p1 = {0, 0.02};
  point_t p2 = {0.3, 0.4};
  point_t p3 = {0.6, 0.07};

  double sol_a = 0.0;
  double sol_b = 0.0;
  double sol_c = 0.0;
};

static double quadratic_function(double coef_a, double coef_b, double coef_c,
                                 double x) {
  return coef_a * x * x + coef_b * x + coef_c;
}

TEST_F(SolverTestsSolution, BasicSolution) {
  // Expected values calculated analytically
  double expected_a = -71.0 / 18.0;
  double expected_b = 49.0 / 20.0;
  double expected_c = 1.0 / 50.0;

  int status =
      find_quadratic_coefficients(&p1, &p2, &p3, &sol_a, &sol_b, &sol_c);
  EXPECT_EQ(status, SOLUTION_FOUND);
  ASSERT_DOUBLE_EQ(expected_a, sol_a);
  ASSERT_DOUBLE_EQ(expected_b, sol_b);
  ASSERT_DOUBLE_EQ(expected_c, sol_c);
}

TEST_F(SolverTestsSolution, InterpolationProperties) {
  int status =
      find_quadratic_coefficients(&p1, &p2, &p3, &sol_a, &sol_b, &sol_c);
  EXPECT_EQ(status, SOLUTION_FOUND);
  ASSERT_NEAR(quadratic_function(sol_a, sol_b, sol_c, p1.x), p1.y,
              ABS_SOL_ERROR);
  ASSERT_NEAR(quadratic_function(sol_a, sol_b, sol_c, p2.x), p2.y,
              ABS_SOL_ERROR);
  ASSERT_NEAR(quadratic_function(sol_a, sol_b, sol_c, p3.x), p3.y,
              ABS_SOL_ERROR);
}

TEST(SolverTestInput, NullPoints) {
  point_t p1;

  ASSERT_EQ(find_quadratic_coefficients(NULL, &p1, &p1, NULL, NULL, NULL),
            WRONG_INPUT);
  ASSERT_EQ(find_quadratic_coefficients(&p1, NULL, &p1, NULL, NULL, NULL),
            WRONG_INPUT);
  ASSERT_EQ(find_quadratic_coefficients(&p1, &p1, NULL, NULL, NULL, NULL),
            WRONG_INPUT);
}

TEST(SolverTestInput, LinearityPropertiesValid) {
  point_t p1 = {1.0, 1.0};
  point_t p2 = {2.0, 2.0};
  point_t p3 = {3.0, 3.0};

  ASSERT_EQ(find_quadratic_coefficients(&p1, &p2, &p3, NULL, NULL, NULL),
            SOLUTION_FOUND);
}

TEST(SolverTestInput, LinearityPropertiesInvalid) {
  point_t p1 = {1.0, 1.0};

  ASSERT_EQ(find_quadratic_coefficients(&p1, &p1, &p1, NULL, NULL, NULL),
            NON_INDEPENDENT_SYSTEM);
}
