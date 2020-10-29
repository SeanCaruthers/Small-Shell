/*
-
- a file for path functions
-
*/
#include "libraries.h"

// a function for merging a path prefix and relative suffix
char* mergePaths(char* prefix, char* suffix) {

  char* slash = "/";
  char* new_pwd = calloc(strlen(prefix) + strlen(slash) + strlen(suffix) + 1, sizeof(char *));
  strcat(new_pwd, prefix);
  // ensure that there is a suffix
  if(suffix){

    // ensure that the prefix does not end in a slash
    char* check = prefix;
    while(*check) { check++; };
    check--;
    if(*check != '/') {
      // concatenate the string
      strcat(new_pwd, slash);
    }
    strcat(new_pwd, suffix);
  }
  return new_pwd;
}

// set path relative to the PWD
void setRelativeToPWD(char* path) {
  char* prefix = getenv("PWD");
  char* suffix = ((*path == '.') ? path+2: path);
  char* new_pwd = mergePaths(prefix, suffix);
  chdir(new_pwd);
  free(new_pwd);
}


// set path relative to a parent directory
void setRelativeToParent(char* suffix){

  // var for storing how many step up to take
  size_t step = 0;

  // continue while moving up in prefixectories
  while(*suffix == '.'){
    suffix += 2;
    if(*suffix == '/') {
      suffix++;
    }
    step++;
  }

  // grab the current working prefixectory
  char* prefix = getenv("PWD");
  char* start = prefix;

  //iterate to end of current path and back up one charater
  while(*prefix) { prefix++; };
  prefix--;

  // iterate step times
  while(step) {
    
    // remove the child directory name from the path name
    if(*prefix == '/') { prefix--; };
    while(*prefix != '/') { 
      prefix--;
    };
    prefix--;
    step--;   
  }
  
  // add a null terminator
  prefix++;
  *prefix = '\0';  

  // merge the prefix and suffix, set the environment and free the path string
  char* new_pwd = mergePaths(start, suffix);
  chdir(new_pwd);
  free(new_pwd);
}
