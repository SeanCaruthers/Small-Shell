/*
-
- a file for all of our function definitions
-
*/
struct Command* parseCommand(struct Command*);
struct Command* allocateCommand(void);
void freeCommand(struct Command*);
void printCommand(struct Command*);
void expandPID(char *);
void pidExpandAttributes(struct Command*);
void removeNewLinesFromAttributes(struct Command*);
void removeNewLines(char*);
bool checkBuiltIn(struct Command*, int*); 
void changeDir(struct Command*); 
void checkStatus(int*);
void exitProgram(struct Command*); 
char* mergePaths(char*, char*);
void setRelativeToPWD(char*);
void setRelativeToParent(char*);
void forkCommand(struct Command*, int*);
void redirectInput(char*);
void redirectOutput(char*);
