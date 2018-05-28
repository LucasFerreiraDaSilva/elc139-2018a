#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char* argv[]) {
  int myrank;         // "rank" do processo (0 a P-1)
  int p;              // número de processos
  int source;         // "rank" do processo remetente
  int dest;           // "rank" do processo destinatário
  int tag = 0;        // "etiqueta" da mensagem
  char msg[100];      // a mensagem
  MPI_Status status;  // "status" de uma operação efetuada

  // MPI_Init deve ser invocado antes de qualquer outra chamada MPI
  MPI_Init(&argc, &argv);
  // Descobre o "rank" do processo
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  // Descobre o número de processos
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  if (myrank != 0) {
    // obtem nome do host
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
    sprintf(msg, "Processo %d disse Ola no host %s!", myrank, processor_name);
    // envia mensagem ao processo 0
    dest = 0;
    MPI_Send(msg, strlen(msg)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
  } else {
    for(source = 1; source < p; source++) {
      // recebe P-1 mensagens
      MPI_Recv(msg, 100, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
      printf("%s\n", msg); // mostra mensagem
    }
  }
  MPI_Finalize(); // finaliza MPI
  return 0;
}
