/*
-
- a file for all of our function definitions
-
*/
struct Command* parseCommand(struct Command*);
struct Command* allocateCommand(void);
void freeCommand(struct Command*);
void printCommand(struct Command*);
