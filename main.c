/* 
-
-  SMALLSH - main function
-
*/
#include "libraries.h"
#include "functions.h"
#include "structs.h"
#define PROMPT ":"
bool bg_mode = true;

int main(void){
  
  // initialize the default ignore signal struct                                                             
  struct sigaction ignore_action = {{0}};

  // setup the SIGINT and SIGTSTP ignore function                                                            
  ignore_action.sa_handler = SIG_IGN;
  sigaction(SIGINT, &ignore_action, NULL);
  sigaction(SIGTSTP, &ignore_action, NULL);

  // bool for while loop (keep it structured)
  bool running = true;         
  
  // status variable for tracking the last exit status
  int* status;
  int stat = 0;
  status = &stat;

  // linked list for holding open processes
  struct LL* open_pid = createLL();
  
  // keep our program running 
  while(running){              

    // check for open background processes that have terminated
    checkOpenPID(open_pid);

    // 1. Provide a prompt for running commands
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
    
    // allocate space for our command struct                                       
    struct Command* command = allocateCommand();
    
    // pass the struct to the parse Command method to fill in the attributes
    command = parseCommand(command);
        
    // 3. Provide expansion for the variable $$
    pidExpandAttributes(command);    

    // remove new lines that cause bugs at the end of commands
    removeNewLinesFromAttributes(command);

    // 2. Handle blank lines and comments beginning with #
    if(!strlen(command->name) || *command->name == '#') {
      freeCommand(command);
      continue;
    }

    // 4. Execute 3 commands: exit, cd and status    
    // check to see if the command is a built in command (execute and continue if it is)
    if(checkBuiltIn(command, status, open_pid)){
      freeCommand(command);
      continue;
    }
    
    // 5. Execute other commands by creating new processes using exec
    // 6. Support input and output redirection
    // 7. Support running foreground and background processes
    // 8. Implement custom handlers for SIGINT and SIGTSTP
    forkCommand(command, status, open_pid);
    
    freeCommand(command);
  } 
}

