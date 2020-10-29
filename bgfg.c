/*
-
- a file for holding our background vs. foreground functions
-
*/
#include "libraries.h"
#include "functions.h"
#include "structs.h"


// a function for setting up child processes in the background
void childBackground(struct Command* command, pid_t* child, struct LL* open_pid) {
 
  // get the process id and print message
  pid_t pid = getpid();
  printf("background pid is %d\n", pid);
  
  // redirect I/O to /dev/null or the specified src/dest
  char* secret = "/dev/null";
  command->input ? redirectInput(command->input) : redirectInput(secret);
  command->output ? redirectOutput(command->output) : redirectInput(secret);  
  
}   


// a function for setting up child processes in the foreground
void childForeground(struct Command* command, pid_t* child) {

  // initialize the SIGINT action struct
  struct sigaction SIGINT_action = {{0}};
  
  // setup the SIGINT handler, block and flags 
  SIGINT_action.sa_handler = handle_SIGINT;
  sigfillset(&SIGINT_action.sa_mask);
  SIGINT_action.sa_flags = 0;

  // install the signal handler
  sigaction(SIGINT, &SIGINT_action, NULL);

  // redirect input if specified
  command->input ? redirectInput(command->input) : NULL;
  command->output ? redirectOutput(command->output) : NULL;
}

// a function for handle parent processes running in the foreground
void parentForeground(struct Command* command, pid_t* child, int* status, struct LL* open_pid) {

  // create a process node, add pid to it and add it to link list                                                                                                                                                          
  struct Node* node = createNode();
  node->pid = *child;
  addNode(open_pid, node);

}

// a function for handle parent processes running in the background
void parentBackground(struct Command* command, pid_t* child, int* status) {
  // wait for the foreground child to stop               
  *child = waitpid(*child, &(*status), 0);
  
  // if foreground child is killed by SIGINT, print out termination status                   
  if(*status == 2){
    printf("terminated by %d\n", *status);
  }

}


// a function for checking the open processes
void checkOpenPID(struct LL* open_pid){

  struct Node* current = open_pid->head;
  
  // iterate through the list of open processes
  while(current){
    
    // check for process termination
    int* statusptr;
    int status = 0;
    statusptr = &status;

    
    pid_t pid = waitpid(current->pid, &status, WNOHANG);
    current = current->next;    
    switch(pid){
    case -1:
      perror("invalid pid ");
      break;
    case 0 :
      break;
    default:
      // print termination message and remove process from list of open processes
      printf("background pid %d is done: ", current->pid);
      checkStatus(statusptr);
      removeNode(open_pid, current);
      break;
    }
    
    //printf("current = %d\t current->next = %d", current->pid, current->next->pid);

    
  }
}
