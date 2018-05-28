//
//  Este programa MPI tem um erro!
//  Identifique este erro e corrija-o para que 2 processos
//  troquem mensagens corretamente.
//  
//  Uso: mpirun -np 2 <prog>
//  
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
   int numtasks, rank, dest, tag, source, rc;
   int inmsg, outmsg = 100;
   MPI_Status stat;

   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);

   printf("Processo %d iniciando...\n",rank);

   if (rank == 0) {
      dest = 1;
      source = dest;
      tag = 0;
      rc = MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
      printf("Enviei mensagem para processo %d...\n", dest);
      rc = MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &stat);
      printf("Recebi mensagem do processo %d...\n", source);
   }
   else if (rank == 1) {
      dest = 0;
      source = dest;
      tag = 0;
      rc = MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &stat);
      printf("Recebi mensagem do processo %d...\n", source);
      rc = MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
      printf("Enviei mensagem para processo %d...\n", dest);
   }

}
