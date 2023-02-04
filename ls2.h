#ifndef LS2_H_INCLUDED
#define LS2_H_INCLUDED

#include "stack.h"

#define TRUE 1
#define FALSE 0
#define INDENT "    "

// TODO: Function declarations here for ls2
char * fullPathName(char* path, char* name); 

void mode1(char path[], stack_t *s, int indent); 

int mode2(char path[], char targetFile[], stack_t *s, int indent);


#endif
