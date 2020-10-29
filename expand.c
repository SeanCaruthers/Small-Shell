/*
-
- a file for variable expansion functions
-
*/
#include "libraries.h"

// a function for expanding $$ in a token
void expandPID(char* token) {

  char* substring = NULL;

  // check for the $$xxxx substring
  while((substring = strstr(token, "$$"))) {
    
    // if it is found, allocate space for a pid token and copy over the process pid
    char* pid = calloc(50, sizeof(char*));

    sprintf(pid, "%d", getpid());

    // duplicate the token suffix
    char* suffix = strdup(substring + 2);

    // set the end of the prefix token at the first $ char
    *substring = '\0';
    
    // reallocate space for the new token
    // size_t len = strlen(token) + strlen(pid) + strlen(suffix);

    // concatenate the pid and suffix to the prefix 
    strcat(token, pid);
    strcat(token, suffix);

    // free the memory allocated to pid
  
    free(pid);
    free(suffix);

  }
  

}

// a function for removing new lines for the end of strings
void removeNewLines(char* token){
  while(*token) {
    if(*token == '\n') {
      *token = '\0';
    }
    token++;
  }
}
