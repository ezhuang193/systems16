#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
//#include "mymalloc.h"

int main(int argc, char** argv) {
	
struct timeval tvBefore, tvAfter; 

    // Workload A
	{

    gettimeofday (&tvBefore, NULL);
    int i = 0;
	for (i = 0; i < 100; i++) {
		
		int* arr[3000];
		// malloc() 1 byte 3000 times
		int j = 0;
		for(j = 0; j < 3000; j++) {
			arr[j] = (int*) malloc(sizeof(1));
//			arr[j] =(int*) myMalloc(sizeof(1), __FILE__, __LINE__);
		}
		// then free() the 3000 1 byte pointers one by one
		int k = 0;
		for(k = 0; k < 3000; k++) {
			free(arr[k]);
		}
	}
    gettimeofday (&tvAfter, NULL);

	float executionTimeA = (float) (tvAfter.tv_usec - tvBefore.tv_usec) + (float) (tvAfter.tv_sec - tvBefore.tv_sec)/ 1000000L;
    printf("Total execution time of workload A in microseconds: %f\n", executionTimeA);
    printf("Average execution time of workload A in microseconds: %f\n", executionTimeA / 100);

	}
/////////////////////////////////////////////////
    // Workload B
	{

    int *b;
    gettimeofday(&tvBefore, NULL);

    int i = 0;
	for (i = 0; i < 100; i++) {
        //malloc one byte and immediately free it 3000 times in  arow                           
		int j = 0;
        for(j = 0; j < 3000; j++) {
        	b = (int*) malloc(sizeof(1));
        	free(b);
        }
    }

    gettimeofday(&tvAfter, NULL);

	float executionTimeB = (float) (tvAfter.tv_usec - tvBefore.tv_usec) + (float) (tvAfter.tv_sec - tvBefore.tv_sec)/ 1000000L;
    printf("Total execution time of workload B in microseconds: %f\n", executionTimeB);
    printf("Average execution time of workload B in microseconds: %f\n", executionTimeB / 100);

	}
/////////////////////////////////////////////////
    //Workload C
	{
    // Randomly choose between a 1 byte malloc() or free() 6000 times

    gettimeofday(&tvBefore, NULL);

    int i = 0;
    for (i = 0; i < 100; i++) {
        int numMallocs = 0;
        int numFrees = 0;
        int* randomArr[3000];
        int random;
        int j = 0;
        for(j = 0; j < 6000; j++) {
            random = (rand()% 2);
            if ((random == 0) && numMallocs < 3000 ) {
                randomArr[numMallocs] = (int*) (malloc(sizeof(1)));
                numMallocs++;
            }
            else if(numFrees < numMallocs){           	
                free(randomArr[numFrees]);
                numFrees++;
            }
        }
    	printf("numMallocs = %d : numFrees = %d\n", numMallocs, numFrees);
    }
    gettimeofday (&tvAfter, NULL);

	float executionTimeC = (float) (tvAfter.tv_usec - tvBefore.tv_usec) + (float) (tvAfter.tv_sec - tvBefore.tv_sec)/ 1000000L;
    printf("Total execution time of workload C in microseconds: %f\n", executionTimeC);
    printf("Average execution time of workload C in microseconds: %f\n", executionTimeC / 100);

	}
/////////////////////////////////////////////////
    // Workload D
    {
    //Randomly choose between a randomly-sized malloc() or free 6000 times

    gettimeofday(&tvBefore, NULL);

    int i = 0;
    for (i = 0; i < 100; i++) {
        //randomly choose between a randomly-sized malloc or free 6000 times

        int numMalloc = 0;
        int numFree = 0;
        int* randArr[3000];
        int random;
        int j = 0;
        for(j = 0; j < 6000; j++) {
            random = (rand()% 2);

            if ((random == 0) && numMalloc < 3000 ) {
                randArr[numMalloc] = (int*) (malloc(sizeof(rand() % 3000)));
                numMalloc++;
            }
            else if(numFree < numMalloc) {
                free(randArr[numFree]);
                numFree++;
            }
        }
            printf("numMalloc = %d : numFree = %d\n", numMalloc, numFree);
    }

    gettimeofday (&tvAfter, NULL);
	
	float executionTimeD = (float) (tvAfter.tv_usec - tvBefore.tv_usec) + (float) (tvAfter.tv_sec - tvBefore.tv_sec)/ 1000000L;
    printf("Total execution time of workload D in microseconds: %f\n", executionTimeD);
    printf("Average execution time of workload D in microseconds: %f\n", executionTimeD / 100);

	}

	/* E. */
	{

int * xt;
	 gettimeofday(&tvBefore, NULL);
	 	int i, j, k;
	 	for (j = 0; j < 100; j++) {
			for(i = 0; i< 1000;i++){
				xt = (int*) malloc(sizeof(5));
				free(xt);
			}	
		}
		gettimeofday (&tvAfter, NULL);

		
	float executionTimeE = (float) (tvAfter.tv_usec - tvBefore.tv_usec) + (float) (tvAfter.tv_sec - tvBefore.tv_sec)/ 1000000L;
    printf("Total execution time of workload E in microseconds: %f\n", executionTimeE);
    printf("Average execution time of workload E in microseconds: %f\n", executionTimeE / 100);

	}
	/* F. */
	{
	gettimeofday(&tvBefore, NULL);
		int x = 3000;
		int i, j;
		int* bt;
		for (j = 0; j < 100; j++) {
		//malloc one byte and immediately free it 3000 times in a row
			for(i = 0; i < 3000; i++) {
				bt = (int*) malloc(sizeof(x));
				free(bt);
				x--;
			}
		}
	gettimeofday (&tvAfter, NULL);

	float executionTimeF = (float) (tvAfter.tv_usec - tvBefore.tv_usec) + (float) (tvAfter.tv_sec - tvBefore.tv_sec)/ 1000000L;
    printf("Total execution time of workload F in microseconds: %f\n", executionTimeF);
    printf("Average execution time of workload F in microseconds: %f\n", executionTimeF / 100);
	}
}