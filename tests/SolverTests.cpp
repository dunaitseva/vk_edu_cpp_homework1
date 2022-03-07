#include <gtest/gtest.h>

extern "C" {
#include "solver.h"
}

#define EPS 1e-5



TEST(HelloTest, BasicAssertions) {
  printf("%f", EPS);
  EXPECT_STRNE("hello", "world");
  EXPECT_EQ(7 * 6, 42);
}