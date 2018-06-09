#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int mpi_err, nproc, rank;

int printArray(int array[], int size, char tipo[]){
	printf("%s Rank %d:  ", tipo, rank);
	for (int i = 0; i < size; ++i)
	{
		printf("%*d, ", 4, *(array++));
	}
	printf("\n\n");
}
int teste[16];
int rec[16];
int rec2[16];
int main(int argc,char *argv[]){
	
	mpi_err = MPI_Init(&argc, &argv);
    mpi_err = MPI_Comm_size( MPI_COMM_WORLD, &nproc );
    mpi_err = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    for (int i = 0; i < 16; ++i)
    {
        rec[i] = 0;
    }


    if (rank == 0) {
        for (int i = 0; i < 16; ++i)
        {
        	teste[i] = (rank + 1) * 1000 + i;
        	//printf("%d, ", teste[i]);    	
        }
    
        printArray(teste, 16, "send");
    }

     /*MPI_Scatter(const void* sendbuf, int sendcount, MPI_Datatype sendtype,
void* recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)*/

    // Posicionando o vetor de recebimento
    //mpi_err = MPI_Scatter(teste, 4, MPI_INT, &rec[rank * 4], 4, MPI_INT, 0, MPI_COMM_WORLD);
    
    // Sem posicionar o vetor de recebimento
    mpi_err = MPI_Scatter(teste, 4, MPI_INT, rec, 4, MPI_INT, 0, MPI_COMM_WORLD);
    printArray(rec, 16, "rec");


    // Posicionando o vetor de recebimento
    //mpi_err = MPI_Gather(&rec[rank*4], 4, MPI_INT, &rec2[rank*4], 4, MPI_INT, 0, MPI_COMM_WORLD);

    // Sem posicionar o vetor de recebimento
    mpi_err = MPI_Gather(rec, 4, MPI_INT, rec2, 4, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printArray(rec2, 16, "rec2");
    }

    MPI_Finalize();

}
