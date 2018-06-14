/*
 *  Calcula produto escalar (dot product) de 2 vetores.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mpi.h"

/*
 * Tempo (wallclock) em microssegundos
 */
long wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec * 1000000 + t.tv_usec;
}

/*
 * Inicializa vetores
 */
void init_vectors(double *a, double *b, int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = 0.5;
        b[i] = 1.0;
    }
}

/*
 * Calcula o produto escalar (varias vezes)
 */
double dot_product(double *a, double *b, int n, int repeat)
{
    double dot;
    for (int k = 0; k < repeat; k++)
    {
        dot = 0.0;
        for (int i = 0; i < n; i++)
        {
            dot += a[i] * b[i];
        }
    }
    return dot;
}

int main(int argc, char **argv)
{
    int wsize;      // tamanho dos vetores
    int repeat;     // numero de repeticoes
    double dot;     // valor do calculo do produto
    double aux_dot; // auxiliar para recebimento dos valores

    int rank;   // "rank" do processo (0 a P-1)
    int source; // "rank" do processo remetente
    int p;      // numero de processos

    int tag_calc = 0; // "etiqueta" da mensagem de calculo
    int tag_time = 1; // "etiqueta" da mensagem de tempo

    MPI_Status status; // "status" de uma operacao efetuada

    long start_time, end_time, total_time, calc_time; // calculo do tempo

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if ((argc != 3))
    {
        printf("Uso: mpiexec -np <nprocesses> %s <tamanho dos vetores> <repeticoes>\n", argv[0]);
        exit(EXIT_FAILURE);
        MPI_Finalize();
    }

    wsize = atoi(argv[1]);
    repeat = atoi(argv[2]);

    double *a = (double *)malloc(sizeof(double) * wsize);
    double *b = (double *)malloc(sizeof(double) * wsize);

    if (a == NULL || b == NULL)
    {
        printf("Erro de alocacao de memoria\n");
        exit(EXIT_FAILURE);
        MPI_Finalize();
    }

    init_vectors(a, b, wsize);
]
    start_time = wtime();
    dot = dot_product(a, b, wsize, repeat);
    end_time = wtime();

    total_time = (long)(end_time - start_time);

    if (rank != 0)
    {
        MPI_Send(&dot, 1, MPI_DOUBLE, 0, tag_calc, MPI_COMM_WORLD);
        MPI_Send(&total_time, 1, MPI_LONG, 0, tag_time, MPI_COMM_WORLD);
    }
    else
    {
        for (source = 1; source < p; source++)
        {
            MPI_Recv(&aux_dot, 1, MPI_DOUBLE, source, tag_calc, MPI_COMM_WORLD, &status);
            MPI_Recv(&calc_time, 1, MPI_LONG, source, tag_time, MPI_COMM_WORLD, &status);
            dot += aux_dot;
            total_time += calc_time;
        }
        //printf("Produto escalar = %f\n", dot);
        //printf("Tempo de calculo = %ld usec\n", total_time);
        printf("Tempo:%ld; Processos:%d; Repeticoes:%d; Tamanho:%d ; Resultado:%f\n", total_time, p, repeat, wsize, dot);
    }

    free((void *)a);
    free((void *)b);

    MPI_Finalize();
    return EXIT_SUCCESS;
}
