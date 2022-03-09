#ifndef PROJECT_INCLUDE_DISPATCHER_H_
#define PROJECT_INCLUDE_DISPATCHER_H_

#include <stdio.h>

#define MAX_COMMAND_LENGTH 6
#define COMMAND_FORMAT_INPUT "%5s"
#define SOL_CMD "solve"
#define EXT_CMD "exit"

#define GREETING                             \
  "Hello. This program will help you find"   \
  "the coefficients of a quadratic function" \
  "from 3 points on a plane."
#define COMMANDS_HEADER "Choose the command:"

typedef enum { CSOL, CEXT, ECMD } command_t;

typedef enum {
  OK = 127,
  EMPTY_STREAM,
} dispatcher_completion_status_t;

int dispatch();

int read_cmd();

#endif  // PROJECT_INCLUDE_DISPATCHER_H_
