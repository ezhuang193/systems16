#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


int main(int argc, char** argv) {
	
struct timeval tvBefore, tvAfter; 

    // Workload A
	{
    gettimeofday (&tvBefore, NULL);
    int i = 0;
	for (i = 0; i < 100; i++) {
		
		void* arr[3000];
		// malloc() 1 byte 3000 times
		int j = 0;
		for(j = 0; j < 3000; j++) {
			arr[j] = (int*) malloc(sizeof(1));
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
    int intialTimeC = gettimeofday(&tvBefore, NULL);

    // Randomly choose between a 1 byte malloc() or free() 6000 times
    int i = 0;
    for (i = 0; i < 100; i++) {

        int numMallocs = 0;
        int numFrees = 0;
        int* randomArr[3000];
        int r;
        int j = 0;
        for(j = 0; j < 6000; j++) {
            r = (rand()% 2);
            if ((r == 0) && numMallocs < 3000 ) {
                randomArr[numMallocs] = (int*) (malloc(sizeof(1)));
                numMallocs++;
            }
            else if(numFrees < numMallocs){           	
                free(randomArr[numFrees]);
                numFrees++;
            }
        }
    	printf("Part C -- countmalloc = %d : countfree = %d\n", numMallocs, numFrees);
    }
    gettimeofday (&tvAfter, NULL);

	float executionTimeC = (float) (tvAfter.tv_usec - tvBefore.tv_usec) + (float) (tvAfter.tv_sec - tvBefore.tv_sec)/ 1000000L;
    printf("Total execution time of workload C in microseconds: %f\n", executionTimeC);
    printf("Average execution time of workload C in microseconds: %f\n", executionTimeC / 100);
	}
/////////////////////////////////////////////////
    // Workload D
    {
    // Randomly choose between a randomly-sized malloc() or free 6000 times
    gettimeofday(&veBefore, NULL);

    for (int e = 0; e < 100; e++) {
            //randomly choose between a randomly-sized malloc or free 6000 times

            //int bytes = rand() % 3000;
            int cM = 0;
            int     cF = 0;
            int* randArr[3000];
            int r;
            for(int i = 0; i < 6000; i++) {
                r = (rand()% 2);
                if ((r == 0) && cM < 3000 ) {
                    randArr[cM] = (int*) (malloc(sizeof(rand() % 3000)));
                    printf("Malloced");
                    cM++;
                }
                else if(cF < cM) {
                    free(randArr[cF]);
                    printf("Free'd");
                    cF++;
                }
                }
                printf("Part D -- countmalloc = %d : countfree = %d\n", cM, cF);
            }
    }
    //int fianlTimeD =
    gettimeofday (&tvAfter, NULL);
	
	float executionTimeC = (float) (tvAfter.tv_usec - tvBefore.tv_usec) + (float) (tvAfter.tv_sec - tvBefore.tv_sec)/ 1000000L;
    printf("Total execution time of workload C in microseconds: %f\n", executionTimeC);
    printf("Average execution time of workload C in microseconds: %f\n", executionTimeC / 100);
	
}