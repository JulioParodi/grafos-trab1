#include "grafo.h"

grafo le_grafo(FILE *input){
  grafo cabeca = NULL;
  grafo aux = NULL;
  bool first = true;

  // instancia o inicio do grafo
  cabeca = aloca_grafo();
  aux = cabeca;
  char linha[2048], vert1Linha[1024],vert2Linha[1024];

  //Laço para ler linha por linha do arquivo
  fgets (linha,2055,input);
  while (!feof(input)){

    //ignora linha vazia
    if ( strcmp(linha,"\n")) {

      //Separa os vertices contidos na linha
      processa_linha (linha, vert1Linha, vert2Linha);

      // Na primeira interação o vertice deve ser inserido na cabeca, intancia ja criada
      if (first){
        strcpy(cabeca->nomeVert,vert1Linha);

        // Se houver dois vertices na linha, então aloca a estrutura para o segundo vertice
        // e cria a vizinhança entre eles
        if (strcmp(vert2Linha, "\0")){
          aux = aloca_grafo();
          strcpy(aux->nomeVert,vert2Linha);
          cabeca->proxVertice = aux;
          cria_vizinho (cabeca, vert1Linha, vert2Linha);
          cria_vizinho (cabeca, vert2Linha, vert1Linha);
        }
        first = false;
      }
      // Apos a primeira interação , sao instanciados a estrutura para novos vertices
      // e encadeadas ao final do grafo
      else {

        // Verifica se o vertice ja pertence ao grafo
        if( !busca_nomeVert_no_grafo (cabeca, vert1Linha)){
          aux->proxVertice = aloca_grafo ();
          strcpy(aux->proxVertice->nomeVert,vert1Linha);
          aux = aux->proxVertice;
        }
        // Se houver dois vertices na linha, então aloca a estrutura para o segundo vertice
        // e cria a vizinhança entre eles
        if (strcmp(vert2Linha, "\0")){

          // Verifica se o vertice ja pertence ao grafo
          if( !busca_nomeVert_no_grafo (cabeca, vert2Linha)){
            aux->proxVertice = aloca_grafo ();
            strcpy(aux->proxVertice->nomeVert,vert2Linha);
            aux = aux->proxVertice;
          }

          // Cria a adjacencia entre eles no grafo
          cria_vizinho (cabeca, vert1Linha, vert2Linha);
          cria_vizinho (cabeca, vert2Linha, vert1Linha);
        }
      }
    }
    fgets (linha,2055,input);
  }

  // retorna o inicio do grafo
  return cabeca;
}


double coeficiente_agrupamento_grafo(grafo g){
  grafo vert1 = NULL, vert2 = NULL;
  double triadesAberta = 0, triadesFechadas = 0, triadesTotal = 0;
  vert1 = g;

  // Laços responsaveis pela combinação dois a dois dos vertices
  while (vert1){
    vert2 = vert1->proxVertice;
    while (vert2) {

      // Busca os vertices em comum entre vert1 e vert2, contalizando as triades
      busca_vertice_comum(vert1, vert2, &triadesAberta, &triadesFechadas);
      vert2 = vert2->proxVertice;
    }
    vert1 = vert1->proxVertice;
  }

  triadesTotal = triadesAberta + triadesFechadas;

  // Para nao existir divisão por zero
  if ((int)triadesTotal == 0){
    return 0;
  }
  // printf("triadesFechadas %lg - triadesAberta %lg\n", triadesFechadas, triadesAberta);
  return triadesFechadas / triadesTotal;
}

// Insere o vert2Linha como adjacente ao vert1Linha
void cria_vizinho (grafo cabeca, char *vert1Linha, char *vert2Linha){
  grafo aux = cabeca;
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

void printa_grafo (grafo g){
  grafo aux = g;
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


int busca_nomeVert_no_grafo (grafo g, char * vert){
  grafo atual = g;
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
  // Aloca espaço em memoria para a estrutura vertice
  verticeP v = (verticeP) malloc( sizeof(VerticeS) );
  // Caso sucesso, inicializa a estrutura
  if (v){
    v->proximo = NULL;
    strcpy (v->nomeVert, "\0");
  }
  return v;
}

grafo aloca_grafo (void){
  // Aloca espaço em memoria para a estrutura grafo
  grafo g = (grafo) malloc( sizeof(GrafoS) );
  // Caso sucesso, inicializa a estrutura
  if (g){
    g->verticeAdj = NULL;
    g->proxVertice = NULL;
    strcpy (g->nomeVert, "\0");
  }
  return g;
}

int destroi_grafo(grafo g){
  grafo lixoG = g, atualG = g;
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
  if (g){
    return 0;
  }
  return 1;
}

// Passado dois vertices g1 e g2 , procurasse um vertice adjacente aos dois, caso exista obtem-se uma
// triade aberta, se ainda g1 e g2 forem vizinhos obtem-se uma fechada
void busca_vertice_comum (grafo g1, grafo g2, double * triadesAberta, double * triadesFechadas){
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

int verifica_vizinho (grafo vert1, char * nomeVert){
  verticeP aux = vert1->verticeAdj;
  while (aux){
    if (!strcmp(aux->nomeVert,nomeVert)) return 1;
    aux = aux->proximo;
  }
  return 0;
}



// grafo escreve_grafo(FILE *output, grafo g);
