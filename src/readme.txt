Trabalho 1 de grafos
Aluno: Julio Cesar P. Parodi
GRR: 20166160

EXECUTANDO O PROGRAMA
  Após compilação, executar :

  ./teste < arquivo-entrada.txt , onde:

  ./teste é o produto da compilação e
  arquivo-entrada.txt é o arquivo de entrada contendo o grafo representado de acordo com a especificação.


OBJETIVO DO TRABALHO
    O algoritmo tem como entrada um arquivo texto representando um grafo, e saída o coeficiente de agrupamento, sendo o número de tríades fechadas dividido pelo número total de tríades (fechadas mais as abertas), logo o problema é contabilizar o número de triades abertas e fechadas contidas no grafo.

ESTRUTURA
    A estrutura implementada para o armazenamento dos dados é uma lista de adjacência, onde cada vértice pertencente ao grafo recebe uma lista encadeada com seus vértices adjacentes (vizinhos). As listas sao encadeadas de acordo em que os vertices são lidos.
    Cada vértice será representado pela struct grafo (GrafoS), e cada vizinho é encadeado com a struct vertice (VerticeS).
    A lista é uma ótima forma de otimizar o espaço em memória e a medida que sao lidos os vertices a estrutura cresce dinamicamente, sendo um dos motivos para a escolha dessa forma de representação.
    
    - Dado um grafo G, em que V(G) = {a,b,c} e E(G) = {(a,b),(b,c), (c,a)}, sua representação em memoria é da seguinte forma:
     a -> b, c
     b -> c, a
     c -> a, b

    - Alterando ṕara o nome das estruturas :
     GrafoS -> VerticeS, VerticeS
	v
     GrafoS -> VerticeS, VerticeS
	v
     GrafoS -> VerticeS, VerticeS

    - Sendo a estrutura GrafoS:
	typedef struct grafo {
  		char nomeVert[1024];           
  		struct vertice *verticeAdj;   
  		struct grafo *proxVertice;     
	} GrafoS;
	
    - E a estrutura VerticeS:
	typedef struct vertice {
 		char nomeVert[1024];           
  		struct vertice *proximo;       
	} VerticeS;

     - As estruturas são conectadas pelas seguintes variaveis:
	GrafoS e GrafoS,conectadas pelo ponteiro GrafoS.proxVert;
	GrafoS e VerticeS, pelo ponteiro GrafoS.verticeAdj;
	VerticeS e VerticeS, pelo ponteiro VerticeS.proximo;

FUNCIONAMENTO DO ALGORITMO
  Função le_grafo()
    Primeiramente o arquivo texto de entrada é lido linha por linha, onde a linha pode possuir até dois vertices,cada linha entao é processada por proc_linha(), que extrai o nome dos vertices, caso não tenha vertices nada é feito, se existir um vertice na linha é criado uma estrutura GrafoS e encadeada no final da estrutura contruida até o momento e por fim se existiram dois vertices, por exemplo A e B, onde formam uma aresta. Para este caso são criadas duas estruturas grafoS uma para A e outra para B e postas no grafo , em seguida é chamada a função cria_vizinho(), que cria uma estrutura vérticeS para B e o encadeia na estrutura grafoS de A , o mesmo para A que é posto na estrutura grafoS de B, por isso é feita duas chamadas de cria_vizinho() alternando a ordem dos dois vertices passados como parametro.
    A cada vertice lido é verificado se existe no grafo com a funçao busca_nomeVert_no_grafo(), se estiver contido no grafo ,nada é feito ,se não é criada uma instancia do vertice e encadeada no grafo.

  Função coeficiente_agrupamento()
    Após o prenchimento da estrutura, é chamada a função coeficiente_agrupamento(), realizando uma busca na estrutura para contabilizar as tríades.
    É feita uma combinação dos vértices no grafo, dois a dois, onde cada combinação é passada para a função busca_vertice_comum(), que busca um vértice em comum aos dois, caso tenha, existe uma tríade aberta, então é verificado se os vértices combinados são vizinhos com a função verifica_vizinho(), se sim, a tríade aberta torna-se uma tríade fechada.
    O retorno da função é o número de tríades fechadas dividida pelo total de tríades.

  Função destroi_grafo()
    Ao final do programa toda estrutura é percorrida e liberado os espaços de memória alocados.
