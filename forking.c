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
  
  // initialize our signal handler structs as per the lecture example
  struct sigaction SIGINT_action = {{0}};
  struct sigaction SIGTSTP_action = {{0}};
  struct sigaction ignore_action =  {{0}};

  // setup the ignore handler
  ignore_action.sa_handler = SIG_IGN;
  
  // setup the signals that we would like to ignore in some cases
  sigaction(SIGINT, &ignore_action, NULL);
  sigaction(SIGTSTP, &ignore_action, NULL);
  
  // setup the SIGTSTP handler, block and flags
  SIGTSTP_action.sa_handler = handle_SIGTSTP;
  sigfillset(&SIGTSTP_action.sa_mask);
  SIGTSTP_action.sa_flags = 0;

  // setup the SIGINT handler, block and flags
  SIGINT_action.sa_handler = handle_SIGINT;
  sigfillset(&SIGINT_action.sa_mask);
  SIGINT_action.sa_flags = 0;
  
  
  // allocate space for the args array
  char** args = calloc(command->num_args + 2, sizeof(char*));

  // add the command name 
  args[0] = command->name;
  printf("arg[0] = %s\n", command->name);
  // add the args 
  size_t count = 1;
  while(count <= command->num_args) {
    args[count] = command->args[count - 1];
    printf("arg[%zu] = %s\n", count, command->name);
    count++;    
  }  

  // add the null terminator
  args[count] = '\0';
 
  // spawn the child and create status variable
  pid_t child = fork();

  // following fork/execv example from lecture
  switch(child) {
    //----------------------------------------------------------------------------------------
    // fork has failed

  case -1 : 
    perror("fork has failed\n");
    exit(1);
    break;

    //----------------------------------------------------------------------------------------
    // fork has succeeded

  case 0 :

    //printf("Background Process beginning with id %d", getpid());
    
    // setup the child as either a background or foreground process and redirect output
    command->background ? setupBackground(command) : setupForeground(command);

    //call function using exec
    execvp(args[0], args);
    
    // if we reach this point, the exec has failed, send error to stderr and set exit status
    perror("command not found\n");
    exit(1);
    break;

    //----------------------------------------------------------------------------------------
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
      if(*status == 2){
	printf("terminated by %d", *status);
      }
      printf("child = %d\n", child);
    }
    break;
    //----------------------------------------------------------------------------------------
  }
  free(args);
}
