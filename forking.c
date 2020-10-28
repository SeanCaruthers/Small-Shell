/*
-
- A file for all functions related to forking
-
*/
#include "libraries.h"
#include "functions.h"
#include "structs.h"

// a function for forking the command sent to it
void forkCommand(struct Command* command, int* status) {
  
  // initialize our signal handler
  struct sigaction SIGINT_action = {0}, SIGTSTP_action = {0}, ignore_action = {0};
  sigaction(SIGINT, &ignore
  SIGINT_action.sa_handler = handle_SIGINT;
  sigfillset(&SIGINT_action.sa_mask);
  SIGINT_action.sa_flags = 0;
  
  
  // allocate space for the args array
  char** args = calloc(command->num_args + 2, sizeof(char*));

  // add the command name 
  args[0] = command->name;

  // add the args 
  size_t count = 1;
  while(count <= command->num_args) {
    args[count] = command->args[count - 1];
    count++;    
  }  

  // add the null terminator
  args[count] = '\0';
 
  // spawn the child and create status variable
  pid_t child = fork();

  // following fork/execv example from lecture
  switch(child) {
    // fork has failed
  case -1 : 
    perror("fork has failed\n");
    exit(1);
    break;
    // fork has succeeded
  case 0 :

    printf("Background Process beginning with id %d", getpid());

    // redirect our input and output
    char* secret = "/dev/null";
    command->input ? redirectInput(command->input) : redirectInput(secret);
    command->output ? redirectOutput(command->output) : redirectInput(secret);
    
    //call function using exec
    execvp(args[0], args);
    
    // if we reach this point, the exec has failed, send error to stderr and set exit status
    perror("command not found\n");
    exit(1);
    break;

    // parent process path
  default :
    
    // run the process in the background
    if(command->background) {
      int dummy;
      child = waitpid(child, &dummy, WNOHANG);

    }
    // otherwise wait for the foreground process and update the status
    else { 
      child = waitpid(child, &(*status), 0);
      printf("child = %d\n", child);
    }
    break;
  }
  free(args);
}
