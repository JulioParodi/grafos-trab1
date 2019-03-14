#ifndef _GRAFO_H
#define _GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct grafo {
  char nomeVert[1024];
  struct vertice *verticeAdj;
  struct grafo *proxVertice;
} GrafoS;

typedef struct vertice {
  char nomeVert[1024];
  struct vertice *proximo;
} VerticeS;



//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um grafo
//
// o grafo tem um nome, que é uma "string"

typedef struct grafo * grafoP;

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um vértice
//
// o vértice tem um nome, que é uma "string"

typedef struct vertice *verticeP;

//------------------------------------------------------------------------------



grafoP aloca_grafo (void);
verticeP aloca_vertice (void);
void processa_linha (char *linha,char *vert1,char *vert2);
int busca_nomeVert_no_grafo (grafoP g, char * vert);
void printa_grafo (grafoP g);
void cria_vizinho (grafoP cabeca, char *vert1Linha, char *vert2Linha);




//------------------------------------------------------------------------------
// desaloca toda a memória usada em *g
//
// devolve 1 em caso de sucesso,
//         ou
//         0, caso contrário

int destroi_grafo(grafoP g);

//------------------------------------------------------------------------------
// lê um grafo de input.
// um grafo é um arquivo onde cada linha tem zero, uma ou duas
// strings (sequência de caracteres sem "whitespace").
//
// devolve o grafo lido. Caso o arquivo esteja mal formado o
// comportamento da função é indefinido

grafoP le_grafo(FILE *input);

//------------------------------------------------------------------------------
// escreve o grafo g em output, no mesmo formato que o usado por le_grafo()
//
// devolve o grafo escrito,
//         ou
//         NULL, em caso de erro

// grafoP escreve_grafo(FILE *output, grafoP g);

//------------------------------------------------------------------------------
// devolve o coeficiente de agrupamento de g
// ou seja, o número de tríades fechadas divido pelo
// total de tríades (ou seja, a soma de tríades abertas e fechadas).
//

double coeficiente_agrupamento_grafo(grafoP g);

//------------------------------------------------------------------------------
#endif
