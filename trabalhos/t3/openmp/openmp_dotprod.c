/*
 *  Calcula produto escalar (dot product) de 2 vetores.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

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
 * Preenche vetor
 */
void fill(double *a, int size, double value)
{
    int i;

    for (i = 0; i < size; i++)
    {
        a[i] = value;
    }
}

/*
 * Calcula o produto escalar (varias vezes)
 */
double dot_product(double *a, double *b, int n, int repeat)
{
    double dot;
    
    #pragma omp parallel for lastprivate(dot)
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
    int nthreads, wsize, repeat;
    long start_time, end_time;
    double dot;

    if ((argc != 4))
    {
        printf("Uso: %s <nthreads> <worksize> <repetitions>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    nthreads = atoi(argv[1]);
    wsize = atoi(argv[2]);  // worksize = tamanho do vetor de cada thread
    repeat = atoi(argv[3]); // numero de repeticoes dos calculos (para aumentar carga)

    // Cria vetores
    double *a = (double *)malloc(wsize * nthreads * sizeof(double));
    fill(a, wsize * nthreads, 0.01);
    double *b = (double *)malloc(wsize * nthreads * sizeof(double));
    fill(b, wsize * nthreads, 1.0);

    if (a == NULL || b == NULL)
    {
        printf("Erro de alocacao de memoria\n");
        exit(EXIT_FAILURE);
    }

    start_time = wtime();
    dot = dot_product(a, b, wsize, repeat);
    end_time = wtime();

    // Mostra resultado e estatisticas da execucao
    printf("%f\n", dot);
    printf("%d thread(s), %ld usec\n", nthreads, (long)(end_time - start_time));
    fflush(stdout);

    free(a);
    free(b);

    return EXIT_SUCCESS;
}
