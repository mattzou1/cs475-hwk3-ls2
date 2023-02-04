#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "ls2.h"

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char* argv[]) {
	// stack stores the lines to print out
	stack_t *s = initstack();

	// push(s, "Hello1");
	// push(s, "Hello2");
	// push(s, "Hello3");

	if(argv[1] == NULL){
		printf("Please enter path\n");
	}
	else if(argv[2] == NULL){
		mode1(argv[1], s, 0);
	}
	else{
		mode2(argv[1], argv[2], s, 0);
	}
	

	// print stack
	printstack(s);

	// free up stack
	freestack(s);	
	return 0;
}
