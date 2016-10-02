#ifndef _MYMALLOC_H_
#define _MYMALLOC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define malloc(x) myMalloc(x, __FILE__, __LINE__)
#define free(x) myFree(x, __FILE__, __LINE__)

typedef enum boolean_ {false, true} boolean;

typedef struct memEntry_ {
	boolean occupied; //returns 0 if block is not occupied, 1 if occupied
	unsigned int memAmount; //size of variable
	struct memEntry_ *prev;
	struct memEntry_ *next;
} memEntry;

void* myMalloc(unsigned int memAmount, char* filename, unsigned int linenum);
void* myFree(void * ptr, char* filename, unsigned int linenum);

#endif
