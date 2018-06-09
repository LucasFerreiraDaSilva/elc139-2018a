#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int mpi_err, nproc, rank;

int printArray(int array[], int size, char tipo[]){
	printf("%s Rank %d:  ", tipo, rank);
	for (int i = 0; i < size; ++i)
	{
		printf("%d, ", *(array++));
	}
	printf("\n\n");
}

int main(int argc,char *argv[]){
	int teste[16];
	int rec[16];
	mpi_err = MPI_Init(&argc, &argv);
    mpi_err = MPI_Comm_size( MPI_COMM_WORLD, &nproc );
    mpi_err = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    for (int i = 0; i < 16; ++i)
    {
    	teste[i] = (rank + 1) * 1000 + i;
    	//printf("%d, ", teste[i]);    	
    }
    printArray(teste, 16, "send");

    mpi_err = MPI_Alltoall(	teste, 4, MPI_INT,
						    rec, 4, MPI_INT,
	                 	    MPI_COMM_WORLD);
    printArray(rec, 16, "rec");

    MPI_Finalize();

}