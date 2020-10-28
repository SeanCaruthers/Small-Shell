/* 
-
-  SMALLSH - main function
-
*/
#include "libraries.h"
#include "functions.h"
#include "structs.h"
#define PROMPT ":"

int main(void){

  // bool for while loop (keep it structured)
  bool running = true;         
  
  // status variable for tracking the last exit status
  int* status;
  int stat = 0;
  status = &stat;
  
  

  // keep our program running 
  while(running){              
    
    // 1. Provide a prompt for running commands
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
    
    // allocate space for our command struct                                       
    struct Command* command = allocateCommand();
    
    // pass the struct to the parse Command method to fill in the attributes
    command = parseCommand(command);
    
    // 2. Handle blank lines and comments beginning with #
    if(!command->name || *command->name == '#') {
      freeCommand(command);
      continue;
    }
    
    // 3. Provide expansion for the variable $$
    pidExpandAttributes(command);
    
    // remove new lines that cause bugs at the end of commands
    removeNewLinesFromAttributes(command);

    // 4. Execute 3 commands: exit, cd and status
    //printCommand(command);
    
    // check to see if the command is a built in command (execute and continue if it is)
    if(checkBuiltIn(command, status)){
      freeCommand(command);
      continue;
    }
    
    // 5. Execute other commands by creating new processes using exec
    forkCommand(command, status);
    
    // 6. Support input and output redirection
    
    // 7. Support running foreground and background processes
    
    // 8. Implement custom handlers for SIGINT and SIGTSTP
    freeCommand(command);
  } 
}

