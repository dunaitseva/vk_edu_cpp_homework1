#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/dispatcher.h"

#define GREETING                               \
  "Hello. This program will help you find\n"   \
  "the coefficients of a quadratic function\n" \
  "from 3 points on a plane.\n"                \
  "----------------------------------------\n"
#define PARTING "Thanks for using\n"

int main(int argc, char *argv[]) {
  printf("%s", GREETING);

  if (argc == COMMAND_LINE_MODE) {
    if (command_line_mode(argv + 1, NULL, NULL)) {
      fprintf(stdout, PARTING);
      return EXIT_SUCCESS;
    }
  } else if (argc == CONSOLE_APP_MODE) {
    if (dispatcher(NULL, NULL, NULL)) {
      fprintf(stdout, PARTING);
      return EXIT_SUCCESS;
    }
  } else {
    printf("%s", ERROR_MODE_MSG);
  }

  return EXIT_FAILURE;
}
