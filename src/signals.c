/*
-
- a file for signals handling functions
-
*/
#include "libraries.h"


// our sigint handler
void handle_SIGINT(int signo) {
  char* msg = "SIGINT\n";
  write(STDOUT_FILENO, msg, 7);
  exit(signo);
}


// our sigtstp handler
void handle_SIGTSTP(int signo) {
  extern volatile bool bg_mode;
  if(bg_mode) {
    char* msg = "Entering Foreground only mode (& is now ignored)\n";
    write(STDOUT_FILENO, msg, 49);
    bg_mode = false;
  }
  else {
    char* msg = "Exiting Foreground only mode\n";
    write(STDOUT_FILENO, msg, 30);
    bg_mode = true;
  }
}



