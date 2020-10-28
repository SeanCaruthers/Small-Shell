/*
-
- a file for holding our background vs. foreground functions
-
*/
#include "libraries.h"
#include "functions.h"
#include "structs.h"

void setupBackground(struct Command* command) {
  char* secret = "/dev/null";
  command->input ? redirectInput(command->input) : redirectInput(secret);
  command->output ? redirectOutput(command->output) : redirectInput(secret);
}   

void setupForeground(struct Command* command) {
  // setup the SIGINT handler, block and flags                                                                
  SIGINT_action.sa_handler = handle_SIGINT;
  sigfillset(&SIGINT_action.sa_mask);
  SIGINT_action.sa_flags = 0;

  command->input ? redirectInput(command->input) : NULL;
  command->output ? redirectOutput(command->output) : NULL;
}
