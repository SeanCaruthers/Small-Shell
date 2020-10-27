
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
  printf("Command name : ");
  if(command->name) {
    printf("%s\n", command->name);
  }
  else {
    printf("None\n");
  }
  printf("Command input : ");
  if(command->input) {
    printf("%s\n", command->input);
  }
  else {
    printf("None\n");
  }
  printf("Command output : ");
  if(command->output) {
    printf("%s\n", command->output);
  }
  else {
    printf("None\n");
  }
  size_t index = 0;
  printf("Command Arguments");
  while(command->args[index]){
    printf(", %s", command->args[index]);
    index++;
  }
  
  printf("\nProcess type: %s\n", command->background ? "Background" : "Foreground");
  
  
}
