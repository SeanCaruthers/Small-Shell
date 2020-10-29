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
  
  // create variables for strtok_r
  char* bookmark;
  char* token;

  size_t index = 0;


  // read a line of input from stdin
  while(!*line){
    //printf("Attempting to get line\n");
    getline(&line, &len, stdin);
    //printf("read %zu chars from stream.\n", check);
  }

  // parse the command name, allocate memory for it in the struct 
  token = strtok_r(line, DELIM, &bookmark);
  command->name = token ? strdup(token) : NULL;

  // parse tokens from the line until the newline
  while((token = strtok_r(NULL, DELIM, &bookmark))) {

    // check for input redirection token and copy input filename to attribute if so
    if((*token) == '<') {
      token = strtok_r(NULL, DELIM, &bookmark);
      if(token != NULL){
	command->input = token ? strdup(token) : NULL;
      }
      
    }

    // check for output redirection token and copy output filename to attribute if so
    else if((*token) == '>') {      
      token = strtok_r(NULL, DELIM, &bookmark);
      if(token != NULL){
	command->output = token ? strdup(token) : NULL;
      }
    }

    // check for background ampersand and set command struct's background variable to true
    else if((*token) == '&') {
      command->background = true;
    }  

    // otherwise token is an command argument, add argument to command structs argument array
    else {
      if(token != NULL){
	char* arg = calloc(strlen(token) + 5, sizeof(char));
	strcpy(arg, token);
	command->args[index] = arg;
	command->num_args++;
	index++;
      }
    }
  }

  command->args[index] = NULL;
  // free the space allocated for input
  free(line);


  // return our command filled with parsed information
  return command;
}
