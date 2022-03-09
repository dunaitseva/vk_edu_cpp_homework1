#ifndef PROJECT_INCLUDE_DISPATCHER_H_
#define PROJECT_INCLUDE_DISPATCHER_H_

#include <stdio.h>

#define MAX_COMMAND_LENGTH 6

#define GREETING                             \
  "Hello. This program will help you find"   \
  "the coefficients of a quadratic function" \
  "from 3 points on a plane."
#define COMMANDS_HEADER "Choose the command:"

typedef enum { CSOL, CEXT } command_t;

int dispatch(FILE *is, FILE *os, FILE *es);

#endif  // PROJECT_INCLUDE_DISPATCHER_H_
