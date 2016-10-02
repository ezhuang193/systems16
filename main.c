#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mymalloc.h"

int main(int argc, char** argv) {
	void* ptr = malloc(3);
	//free(ptr);
	void* ptrr = malloc(4);
	//free(ptrr);
	return 0;
}

