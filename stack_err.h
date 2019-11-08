#ifndef STACK_ERR_CODE
#define STACK_ERR_CODE

#define ST_FULL 2
#define ST_EMPTY 3
#define ST_NULLPTR 4
#define SUCCESS 1
#define ST_CORRUPTION 5

char ok(char code);
void decrypt(char code);

#include "stack_err.cpp"
#endif