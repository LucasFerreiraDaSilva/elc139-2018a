#ifndef __RANDOM_H
#define __RANDOM_H

//  
// Classe para geração de números pseudo-aleatórios.
//
class Random
{
   public:
      Random();
      Random(unsigned int s);
      
      // Retorna próximo número da seqüência pseudo-aleatória
      // (valores entre 0.0 e 1.0)
      double nextDouble();

      void setSeed(unsigned int s);
      void setSeedByTime();

   private:
      unsigned int seed;
      
};

#endif

