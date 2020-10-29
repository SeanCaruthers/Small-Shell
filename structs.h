/*
-
- A file for declaring all of our structs
-
*/
#include "libraries.h"
#define MAX_ARGS 512

// setup our command struct
struct Command{
  char* name;                           // command name
  char* args[MAX_ARGS];                 // command arguments
  size_t num_args;                      // variable for holding the number of arguments
  char* input;                          // input file's name
  char* output;                         // output file's name
  bool background;                      // boolean fg = 1, bg = 0 process locaiton
};

// setup our Node struct
struct Node{
  pid_t pid;
  struct Node* next;
};
  
// setup our linked list struct
struct LL{
  struct Node* head;
  struct Node* tail;
};

