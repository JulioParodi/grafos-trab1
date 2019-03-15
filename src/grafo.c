#include "grafo.h"

grafoP le_grafo(FILE *input){
  grafoP cabeca = NULL;
  grafoP aux = NULL;
  bool first = true;

  cabeca = aloca_grafo();
  aux = cabeca;
  char linha[2048], vert1Linha[1024],vert2Linha[1024];
  fgets (linha,2055,input);
  while (!feof(input)){
    if ( strcmp(linha,"\n")) {
      processa_linha (linha, vert1Linha, vert2Linha);
      if (first){
        strcpy(cabeca->nomeVert,vert1Linha);
        if (strcmp(vert2Linha, "\0")){
          aux = aloca_grafo();
          strcpy(aux->nomeVert,vert2Linha);
          cabeca->proxVertice = aux;
          cria_vizinho (cabeca, vert1Linha, vert2Linha);
          cria_vizinho (cabeca, vert2Linha, vert1Linha);
        }
        first = false;
      } else {
        if( !busca_nomeVert_no_grafo (cabeca, vert1Linha)){
          aux->proxVertice = aloca_grafo ();
          strcpy(aux->proxVertice->nomeVert,vert1Linha);
          aux = aux->proxVertice;
        }
        if (strcmp(vert2Linha, "\0")){
          if( !busca_nomeVert_no_grafo (cabeca, vert2Linha)){
            aux->proxVertice = aloca_grafo ();
            strcpy(aux->proxVertice->nomeVert,vert2Linha);
            aux = aux->proxVertice;
          }
          cria_vizinho (cabeca, vert1Linha, vert2Linha);
          cria_vizinho (cabeca, vert2Linha, vert1Linha);
        }
      }
    }
    fgets (linha,2055,input);
  }
  return cabeca;
}

void cria_vizinho (grafoP cabeca, char *vert1Linha, char *vert2Linha){
  grafoP aux = cabeca;
  verticeP auxV = NULL;

  while (aux){
    if (!strcmp(aux->nomeVert, vert1Linha)){
      if (aux->verticeAdj){
        auxV = aux->verticeAdj;
        while(auxV->proximo){
          auxV = auxV->proximo;
        }
        auxV->proximo = aloca_vertice ();
        strcpy(auxV->proximo->nomeVert, vert2Linha);
      } else {
        aux->verticeAdj = aloca_vertice ();
        strcpy(aux->verticeAdj->nomeVert, vert2Linha);
      }
    }
    aux = aux->proxVertice;
  }
}

void printa_grafo (grafoP g){
  grafoP aux = g;
  verticeP auxV = NULL;

  while (aux){
    printf("%s -> ", aux->nomeVert );
    auxV = aux->verticeAdj;
    while (auxV){
      printf("%s ", auxV->nomeVert);
      auxV = auxV->proximo;
    }
    printf("\n");
    aux = aux->proxVertice;
  }
  printf("\n");
}


int busca_nomeVert_no_grafo (grafoP g, char * vert){
  grafoP atual = g;

  while (atual){
    if (!strcmp (atual->nomeVert, vert)){
      return 1;
    }
    atual = atual->proxVertice;
  }
  return 0;
}

void processa_linha (char *linha,char *vert1,char *vert2){
  int k = 0, j = 0;
  strcpy (vert1, "\0");
  strcpy (vert2, "\0");
  while (linha[k] != ' ' && linha[k] != '\n'){
    vert1[k] = linha[k];
    ++k;
  }
  vert1[k] = '\0';
  ++k;
  while (linha[k + j] != ' ' && linha[k + j] != '\n'){
    vert2[j] = linha[k + j];
    ++j;
  }
  vert2[j] = '\0';
}

verticeP aloca_vertice (void){
  verticeP v = (verticeP) malloc( sizeof(VerticeS) );
  if (v){
    v->proximo = NULL;
    strcpy (v->nomeVert, "\0");
  }
  return v;
}

grafoP aloca_grafo (void){
  grafoP g = (grafoP) malloc( sizeof(GrafoS) );
  if (g){
    g->verticeAdj = NULL;
    g->proxVertice = NULL;
    strcpy (g->nomeVert, "\0");
  }
  return g;
}

int destroi_grafo(grafoP g){
  grafoP lixoG = g, atualG = g;

  verticeP lixoV = NULL, atualV = NULL;
  while (atualG){
    atualV = atualG->verticeAdj;
    while (atualV){
      lixoV = atualV;
      atualV = atualV->proximo;
      free(lixoV);
    }
    lixoG = atualG;
    atualG = atualG->proxVertice;
    free(lixoG);
  }
  return 1;
}

void busca_vertice_comum (grafoP g1, grafoP g2, double * triadesAberta, double * triadesFechadas){
  verticeP vert1 , vert2;
  vert1 = g1->verticeAdj;
  vert2 = g2->verticeAdj;
  while (vert1){
    while (vert2) {
      if (!strcmp(vert1->nomeVert, vert2->nomeVert)){
        if (verifica_vizinho (g1,g2->nomeVert)){
          (*triadesFechadas)++;
        }else {
          (*triadesAberta)++;
        }
      }
      vert2 = vert2->proximo;
    }
    vert2 = g2->verticeAdj;
    vert1 = vert1->proximo;
  }
}

int verifica_vizinho (grafoP vert1, char * nomeVert){
  verticeP aux = vert1->verticeAdj;
  while (aux){
    if (!strcmp(aux->nomeVert,nomeVert)) return 1;
    aux = aux->proximo;
  }
  return 0;
}

double coeficiente_agrupamento_grafo(grafoP g){
  grafoP vert1 = NULL, vert2 = NULL;
  double triadesAberta = 0, triadesFechadas = 0, triadesTotal = 0;
  vert1 = g;
  while (vert1){
    vert2 = vert1->proxVertice;
    while (vert2) {
      busca_vertice_comum(vert1, vert2, &triadesAberta, &triadesFechadas);
      vert2 = vert2->proxVertice;
    }
    vert1 = vert1->proxVertice;
  }

  triadesTotal = triadesAberta + triadesFechadas;
  if ((int)triadesTotal == 0){
    return 0;
  }
  // printf("triadesFechadas %lg - triadesAberta %lg\n", triadesFechadas, triadesAberta);
  return triadesFechadas / triadesTotal;
}

// grafo escreve_grafo(FILE *output, grafo g);
