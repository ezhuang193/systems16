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
		return NULL;
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
	if(ptr == NULL) {
		fprintf(stderr, "File %s, line %d: unable to free a null pointer.\n", filename, linenum);	
		return;
	}

	//The address of our ptr minus the size of our memEntry should give us a pointer
	//to the memEntry struct from which we can check if valid
	memEntry* toFree = (memEntry*) ((char *) ptr - sizeof(memEntry));

	//we know that our malloc function has added the pointer of every memEntry
	//it has ever created in our memEntries array which is global. All we need
	//to do is ensure that our current toFree pointer has an address that is 
	//found within this array 
	int i = 0;
	for(i = 0; i < maxNumEntries; i++) {
		if(toFree == memEntries[i]) {
			//now we need to free this memory block
			//there are 4 cases: Prev and Next blocks are free,
			//prev is free, but next isn't, and vice versa OR no neighbors
			//are free
			if(toFree->prev != NULL
					&& toFree->prev->occupied == false) {

				if(toFree->next != NULL
				 && toFree->next->occupied == false) {
					//here prev and next memEntry can merge
					//first remove curr memEntry from glob array
					//and make unoccupied
					memEntries[i] = 0;
					toFree->occupied = false;
					//get number of bytes to merge from next
					unsigned int memToMerge = sizeof(memEntry) + (toFree->next->memAmount);
					//update amount current memEntry memory	
					toFree->memAmount += memToMerge;
					//update linked list
					toFree->next = toFree->next->next;

					//here, next was merged with current memEntry
					//now need to merge current memEntry with prev
					//memEntry
					memToMerge = sizeof(memEntry) + (toFree->memAmount);
					toFree->prev->memAmount += memToMerge;
					toFree->prev->next = toFree->next;
					
					//done, next was merged with curr and then curr
					//was merged with prev
				}
				//here prev can merge, but not next

				//get size of total memory consumed by current memEntry 
				unsigned int memToMerge = sizeof(memEntry) + (toFree->memAmount);
				//need to removed from glob array because free
				memEntries[i] = 0;
				toFree->occupied = false; //just for good measure

				//add memToMerge to prev free struct's memAmount
				toFree->prev->memAmount += memToMerge;	
				//make prev struct point to curr struct's next
				toFree->prev->next = toFree->next;

				//done, prev is already unlisted from glob array and
				//is shown as unoccupied so nothing left to do
			}
			else if(toFree->next != NULL
				&& toFree->next->occupied == false) {
				//here, prev can't merge, but next can merge
				
				//first need to get total memory consumed by next
				unsigned int memToMerge = sizeof(memEntry) + (toFree->next->memAmount);
				//now we don't need to remove the ->next struct from the
				//global array because array contains only structs that 
				//are currently being occupied (i.e. returned by malloc)
				
				//now update the currents struct to add this memory to
				//its size
				toFree->memAmount += memToMerge;
				//and make it's next be whatever it's original ->next's 
				//next was
				toFree->next = toFree->next->next;

				//now remove curr memEntry from Arr to indicate that
				//it was free
				memEntries[i] = 0;
				toFree->occupied = false;
			}
			else {
				//the case where we only have one memEntry, or neighbors
				//are unable to merge
				//
				//simplest case: remove this memEntry from array and
				//change occupied to false, memsize doesnt change
				memEntries[i] = 0;
				toFree->occupied = false;
			}
			return;
		}
	}
	fprintf(stderr, "File %s, line %d: unable to free pointer.\n", filename, linenum);	
	return;

}



