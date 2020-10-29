/*
-
- A file for all functions related to forking
-
*/
#include "libraries.h"
#include "functions.h"
#include "structs.h"


// a function for forking the command sent to it
void forkCommand(struct Command* command, int* status, struct LL* open_pid) {
  extern volatile bool bg_mode;

  
  // initialize the default ignore signal struct
  struct sigaction SIGTSTP_action = {{0}};
  struct sigaction ignore_action = {{0}};

  ignore_action.sa_handler = SIG_IGN;

  // allocate and create an array of args for the exec function
  char** args = commandArgsArray(command);
  
  // spawn the child and create status variable
  pid_t spawn = fork();
  
  // create pid_t pointer
  pid_t* child;
  child = &spawn;

  // following fork/execv example from lecture
  switch(spawn) {
    //----------------------------------------------------------------------------------------
    // fork has failed
  case -1 : 
    perror("fork has failed\n");
    exit(1);
    break;
    //----------------------------------------------------------------------------------------
    // fork has succeeded
  case 0 :
    sigaction(SIGTSTP, &ignore_action, 0);
    
    // setup the spawn as either a background or foreground process and redirect output
    (bg_mode && command->background) ? childBackground(command, child, open_pid) : childForeground(command, child);
    //command->background ? childBackground(command, child, open_pid) : childForeground(command, child);
 
    //call function using exec
    execvp(args[0], args);
    
    // if we reach this point, the exec has failed, send error to stderr and set exit status
    perror("command not found\n");
    exit(1);
    break;

    //----------------------------------------------------------------------------------------
    // parent process path
  default :
 
    // setup the SIGTSTP handler, block and flags for changing background mode                                                                                      
    SIGTSTP_action.sa_handler = handle_SIGTSTP;
    sigfillset(&SIGTSTP_action.sa_mask);
    SIGTSTP_action.sa_flags = SA_RESTART;
    sigaction(SIGTSTP, &SIGTSTP_action, NULL);

    // if spawn process is running in the background send parent to foreground
    (bg_mode && command->background) ? parentForeground(command, child, status, open_pid) : parentBackground(command, child, status);
    //command->background ? parentForeground(command, child, status, open_pid) : parentBackground(command, child, status);
    break;
    //----------------------------------------------------------------------------------------
  }
  free(args);
}

// a function for ending all child processes
void endChildProcesses(struct LL* linked){
  
  struct Node* current = linked->head;
  while(current) {
    kill(current->pid, SIGTERM);
    current = current->next;
  }
}
