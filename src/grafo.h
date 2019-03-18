#ifndef _GRAFO_H
#define _GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//------------------------------------------------------------------------------
// Cada vertice pertencente ao grafo tera um struct grafo para si, se o ponteiro
// verticeAdj = NULL , overtice esta isolado no grafo sem vizinhos 

typedef struct grafo {
  char nomeVert[1024];           // Armazena nome do vertice existente no grafo
  struct vertice *verticeAdj;    // Ponteiro para os vertices adjacentes ao nomeVert
  struct grafo *proxVertice;     // Ponteiro para os proximos vertices existentes no grafo
} GrafoS;

//------------------------------------------------------------------------------

typedef struct vertice {
  char nomeVert[1024];           // Nome do vertice adjacente a algum outro vertice ja existente no grafo
  struct vertice *proximo;       // Ponteiro para o proximo vizinho do mesmo vertice
} VerticeS;

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um grafo
//
// o grafo tem um nome, que é uma "string"
typedef struct grafo * grafo;

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um vértice
//
// o vértice tem um nome, que é uma "string"
typedef struct vertice *verticeP;

//------------------------------------------------------------------------------
// Aloca e inicializa uma instancia da estrutura grafo,
// retorna um ponteiro da instancia. (grafo)
grafo aloca_grafo (void);

//------------------------------------------------------------------------------
// Aloca e inicializa uma instancia da estrutura vertice,
// retorna um ponteiro da instancia. (VericeP)
verticeP aloca_vertice (void);

//------------------------------------------------------------------------------
// Recebe como parametro a linha lida do arquivo entrada e separa os vertices
// contidas nela, no caso de não existir vertice na linha :
//  vert1 = '\0' e vert2 = '\0'
// Caso haja um vertice:
//  vert1 = primeiro vertice lido e vert2 = '\0'
// E dois verices:
// vert1 = primeiro vertice lido e vert2 = segundo vertice lido
void processa_linha (char *linha,char *vert1,char *vert2);

//------------------------------------------------------------------------------
// Caso vertice exista no grafo
//  retorna 1
//  caso não esteja no grafo
//    Retorna 0
int busca_nomeVert_no_grafo (grafo g, char * vert);

//------------------------------------------------------------------------------
// Passados dois vertices g1 e g2 , procurasse um vertice em comum entre os dois.
// A propria função realiza a contagem das triades.
void busca_vertice_comum (grafo g1, grafo g2, double * triadesAberta, double * triadesFechadas);

//------------------------------------------------------------------------------
// Escreve na saida padrão o desenho da estrutura de dados, de como o grafo esta
// representado em memória
void printa_grafo (grafo g);

//------------------------------------------------------------------------------
// Passado o grafo, a função encadeia o vertice vert2Linha na lista do vertice
// vert1Linha
void cria_vizinho (grafo cabeca, char *vert1Linha, char *vert2Linha);

//------------------------------------------------------------------------------
// Caso o nomeVert seja vizinho de vert1 , ou seja , esteja da lista de vert1,
// entao
//  devolve 1
// caso contrario,
//  devolve 0
int verifica_vizinho (grafo vert1, char * nomeVert);

//------------------------------------------------------------------------------
// desaloca toda a memória usada em *g
//
// devolve 1 em caso de sucesso,
//         ou
//         0, caso contrário
int destroi_grafo(grafo g);

//------------------------------------------------------------------------------
// lê um grafo de input.
// um grafo é um arquivo onde cada linha tem zero, uma ou duas
// strings (sequência de caracteres sem "whitespace").
//
// devolve o grafo lido. Caso o arquivo esteja mal formado o
// comportamento da função é indefinido
grafo le_grafo(FILE *input);

//------------------------------------------------------------------------------
// escreve o grafo g em output, no mesmo formato que o usado por le_grafo()
//
// devolve o grafo escrito,
//         ou
//         NULL, em caso de erro
// grafo escreve_grafo(FILE *output, grafo g);

//------------------------------------------------------------------------------
// devolve o coeficiente de agrupamento de g
// ou seja, o número de tríades fechadas divido pelo
// total de tríades (ou seja, a soma de tríades abertas e fechadas).
//
double coeficiente_agrupamento_grafo(grafo g);

//------------------------------------------------------------------------------
#endif
