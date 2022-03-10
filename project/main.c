#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/dispatcher.h"

int main(int argc, char *argv[]) {
  printf("%s", GREETING);

  if (argc == COMMAND_LINE_MODE) {
    if (command_line_mode(argv + 1, NULL, NULL)) {
      return EXIT_SUCCESS;
    }
  } else if (argc == CONSOLE_APP_MODE) {
    if (dispatcher(NULL, NULL, NULL)) {
      return EXIT_SUCCESS;
    }
  } else {
    printf("%s", ERROR_MODE_MSG);
  }

  return EXIT_FAILURE;
}
