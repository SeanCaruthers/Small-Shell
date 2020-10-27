/*
-
- A file for declaring all of our structs
-
*/
#include "libraries.h"
#define MAX_ARGS 512

struct Command {
  char* name;                           // command name
  char* args[MAX_ARGS];                 // command arguments
  char* input;                          // input file's name
  char* output;                         // output file's name
  bool background;                      // boolean fg = 1, bg = 0 process locaiton
};
