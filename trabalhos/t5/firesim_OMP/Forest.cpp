#include "Forest.h"

Forest::Forest(int s) : size(s) 
{
   t = new Tree*[size];
   for (int i = 0; i < size; i++)
      t[i] = new Tree[size];
   grow();
}

Forest::~Forest()
{
   for (int i = 0; i < size; i++)
      delete[] t[i];
   delete[] t;
}

struct Forest::TreePosn 
Forest::centralTree()
{
   struct TreePosn p = {size/2, size/2};
   return p;
}

int
Forest::burnUntilOut(TreePosn start_tree, double prob_spread, Random& r) 
{
   int count;

   grow();
   lightTree(start_tree);

   // queima a floresta até terminar o fogo
   count = 0;
   while (isBurning()) {
      burn(prob_spread, r);
      count++;
   }

   return count;
}

double 
Forest::getPercentBurned() 
{
   int total = size*size-1;
   int sum = 0;

   // calcula quantidade de árvores queimadas
   for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
         if (t[i][j] == Burnt) {
            sum++;
         }
      }
   }
   // retorna percentual de árvores queimadas
   return ((double)(sum-1)/(double)total);
}

void 
Forest::burn(double prob_spread, Random& r) 
{
   for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
         if (t[i][j] == Burning) // árvores pegando fogo
            t[i][j] = Burnt;     // ficam completamente queimadas
         if (t[i][j] == Smoldering) // árvores começando a pegar fogo
            t[i][j] = Burning;      // ficam queimando
      }
   }

   // árvores não queimadas começam a pegar fogo
   for (int i = 0;  i < size; i++) {
      for (int j = 0; j < size; j++) {
         if (t[i][j] == Burning) {
            if (i != 0) { // árvore ao norte
               if (t[i-1][j] == Unburnt && fireSpreads(prob_spread, r)) {
                  t[i-1][j] = Smoldering;
               }
            }
            if (i != size-1) { // árvore ao sul
               if (t[i+1][j] == Unburnt && fireSpreads(prob_spread, r)) {
                  t[i+1][j] = Smoldering;
               }
            }
            if (j != 0) { // árvore a oeste
               if (t[i][j-1] == Unburnt && fireSpreads(prob_spread, r)) {
                  t[i][j-1] = Smoldering;
               }
            }
            if (j != size-1) { // árvore a leste
               if (t[i][j+1] == Unburnt && fireSpreads(prob_spread, r)) {
                  t[i][j+1] = Smoldering;
               }
            }
         }
      }
   }
}

void 
Forest::grow()
{
   for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++)
         t[i][j] = Unburnt;
}

void 
Forest::lightTree(TreePosn p) 
{ 
   t[p.i][p.j] = Smoldering;
}

bool
Forest::isBurning()
{
   for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
         if (t[i][j] == Smoldering || t[i][j] == Burning) {
            return true;
         }
      }
   }
   return false;
}

bool
Forest::fireSpreads(double prob_spread, Random& r) 
{
   if (r.nextDouble() < prob_spread) 
      return true;
   else
      return false;
}
