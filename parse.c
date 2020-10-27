/*
-
- A file for parsing related functions
-
*/
#include "libraries.h"
#include "functions.h"
#include "structs.h"
#define MAX_LINE 2048
#define DELIM "' '"

// a function for parsing user commands
struct Command* parseCommand(struct Command* command) {
  
  // allocate space for a line of input
  size_t len = MAX_LINE;
  char* line = calloc(len, sizeof(char));

  // read a line of input from stdin
  getline(&line, &len, stdin);
  
  // create variables for strtok_r
  char* bookmark;
  char* token;
  size_t index = 0;

  // parse the command name, allocate memory for it in the struct and expand the variable $$ if necessary
  command->name = strdup(strtok_r(line, DELIM, &bookmark));

  // parse tokens from the line until the newline
  while((token = strtok_r(NULL, DELIM, &bookmark))) {

    // check for input redirection token 
    if((*token) == '<') {
      // if input redirection, copy input filename to command struct's input attribute
      command->input = strdup(strtok_r(NULL, DELIM, &bookmark));
    }

    // check for output redirection token
    else if((*token) == '>') {      
      // if output redirection, copy output filename to command struct's output variable
      command->output = strdup(strtok_r(NULL, DELIM, &bookmark));
    }

    // check for background ampersand
    else if((*token) == '&') {
      // if background ampersand, set command struct's background variable to true
      command->background = true;
    }  

    // otherwise token is an command argument
    else {
      // add argument to command structs argument array
      command->args[index] = strdup(token);
      index++;
    }
  }
  

  // free the space allocated for input
  free(line);

  // return our command filled with parsed information
  return command;
}
