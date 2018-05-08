#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "nqueens.h"

#define N 5

long wtime();

int main(int argc, char** argv) {
	int size = N;
	long start_time, end_time;
	
	if(argc > 1)
		size = atoi(argv[1]);
	
	start_time = wtime();
	int solutions = find_queens(size);
	end_time = wtime();
	
	printf("Nqueens ; size: %d; time: %ld; solutions: %d\n", 
			 size, (long) (end_time - start_time), solutions);
}

/* wtime */
long wtime() {
   struct timeval t;
   gettimeofday(&t, NULL);
   return t.tv_sec*1000000 + t.tv_usec;
}
