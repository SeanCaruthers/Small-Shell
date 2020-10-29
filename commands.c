
#include "libraries.h"
#include "functions.h"
#include "structs.h"

// a function for allocating space for our Command struct
struct Command* allocateCommand(void) {
  struct Command* command = calloc(1, sizeof(struct Command));
  command->name = NULL;
  command->input = NULL;
  command->output = NULL;
  command->background = false;
  command->num_args = 0;
  return command;
}

// a function for freeing all space allocated to the Command struct
void freeCommand(struct Command* command){
  if(command->name) {
    free(command->name);
  }
  if(command->input) {
    free(command->input);
  }
  if(command->output) {
    free(command->output);
  }
  size_t index = 0;
  while(command->args[index]){
    free(command->args[index]);
    index++;
  }
  free(command);
}


// a function for printing our command struct
void printCommand(struct Command* command) {
  
  char* default_msg = "None specified";
  printf("\n\nCommand name   : %s\n", command->name ? command->name : default_msg);
  printf("Command input  : %s\n", command->input ? command->input : default_msg);
  printf("Command output : %s\n", command->output ? command->output : default_msg);
  
  size_t index = 0;
  printf("Command Arguments : %s", command->args[index] ? command->args[index++] : default_msg);
  while(command->args[index]){
    printf(", %s", command->args[index++]);
  }  
  printf("\nProcess type  : %s\n", command->background ? "Background" : "Foreground");  
  
}


// function for expanding the $$ string in command attributes
void pidExpandAttributes(struct Command* command){
  command->name ? expandPID(command->name) : NULL;
  command->input ? expandPID(command->input) : NULL;
  command->output ? expandPID(command->output) : NULL;

  size_t index = 0;
  while(command->args[index]) {
    expandPID(command->args[index]);
    index++;
  }
}


void removeNewLinesFromAttributes(struct Command* command){
  
  command->name ? removeNewLines(command->name) : NULL;
  command->input ? removeNewLines(command->input) : NULL;
  command->output ? removeNewLines(command->output) :NULL;

  size_t index = 0;
  while(command->args[index]) {
    removeNewLines(command->args[index]);
    index++;
  }

}


// a function for formatting command args into an array suitable for exec functions
char** commandArgsArray(struct Command* command) {

  // allocate space for our arguments
  char** args = calloc(command->num_args + 2, sizeof(char*));

  // add the command name                                                                                              
  args[0] = command->name;
  //printf("arg[0] = %s\n", command->name);
  // add the args                                                                                                       
  size_t count = 1;
  while(count <= command->num_args) {
    args[count] = command->args[count - 1];
    //printf("arg[%zu] = %s\n", count, command->name);
    count++;
  }

  // add the null terminator                                                                                           
  args[count] = '\0';

  return args;
}
