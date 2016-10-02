#include "mymalloc.h"

//global mem array
static char memBlock[5000];

#define maxNumEntries (5000/(sizeof(memEntry) + 1))
//in order to keep track of how many memEntries we've created we have an array of 
//memEntry pointers. The max number of structs we can have is given by 5000 (our max 
//number of bytes) divided by the sizeof memEntry + 1 for a minimum memory size of 1. 
//That is to say, memEntries is designed to hold the maximum number of memEntry 
//structs pointers possible. This is used for free when checking to ensure that we 
//are freeing a valid pointer, if its found in our array
static memEntry* memEntries[maxNumEntries] = {0};


void* myMalloc(unsigned int memAmount, char* filename, unsigned int linenum) {
	//first ensure at least 1 byte is requested
	if(memAmount <= 0) {
		fprintf(stderr, "File %s, line %d: unable to provide 0 or fewer bytes.\n", filename, linenum);
		return 0;
	}

	//if this is the first time malloc is called, we need to create a 'base' struct
	//that will hold all of our available memory in a memEntry struct (5000 bytes -
	//sizeof(memEntry)) and mark it as free available memory to be used by malloc 
	
	//static means this variable's value will stay constant with respect to function
	//calls. If it's changed to true, then future calls to malloc will consider this
	//boolean as true, likewise for false
	static boolean initCall = true; 
	static memEntry *base = NULL;	
	
	//creating base struct that will initially hold all our free memory
	if(initCall == true) { //only happens on the first call to malloc
		//char * head = ALLMEM
		//MemEntry * construct = (MemEntry*) head;
		base = (memEntry*) memBlock;
		base->memAmount = 5000 - sizeof(memEntry);
		/*
		printf("%d\n", sizeof(memEntry)); //24 bytes
		printf("%d\n", sizeof(*base)); //24 bytes
		*/
		base->occupied = false;
		base->next = NULL;
		base->prev = NULL;

		initCall = false;
	}
	//now we have a base struct that is 24 bytes followed by 5000-24 bytes of free
	//memory.

	memEntry *head = NULL;
	//loop through all our available memEntries searching for one that has
	//enough memory for the requested amount	
	for(head = base; head != NULL; head = head->next) {
		//for every memEntry we need to compare its memAmount with requested
		
		//first check if memEntry is free memory, else, can't use it
		if(head->occupied == true) {
			continue;
		}

		//here we know memory is unoccuppied
		//three cases: 1) not enough memory
		if(head->memAmount < memAmount) {
			continue;
		}
		//2)enough memory for request but not enough to make a new memEntry
		//with at least 1 byte of memory for malloc
		else if((head->memAmount < (sizeof(memEntry) + memAmount + 1))
				&& (head->memAmount >= memAmount)) {
			head->occupied = true;
			//leave prev and next alone, since new struct aint being created
		
			//everytime a memEntry is returned by malloc
			//we need to append its pointer to our
			//memEntries array, so when we want to free something, we can check our
			//memEntries array to ensure our malloc funct was what provided the mem
			int i = 0;
			for(i = 0; i < maxNumEntries; i++) {
				if(memEntries[i] == 0) {
					memEntries[i] = head;	
					break;
				}
			}
			//get address of struct and displace by size of struct in order
			//to reference the memory itself
			return (char *)head + sizeof(memEntry);
		}
		//3) enough mem for request and new memEntry with at least 1 byte of mem
		else {
			//need to splice up current memEntry, thus creating a new
			//memEntry and returning requested memory
			
			//next memEntry is at addresss (address of current memEntry +
			//size of memEntry + size of memory requested).
			memEntry *new = (memEntry*)((char*)head + sizeof(memEntry) + memAmount);
			//now attach new memEntry to our linked list
			//first make new point to current struct's next
			new->next = head->next;
			//now update current struct's next to point to new struct
			head->next = new;
			//finally, update new's prev pointer to point to current struct
			new->prev = head;

			//now that the new struct is placed in, need to instantiate vals
			new->occupied = false;
			//available memory is all the memory taken by the current 
			//memEntry - memAmount - sizeof(newmemEntry).
			new->memAmount = head->memAmount - memAmount - sizeof(memEntry);

			//need to indicate that our current memEntry is going to be 
			//returned by malloc
			head->occupied = true;

			//plus update memAmount to indicate how much memory of all the 
			//available memory this struct is left with after splice 
			head->memAmount = memAmount;
		
	
			//insert pointer to the memEntry being returned to array for when
			//needed for free referencing
			int i = 0;
			for(i = 0; i < maxNumEntries; i++) {
				if(memEntries[i] == 0) {
					memEntries[i] = head;	
					break;
				}
			}

			return (char *)head + sizeof(memEntry);
		}
	}
	//the only time we would finish our loop is when we could not allocate the
	//requested memory	
	fprintf(stderr, "File %s, line %d: unable to provide requested bytes.\n", filename, linenum);
	return NULL;	
}



void* myFree(void * ptr, char* filename, unsigned int linenum) {

	return;

}



