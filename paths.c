/*
-
- a file for path functions
-
*/
#include "libraries.h"
#define BUFFSIZE 2048

// a function for merging a path prefix and relative suffix
char* mergePaths(char* prefix, char* suffix) {

  // slash for use in checks
  char* slash = "/";

  // allocate a char* that will point to a string prefix/suffix directory filepath
  char* new_pwd = calloc(strlen(prefix) + strlen(slash) + strlen(suffix) + 2, sizeof(char));
  
  // validate copy the prefix into the beginning of the directory filepath
  if(*prefix) {
    strcat(new_pwd, prefix);
  }

  // ensure that there is a suffix
  if(suffix){

    
    // --------------- Ensure that exactly one slash will exist between the prefix and suffix.
    
    // iterate the prefix char pointer until it reaches the last character
    while(*(prefix+1)) { prefix++; };
    
    // case 1 - prefix ends in a slashe and suffix begins with a slash
    if(*prefix == '/' && *suffix == '/') {

      // iterate the suffix pointer so that only one slash is used
      suffix++;
      
    }
    
    // case 2 - neither prefix nor suffix have a slash
    else if (*prefix != '/' && *suffix != '/') {
      
      // add a slash on to the prefix
      strcat(new_pwd, slash);
            

    }
    
    // cases 1 & 2 
    // cases 3 & 4 add suffix to the project working directory to finish
    strcat(new_pwd, suffix);  

  }
  
  // return the project working directory in an allocated string
  return new_pwd;
}

// set path relative to the PWD
void setRelativeToPWD(char* path) {
  
  //printf("Entering func setRelativeToPWD in paths.c");
  
  // get a ptr to a buffer allocated in the appropriate size for the current working directiory
  char* prefix = calloc(BUFFSIZE, sizeof(char));
  getcwd(prefix, BUFFSIZE);
  
  //printf("old directory = %s\n", prefix);

  /* 
     If the path starts with a period, 
     move the pointer two steps to the right
     so that the char* points at the beginning of the directory name
  */
  char* suffix = ((*path == '.') ? path+2: path);

  // allocate memory for a char* that points to the merged prefix/suffix directory filepath
  char* new_pwd = mergePaths(prefix, suffix);

  //printf("new directory = %s\n", new_pwd);
  // change directories to the new pwd
  chdir(new_pwd);

  // free the memory allocated for the new pwd
  free(prefix);
  free(new_pwd);
}


// set path relative to a parent directory
void setRelativeToParent(char* suffix){
  
  //printf("Entering func setRelativeToParent in paths.c");
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
  
  // get a ptr to a buffer allocated in the appropriate size for the current working directiory
  char* prefix = calloc(BUFFSIZE, sizeof(char));
  getcwd(prefix, BUFFSIZE);
  
  char* start = prefix;
  char * end = prefix;
  //printf("old directory = %s\n", prefix);

  //iterate to end of current path and back up one charater
  while(*end) { end++; };
  end--;

  // iterate step times
  while(step) {
    
    // remove the child directory name from the path name
    if(*end == '/') { end--; };
    while(*end != '/') { 
      end--;
    };
    end--;
    step--;   
  }
  
  // add a null terminator
  end++;
  *end = '\0';  

  // merge the prefix and suffix, set the environment and free the path string
  char* new_pwd = mergePaths(start, suffix);
  //printf("new directory = %s\n", new_pwd);
  chdir(new_pwd);
  free(prefix);
  free(new_pwd);
}
