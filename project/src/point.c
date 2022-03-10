#include "../include/point.h"

#include <stdlib.h>
#include <string.h>

static void set_err_status(int *err_storage, int err_code);

point_t *create_point(double x_val, double y_val, int *err) {
  point_t *result_point = (point_t *)malloc(sizeof(point_t));
  if (result_point == NULL) {
    set_err_status(err, EALLOC);
    return NULL;
  }
  result_point->x = x_val;
  result_point->y = y_val;
  return result_point;
}

point_t *read_point(FILE *stream, int *err) {
  if (stream == NULL) {
    set_err_status(err, ESTREAM);
    return NULL;
  }

  // prepare buffers for float point digits input
  char x_string_repr[MAX_CONSOLE_INPUT];
  char y_string_repr[MAX_CONSOLE_INPUT];
  memset((void *)x_string_repr, 0, MAX_CONSOLE_INPUT);
  memset((void *)y_string_repr, 0, MAX_CONSOLE_INPUT);

  char tail_sym = 0;
  int read_status = fscanf(stream, POINT_INPUT_FORMAT, x_string_repr,
                           y_string_repr, &tail_sym);
  if (read_status == EOF || read_status < INPUT_ITEMS_COUNT ||
      tail_sym != BRACKET_TAIL) {
    set_err_status(err, EFMTI);
    return NULL;
  }

  char *tmp_ptr_x_repr = x_string_repr;
  char *tmp_ptr_y_repr = y_string_repr;
  double x_val = strtod(x_string_repr, &tmp_ptr_x_repr);
  double y_val = strtod(y_string_repr, &tmp_ptr_y_repr);

  /* This part means that string performing to float point digit was failed
   according the manual for strtod function. So if  operation was success
   tmp_ptr_<coord>_repr will refer after last byte used in conversion. So
   if all string's bytes of digit was performed, tmp_ptr_<coord>_repr should
   have value 0 or '\0'. In other cases it means that error occurred. */
  // if (y_string_repr == tmp_ptr_x_repr || tmp_ptr_y_repr == y_string_repr) {
  if (*tmp_ptr_x_repr || *tmp_ptr_y_repr) {
    set_err_status(err, EREPR);
    return NULL;
  }

  point_t *result_point = create_point(x_val, y_val, NULL);
  if (result_point == NULL) {
    set_err_status(err, EALLOC);
  }

  return result_point;
}

point_t *create_point_from_string(char *str_point_repr, size_t size, int *err) {
  if (str_point_repr == NULL || size == 0) {
    set_err_status(err, EEMTYSTR);
    return NULL;
  }

  // Open string as FILE with read option
  FILE *sstream = fmemopen(str_point_repr, size, "r");
  if (sstream == NULL) {
    set_err_status(err, ESTREAM);
    return NULL;
  }

  point_t *result = read_point(sstream, err);
  fclose(sstream);

  return result;
}

int delete_point(point_t *point) {
  if (point == NULL) {
    return -1;
  }

  free(point);
  return 0;
}

/*
 * Following function is util for set err variable in defined code
 * if pointer to variable is not null in one command.
 */
static void set_err_status(int *err_storage, int err_code) {
  if (err_storage != NULL) {
    *err_storage = err_code;
  }
}
