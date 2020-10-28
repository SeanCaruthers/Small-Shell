/*
-
- A file for our built-in commands (exit, cd, status)
-
*/
#include "libraries.h"
#include "functions.h"
#include "structs.h"

// a function to check whether the command is a built in command and run it if it is
bool checkBuiltIn(struct Command* command, int* status) {

  if(!strcmp(command->name, "cd")){            
    changeDir(command);
    return true;
  }
  else if(!strcmp(command->name, "exit")){                                                                               
    exitProgram(command);
  }                                         
  else if(!strcmp(command->name, "status")){                                                                            
    checkStatus(status);                                                                                                 
    return true;
  }
  return false;
}


void exitProgram(struct Command* command) {
  freeCommand(command);                 
  exit(1);
}

// a function for changing the PWD to a specified directory
void changeDir(struct Command* command) {

  char* path = command->args[0];

  // if no args, set PWD to HOME
  if(!path) {
    setenv("PWD", getenv("HOME"), true);
  } 
  // otherwise set to relative or absolute path stated
  else {
    // if path is absolute
    if(*path == '/') {
      setenv("PWD", path, true);
    }
    // if path is relative to pwd, merge the pwd with the specified path and set it to the env
    else if(*path != '.' || (*path  == '.' && *(path + 1) == '/')) {
      setRelativeToPWD(path);
    }
    // if path is relative to parent of pwd, merge parent with pwd and set to env
    else if(*path == '.' && *(path + 1) == '.') {
      setRelativeToParent(path);
    }
    
  }
}

// check exit status of last foreground process using macros as in the termination status lecture
void checkStatus(int* status) {
  if(WIFEXITED(*status)) {
    printf("Exit value %d\n", WEXITSTATUS(*status));
  }
  else{
    printf("Exit value %d\n", WTERMSIG(*status));
  }
}
