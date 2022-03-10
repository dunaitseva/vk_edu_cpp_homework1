#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/point.h"

#define POINT "{000000000; 1}"

int main() {
  size_t string_size = strlen(POINT);
  int err;
  point_t *p = create_point_from_string(POINT, string_size, &err);
  if (p == NULL) {
    printf("Error code: %d\n", err);
    return EXIT_FAILURE;
  }

  printf("%lf %lf\n", p->x, p->y);
  delete_point(p);
  return EXIT_SUCCESS;
}
