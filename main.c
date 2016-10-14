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

// int main( int argc, char** argv) {

// 	printf("1\n");
// 	block_init();
// 	printf("2\n");
// 	int x;
// 	printf("3\n");
// 	free( &x );
// 	printf("4\n");
	
// 	char * p = (char *)malloc( 200 );
// 	printf("5\n");
// 	free( p + 10 );
// 	printf("6\n");
	
// 	int * y;
// 	printf("7\n");
// 	free( y );
// 	printf("8\n");
// 	char * p2 = (char*)malloc(100);
// 	printf("9\n");
// 	free( p2 );
// 	printf("10\n");
// 	free( p2 );
// 	printf("11\n");
// 	char* p4 = (char*)malloc(5001);
// 	printf("12\n");
// 	char* p5 = (char*)malloc(5000);
// 	printf("13\n");
// 	char* p6 = (char*)malloc(1);
// 	printf("14\n");

//    int i, n;
//    time_t t;
   
//    n = 5;
   
//    /* Intializes random number generator */
//    srand((unsigned) time(&t));

//    /* Print 5 random numbers from 0 to 49 */
//    for( i = 0 ; i < n ; i++ ) 
//    {
//       printf("%d\n", rand() % 2);
//    }
   
// 	return 0;

// }