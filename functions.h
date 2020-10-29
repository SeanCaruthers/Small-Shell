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
void changeDir(struct Command*); 
void checkStatus(int*);
char* mergePaths(char*, char*);
void setRelativeToPWD(char*);
void setRelativeToParent(char*);
void redirectInput(char*);
void redirectOutput(char*);
void childForeground(struct Command*, pid_t*);
void parentBackground(struct Command*, pid_t*, int*);
void handle_SIGINT(int);
void handle_SIGTSTP(int);
void handle_SIGCHLD(int);
char** commandArgsArray(struct Command*);
struct Node* createNode(void);
struct LL* createLL(void);
void parentForeground(struct Command*, pid_t*, int*, struct LL*);
struct Node* addNode(struct LL*, struct Node*);
void removeNode(struct LL*, struct Node*);
void printLL(struct LL*);
void freeLL(struct LL*);
void checkOpenPID(struct LL*);
bool checkBuiltIn(struct Command*, int*, struct LL*); 
void childBackground(struct Command*, pid_t*, struct LL*);
void forkCommand(struct Command*, int*, struct LL*);
void exitProgram(struct Command*, struct LL*); 
void endChildProcesses(struct LL*);
