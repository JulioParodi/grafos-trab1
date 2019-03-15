#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void) {

  grafoP g = le_grafo(stdin);

  if ( !g )
    return 1;

    printa_grafo(g);
  printf ("\nO coeficiente de agrupamento do grafo é %f\n", coeficiente_agrupamento_grafo(g));

  return ! destroi_grafo(g);
}
