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
  char* msg = "SIGTSTP\n";
  write(STDOUT_FILENO, msg, 8);

}
