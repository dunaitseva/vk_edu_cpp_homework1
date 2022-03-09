#ifndef PROJECT_INCLUDE_POINT_H_
#define PROJECT_INCLUDE_POINT_H_

#include <stdio.h>

#define INPUT_ITEMS_COUNT 3
#define MAX_CONSOLE_INPUT 161
#define POINT_INPUT_FORMAT "{%80[.0-9e-]; %80[.0-9e-]%1c"
#define BRACKET_TAIL '}'

typedef struct {
  double x;
  double y;
} point_t;

typedef enum {
  ESTREAM = 2,  // Error with stream pointer
  EFMTI,        // Error in format input
  EALLOC,       // Error in memory allocating
  EREPR,        // Error in float point digit representation
} point_errors_t;

/*
 * The behavior of the following three functions is reflected in their names.
 * They return zero in case of an error, the error code is written to the
 * variable err if it is not NULL.
 */
point_t *create_point(double x_val, double y_val, int *err);

point_t *read_point(FILE *stream, int *err);

/*
 * Also, I add feature the creation of point from string. It's pretty
 * helpful for user's generally and improve the flexibility of library.
 * For particular example it can be used for some kind serialization
 * of point data.
 */
point_t *create_point_from_string(char *str_point_repr, int *err);

// Free resources from point. Return -1 if point si NULL and 0 on success.
int delete_point(point_t *point);

#endif  // PROJECT_INCLUDE_POINT_H_
