#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int main(int argc, char** argv) {
	
	struct timeval *timeBefore, *timeAfter;
	
	int *a;
	int *b;
	int *c;
	int *d;
	
	//Testcase A:
	{
	/*int intialTimeA */
	gettimeofday(&timeBefore, NULL);
		
		for (int e = 0; e < 100; e++) {
				
				int* arr[3000];
				//malloc 1 byte 3000 times
				for(int i = 0; i < 3000; i++) {
					arr[i] = (int*) malloc(sizeof(1));
				}
				//free the 3000 1 byte pointers one by one
				for(int i = 0; i < 3000; i++) {
					free(arr[i]);
				}	
			}
		
		//int fianlTimeA = 
		gettimeofday (&timeAfter, NULL);
		
		double exeTimeA = (double) (timeAfter.tv_usec - timeBefore.tv_usec) / 1000000 + (double) (timeAfter.tv_sec - timeBefore.tv_sec);
		
		printf("The execution time of testcase A, over 100 executions, in microseconds is: %ld\n", exeTimeA);
	}
	
	//Testcase B:
	{
		//int intialTimeB = 
		gettimeofday(&timeBefore, NULL);
		
			for (int e = 0; e < 100; e++) {
			//malloc one byte and immediately free it 3000 times in a row
				for(int i = 0; i < 3000; i++) {
					b = (int*) malloc(sizeof(1));
					free(b);
				}
			}
			
		//int fianlTimeB = 
		gettimeofday (&timeAfter, NULL);
		
		double exeTimeB = (double) (timeAfter.tv_usec - timeBefore.tv_usec) / 1000000 + (double) (timeAfter.tv_sec - timeBefore.tv_sec);
		
		printf("The execution time of testcase B, over 100 executions, in microseconds is: %ld\n", exeTimeB);
	}

	//randomly choose between 1 byte malloc or free 6000 times
	
	/*a = (int*) malloc(856*sizeof(1));
	
	
	for(int r1 = 0; r1 < 856; r1++) {
		free(a);
	}
	
	c = (int*) malloc(365*sizeof(1));
	
	for(int r2 = 0; r2 < 365; r2++) {
		free(c);
	}
	
	d = (int*) malloc(1779*sizeof(1));
	
	for(int r3 = 0; r3 < 1779; r3++) {
		free(d);
	}*/
	
	//Testcase C:
	{
		//int intialTimeC = 
		gettimeofday(&timeBefore, NULL);
		
			for (int e = 0; e < 100; e++) {
				int valid = 0;
				int countM = 0;
				int	countF = 0;
				int* randomArr[3000];
				int r;
				for(int i = 0; i < 6000; i++) {
					r = (rand()% 2);
					if ((r == 0) && countM < 3000 ) {
						randomArr[countM] = (int*) (malloc(sizeof(1)));
						printf("Malloced");
						countM++;
						//valid++;
					}
					else {
						if(countF < countM) {
							free(randomArr[countF]);
							printf("Free'd");
							countF++;
						}	
					}
					printf("Part C -- countmalloc = %d : countfree = %d\n", countM, countF);
				}
			}
		//int fianlTimeC = 
		gettimeofday (&timeAfter, NULL);
		
		double exeTimeC = (double) (timeAfter.tv_usec - timeBefore.tv_usec) / 1000000 + (double) (timeAfter.tv_sec - timeBefore.tv_sec);
		
		printf("The execution time of testcase C, over 100 executions, in microseconds is: %ld\n", exeTimeC);
	}
	
	//Testcase D:
	{
		//int intialTimeD = 
		gettimeofday(&timeBefore, NULL);
		
		for (int e = 0; e < 100; e++) {
			//randomly choose between a randomly-sized malloc or free 6000 times
			
			//int bytes = rand() % 3000;
			int cM = 0;
			int	cF = 0;
			int* randArr[3000];
			int r;
			for(int i = 0; i < 6000; i++) {
				r = (rand()% 2);
				if ((r == 0) && cM < 3000 ) {
					randArr[cM] = (int*) (malloc(sizeof(rand() % 3000)));
					printf("Malloced");
					cM++;
					//valid++;
				}
				else {
					if(cF < cM) {
						free(randArr[cF]);
						printf("Free'd");
						cF++;
					}	
				}
				printf("Part D -- countmalloc = %d : countfree = %d\n", cM, cF);
			}
		}
		//int fianlTimeD = 
		gettimeofday (&timeAfter, NULL);
		
		double exeTimeD = (double) (timeAfter->tv_usec - timeBefore->tv_usec) / 1000000 + (double) (timeAfter->tv_sec - timeBefore->tv_sec);
		
		printf("The execution time of testcase D, over 100 executions, in microseconds is: %ld\n", exeTimeD);
	}
	
	
	/*e = (int*) malloc(rand() * sizeof(1));
	int size = sizeof(e);
	
	if(size <= 3000) {
		for(int r4 = 0; r4 < size; r4++) {
			free(e);
		}
	}*/
	
	
}