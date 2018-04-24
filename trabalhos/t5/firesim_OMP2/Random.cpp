#include "Random.h"
#include <cstdlib>
#include <ctime>

Random::Random()
{
   seed = 1;
   srand(seed);
}


void
Random::setSeed(unsigned int s)
{
   seed = s;
   srand(seed);
}

void
Random::setSeedByTime()
{
   time_t t;
   time(&t);
   seed = (unsigned int) t;
   srand(seed);
}

// Retorna próximo número da seqüência pseudo-aleatória
// (valores entre 0.0 e 1.0)
double
Random::nextDouble()
{
   return (double) rand() / (double) RAND_MAX;
}
