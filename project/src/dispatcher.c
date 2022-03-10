#include "../include/dispatcher.h"

#include <stdio.h>
#include <string.h>

#include "../include/point.h"
#include "../include/solver.h"

static void show_solution(point_t *points[REQ_POINTS_AMOUNT], FILE *os,
                          FILE *es);
static void free_resources(point_t *points[REQ_POINTS_AMOUNT]);
static void print_error_msg(int err, FILE *es);
static int solution_command(FILE *is, FILE *os, FILE *es);

int command_line_mode(char *points_argv[], FILE *os, FILE *es) {
  if (points_argv == NULL) {
    return 0;
  }

  os = (os == NULL ? stdout : os);
  es = (es == NULL ? stderr : es);

  point_t *points[REQ_POINTS_AMOUNT];
  memset(points, 0, sizeof(point_t *) * REQ_POINTS_AMOUNT);
  for (size_t i = 0; i < REQ_POINTS_AMOUNT; ++i) {
    int err;
    size_t point_argument_len = strlen(points_argv[i]);
    points[i] =
        create_point_from_string(points_argv[i], point_argument_len, &err);
    if (points[i] == NULL) {
      print_error_msg(err, es);
      free_resources(points);
      return 1;
    }
  }

  show_solution(points, os, es);
  free_resources(points);
  return 1;
}

int dispatcher(FILE *is, FILE *os, FILE *es) {
  is = (is == NULL ? stdin : is);
  os = (os == NULL ? stdout : os);
  es = (es == NULL ? stderr : es);
  //  fprintf(os, GREETING);

  while (1) {
    fprintf(os, "%s", CMD_INPUT_INVITE);
    int cmd = get_cmd(is);
    switch (cmd) {
      case CSOL:
        if (!solution_command(is, os, es)) {
          return 0;
        }
        break;

      case CEXT:
        return 1;

      default:
        fprintf(es, "%s", ECMD_MSG);
    }
  }
}

int get_cmd(FILE *is) {
  is = (is == NULL ? stdin : is);

  char cmd_buff[MAX_COMMAND_LENGTH];
  fscanf(is, COMMAND_FORMAT_INPUT, cmd_buff);
  fgetc(is);

  if (strcmp(cmd_buff, SOL_CMD) == 0) {
    return CSOL;
  }

  if (strcmp(cmd_buff, EXT_CMD) == 0) {
    return CEXT;
  }

  return ECMD;
}

static int solution_command(FILE *is, FILE *os, FILE *es) {
  point_t *points[REQ_POINTS_AMOUNT];
  memset(points, 0, sizeof(point_t *) * REQ_POINTS_AMOUNT);
  for (int i = 0; i < REQ_POINTS_AMOUNT; ++i) {
    int err;
    fprintf(os, "%s", POINT_INPUT_INVITE);
    points[i] = read_point(is, &err);

    if (points[i] == NULL) {
      print_error_msg(err, es);
      free_resources(points);
      return 0;
    }
    fgetc(is);
  }

  show_solution(points, os, es);
  free_resources(points);
  return 1;
}

static void print_error_msg(int err, FILE *es) {
  switch (err) {
    case EFMTI:
      fprintf(es, "%s", EFMTI_MSG);
      break;
    case EREPR:
      fprintf(es, "%s", EREPR_MSG);
      break;
    default:
      fprintf(es, "%s", OTHER_ERR_MSG);
  }
}

static void show_solution(point_t *points[REQ_POINTS_AMOUNT], FILE *os,
                          FILE *es) {
  double a_coef;
  double b_coef;
  double c_coef;
  int err = find_quadratic_coefficients(points[0], points[1], points[2],
                                        &a_coef, &b_coef, &c_coef);
  if (err == SOLUTION_FOUND) {
    fprintf(os, SOLUTION_MSG, a_coef, b_coef, c_coef);
  }

  if (err == NON_INDEPENDENT_SYSTEM) {
    fprintf(es, "%s", NON_IND_MSG);
  }
}

static void free_resources(point_t *points[REQ_POINTS_AMOUNT]) {
  for (size_t i = 0; i < REQ_POINTS_AMOUNT; ++i) {
    if (points[i] != NULL) {
      delete_point(points[i]);
    }
  }
}
