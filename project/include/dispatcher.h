#ifndef PROJECT_INCLUDE_DISPATCHER_H_
#define PROJECT_INCLUDE_DISPATCHER_H_

#include <stdio.h>
#include <stdlib.h>

// General defines
#define REQ_POINTS_AMOUNT 3
#define SOLUTION_MSG     \
  "coefficient a: %lf\n" \
  "coefficient b: %lf\n" \
  "coefficient c: %lf\n"

// Possible application work modes
#define COMMAND_LINE_MODE 4
#define CONSOLE_APP_MODE 1

// Error messages
#define ERROR_MODE_MSG "Error. Work only with 1 or 3 arguments.\n"
#define EFMTI_MSG "Error in point input format. Format sample {12.3; 23e-2}.\n"
#define EREPR_MSG "Invalid number format\n"
#define NON_IND_MSG "Solution was not found, non independent system\n"
#define WRONG_INPUT_MSG "Solution can't be found. Solver input error.\n"
#define OTHER_ERR_MSG \
  "A system error has occurred that does not depend on the user\n"

// Defines for dispatcher mode (commands, messages, sizes)
#define MAX_COMMAND_LENGTH 6
#define COMMAND_FORMAT_INPUT "%5s"
#define SOL_CMD "solve"
#define EXT_CMD "exit"
#define PARTING "Thanks for using\n"
#define ECMD_MSG "Commands available: solve, exit.\n"
#define GREETING                               \
  "Hello. This program will help you find\n"   \
  "the coefficients of a quadratic function\n" \
  "from 3 points on a plane.\n"                \
  "----------------------------------------\n"
#define CMD_INPUT_INVITE "Choose the command: "
#define POINT_INPUT_INVITE "Enter point: "

// Possible commands codes, also added unexpected command code
typedef enum { CSOL, CEXT, ECMD } command_t;

/*
 * App can work in two modes
 * 1. Command line mode
 *    3 points passing through command line arguments when
 *    application starting. After calculations, application
 *    put the solution in os argument. (If errors occurs,
 *    then put the messages in es)
 *
 * 2. Console app mode
 *    If no arguments passed in command line, then application
 *    work with tow possible commands: solve and exit. When
 *    solve picked - application gets 3 points from is input and
 *    put solution in os output. exit command stop works. (If
 *    errors occurs, then put the messages in es)
 */

// Implements command line mode work
int command_line_mode(char *points_argv[], FILE *os, FILE *es);

// Implements console app mode work
int dispatcher(FILE *is, FILE *os, FILE *es);
int get_cmd(FILE *is);

#endif  // PROJECT_INCLUDE_DISPATCHER_H_
