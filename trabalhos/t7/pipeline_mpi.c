#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
    int rank;          // "rank" do processo (0 a P-1)
    int p;             // n�mero de processos
    int source;        // "rank" do processo remetente
    int dest;          // "rank" do processo destinat�rio
    int tag = 0;       // "etiqueta" da mensagem
    int msg;           // a mensagem
    MPI_Status status; // "status" de uma opera��o efetuada

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (!rank)
    {
        msg = 0;
        dest = 1;
        printf("[Processo %d] Enviando mensagem com valor '%d' ao processo %d!\n", rank, msg, dest);
        MPI_Send(&msg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
    }
    else if (rank == (p - 1))
    {
        source = rank - 1;
        MPI_Recv(&msg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
        printf("[Processo %d] Valor da mensagem recebida: '%d'\n", rank, msg);
    }
    else
    {
        source = rank - 1;
        MPI_Recv(&msg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
        dest = rank + 1;
        printf("[Processo %d] Recebida a mensagem: '%d' - Enviando ao processo %d a mensagem: '%d'!\n", rank, msg, dest, msg + 1);
        msg++;
        MPI_Send(&msg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
