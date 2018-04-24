//
// Simula��o de inc�ndio em uma floresta.
// Baseada no c�digo proposto por David Joiner.
//
// Uso: firesim <tamanho-do-problema> <nro. experimentos> <probab. maxima>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "Random.h"
#include "Forest.h"
#include <omp.h>
#include <sys/time.h>

long wtime()
{
   struct timeval t;
   gettimeofday(&t, NULL);
   return t.tv_sec*1000000 + t.tv_usec;
}

void checkCommandLine(int argc, char **argv, int &size, int &trials, int &probs)
{
    if (argc > 1)
    {
        size = atoi(argv[1]);
    }
    if (argc > 2)
    {
        trials = atoi(argv[2]);
    }
    if (argc > 3)
    {
        probs = atoi(argv[3]);
    }
}

int main(int argc, char *argv[])
{

    // par�metros dos experimentos
    int forest_size = 30;
    int n_trials = 5000;
    int n_probs = 101;

    double *percent_burned; // percentuais queimados (sa�da)
    double *prob_spread;    // probabilidades (entrada)
    double prob_min = 0.0;
    double prob_max = 1.0;
    double prob_step;
    int base_seed = 100;

    long start, end;

    checkCommandLine(argc, argv, forest_size, n_trials, n_probs);

    try
    {
        start = wtime();
        Random rand;

        prob_spread = new double[n_probs];
        percent_burned = new double[n_probs];

        prob_step = (prob_max - prob_min) / (double)(n_probs - 1);

        printf("Probabilidade, Percentual Queimado\n");

        // para cada probabilidade, calcula o percentual de �rvores queimadas
        for (int ip = 0; ip < n_probs; ip++){
            prob_spread[ip] = prob_min + (double)ip * prob_step;
            percent_burned[ip] = 0.0;
            rand.setSeed(base_seed + ip); // nova seq��ncia de n�meros aleat�rios
            
            int it;       
            #pragma omp parallel private(it) default(shared) 
            {
                Forest *forest = new Forest(forest_size);

                // executa v�rios experimentos
                #pragma omp for schedule(static)
                for (it = 0; it < n_trials; it++)
                {
                    // queima floresta at� o fogo apagar
                    forest->burnUntilOut(forest->centralTree(), prob_spread[ip], rand);
                    percent_burned[ip] += forest->getPercentBurned();
                }
            }
            // calcula m�dia dos percentuais de �rvores queimadas

            percent_burned[ip] /= n_trials;

            // mostra resultado para esta probabilidade
            printf("%lf, %lf\n", prob_spread[ip], percent_burned[ip]);
            
        }

        delete[] prob_spread;
        delete[] percent_burned;

        end = wtime();
        printf("Tempo = %ld usec\n", (long) (end - start));
    }
    catch (std::bad_alloc)
    {
        std::cerr << "Erro: alocacao de memoria" << std::endl;
        return 1;
    }
    
    return 0;
}
