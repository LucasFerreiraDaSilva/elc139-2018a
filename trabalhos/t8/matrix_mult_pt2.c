
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 8 /* Size of matrices */

int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

void fill_matrix(int m[SIZE][SIZE])
{
    static int n = 0;
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            m[i][j] = n++;
}

void print_matrix(int m[SIZE][SIZE])
{
    int i, j = 0;
    for (i = 0; i < SIZE; i++)
    {
        printf("\n\t| ");
        for (j = 0; j < SIZE; j++)
            printf("%*d", 6, m[i][j]);
        printf("|");
    }
}

int main(int argc, char *argv[])
{
    int myrank, nproc, from, to, i, j, k;
    int tag_A = 0;
    int tag_B = 1;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank); /* who am i */
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);  /* number of processors */

    int *sendcounts = malloc(nproc * sizeof(int));
    int *displs = malloc(nproc * sizeof(int));

    for (int i = 0; i < nproc; i++)
    {
        sendcounts[i] = 0;
    }

    int linha = 0;
    while (linha < SIZE)
    {
        sendcounts[linha % nproc] += SIZE;
        linha++;
    }

    int acum = 0;
    for (int i = 0; i < nproc; i++)
    {
        displs[i] = acum;
        acum += sendcounts[i];
    }

    from = displs[myrank] / SIZE;
    to = from + (sendcounts[myrank] / SIZE);

    /* Process 0 fills the input matrices and broadcasts them to the rest */
    /* (actually, only the relevant stripe of A is sent to each process) */

    if (myrank == 0)
    {
        fill_matrix(A);
        fill_matrix(B);
    }

    /*
        MPI_Bcast(
            void* data,
            int count,
            MPI_Datatype datatype,
            int root,
            MPI_Comm communicator
        )
    */

    // Broadcast B to other process
    MPI_Bcast(B, SIZE * SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    /*
        MPI_Scatterv(
            const void *sendbuf,
            const int *sendcounts,
            const int *displs,
            MPI_Datatype sendtype,
            void *recvbuf,
            int recvcount,
            MPI_Datatype recvtype,
            int root,
            MPI_Comm comm
        )
   */

    MPI_Scatterv(A, sendcounts, displs, MPI_INT, &A[from], sendcounts[myrank], MPI_INT, 0, MPI_COMM_WORLD);

    printf("computing slice %d (from row %d to %d)\n", myrank, from, to - 1);

    for (i = from; i < to; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            C[i][j] = 0;
            for (k = 0; k < SIZE; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    MPI_Gatherv(C[from], sendcounts[myrank], MPI_INT, C, sendcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);

    if (myrank == 0)
    {
        printf("\n\n");
        print_matrix(A);
        printf("\n\n\t       * \n");
        print_matrix(B);
        printf("\n\n\t       = \n");
        print_matrix(C);
        printf("\n\n");
    }

    MPI_Finalize();
    return 0;
}
