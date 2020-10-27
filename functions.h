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
bool checkBuiltIn(struct Command* command); 
void changeDir(struct Command* command); 
void checkStatus(struct Command* command);
void exitProgram(struct Command* command); 
char* mergePaths(char*, char*);
void setRelativeToPWD(char*);
void setRelativeToParent(char*);
