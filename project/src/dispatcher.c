#include "../include/dispatcher.h"

#include <stdio.h>
#include <string.h>

int read_cmd() {
  char cmd_buffer[MAX_COMMAND_LENGTH];
  int status = fscanf(stdin, COMMAND_FORMAT_INPUT, cmd_buffer);
  if (status == EOF || status != 1) {
    return 0;
  }

  if (strncmp(cmd_buffer, SOL_CMD, MAX_COMMAND_LENGTH - 1) == 0) {
    return CSOL;
  }

  if (strncmp(cmd_buffer, EXT_CMD, MAX_COMMAND_LENGTH - 1) == 0) {
    return CEXT;
  }

  return ECMD;
}
