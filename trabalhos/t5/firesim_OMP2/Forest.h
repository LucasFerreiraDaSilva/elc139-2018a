#ifndef __FOREST_H
#define __FOREST_H

#include "Random.h"

//
// Classe que representa uma floresta incendiável.
//
class Forest
{
   public:

      Forest(int s);
      ~Forest();

      struct TreePosn
      { 
            int i; 
            int j;
      };

      struct TreePosn centralTree();
      int burnUntilOut(TreePosn start_tree, double prob_spread, Random& r);
      double getPercentBurned();

   private:

      void burn(double prob_spread, Random& r);     
      void grow();
      void lightTree(TreePosn p);
      bool isBurning();
      bool fireSpreads(double prob_spread, Random& r);

   private:

      // A floresta é armazenada em uma matriz.
      // Cada elemento é uma árvore que pode estar em 4 estados.

      enum Tree {
         Unburnt,       // árvore não queimada 
         Smoldering,    // árvore começando a pegar fogo
         Burning,       // árvore queimando
         Burnt          // árvore completamente queimada
      };        

      Tree** t; 
      int size;

};

#endif

