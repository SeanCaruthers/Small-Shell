/*
-
- a file for redirection functions
-
*/ 
#include "libraries.h"
#include "structs.h"

// a function for redirecting input to the specified filehandle using example from lecture
void redirectInput(char* filehandle) {
  int infile = open(filehandle, O_RDONLY);
  if(infile == -1) {
    perror("error opening infile");
    exit(1);
  }

  int redirect = dup2(infile, STDIN_FILENO);
  if(redirect == -1) {
    perror("error redirecting input");
    exit(2);
  }
}

// a function for redirecting output to the specified filehandle using example from lecture
void redirectOutput(char* filehandle) {
  printf("filehandle = %s", filehandle);
  // open outfile with specified flags
  int outfile = open(filehandle, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if(outfile == -1) {
    perror("Error in opening file");
    exit(1);
  }
  
  // redirect output
  int redirect = dup2(outfile, STDOUT_FILENO);
  if(redirect == -1 ) {
    perror("Error in redirection");
    exit(2);
  }
  
}
