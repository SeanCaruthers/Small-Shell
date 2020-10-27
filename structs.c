
#include "libraries.h"
#include "functions.h"
#include "structs.h"

// a function for allocating space for our Command struct
struct Command* allocateCommand(void) {
  struct Command* command = calloc(1, sizeof(struct Command));
  command->name = NULL;
  command->input = NULL;
  command->output = NULL;
  command->background = true;
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
