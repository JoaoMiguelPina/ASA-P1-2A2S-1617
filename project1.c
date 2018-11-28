#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*Estrutura para representar um vertice (nodulo de uma lista)*/
typedef struct vertex {
	int value;
  struct vertex *next;
} *Vertex;

/*----- Declaracao das Funcoes Auxiliares -----*/
void putVertex(Vertex v, int i);
void findHeader(Vertex v[]);
/*int free_all(Vertex vList[]);*/

/*----- Variaveis Globais -----*/
int nr_vertices, nr_edges, first, list_size;
int flag_insuf = 0, res_idx = 0;
int *entradas, *resultado;

/*----- Corpo do Programa -----*/
int main(){
  int n1, n2, i, j = 0;

  scanf("%d %d", &nr_vertices, &nr_edges);	/* Recebe a 1a linha de input*/

	list_size = nr_vertices;

  Vertex vertices_list[nr_vertices]; /*Vetor dos vertices*/

	entradas = (int *)malloc(sizeof(int)*nr_vertices);
	resultado = (int *)malloc(sizeof(int)*nr_vertices + 1);

	/*Inicializar a lista de adjacencias / Alocar vertices*/
  for(i = 0; i < nr_vertices; i++){
    vertices_list[i] = malloc(sizeof(struct vertex));
		entradas[i] = 0;
  }


	/*Recebe os restantes inputs e aloca as arestas*/
  for(i = 0; i < nr_edges; i++){
    scanf("%d %d", &n1, &n2);
    putVertex(vertices_list[n1-1], n2);
		entradas[n2-1]++;
  }

	/*Executa a ordenacao topologica*/
	while(list_size > 0){
		findHeader(vertices_list);
	}

	if(resultado[-1] == 1){
		printf("Incoerente\n");
		return 0;
	}

	else if(resultado[-1] == 2){
		printf("Insuficiente\n");
		return 0;
	}

	/*Imprime o resultado final*/
	for (i = 0; i < nr_vertices; i++)
		printf("%d ", resultado[i]);
	printf("\n");

	/*free_all(vertices_list);*/

	return 0;

}


/*----- Funcoes Auxiliares -----*/
void putVertex(Vertex v, int n) {
	/*Rotina que recebe um vertice e um inteiro e coloca
		o inteiro no value do proximo vertice disponivel*/

	Vertex nextV;

  while(v->next != NULL){
    v = v->next;
  }

  v->value = n;
	nextV = malloc(sizeof(struct vertex));
  v->next = nextV;
}


void findHeader(Vertex vList[]) {
  /* Rotina que procura e devolve o primeiro elemento do grafo
  (aquele que nao tem arcos de entrada)
  Devolve -1 caso tal vertice nao exista
  Devolve -2 caso existam mais do que um*/

  int first = -1;
  int number = 0;
  int i, idx, j=0;
  Vertex v;

	/*Regista o indice da cabeca do grafo*/
  for (i = 0; i < nr_vertices; i++) {
    if (entradas[i] == 0){
			first = i + 1;
			resultado[res_idx++] = first;
      number++;
    }
  }

	while(v != NULL) {
		v = vList[first-1];
		entradas[v->value - 1]--;
		v = v->next;
	}

	vList[first-1] = NULL;

  if(number > 1)
		resultado[-1] = 2;
	else if(number == 0)
		resultado[-1] = 1;
	else if(number == 1)
		resultado[-1] = 0;

	list_size--;
}


/*int free_all(Vertex vList[]) {*/
	/*Rotina que recebe um vetor e liberta toda a memoria la alocada*/
	/*int i;
	Vertex v = NULL, w;

	for (i = 0; i < nr_vertices; i++)
		v = vList[i];

		if(v != NULL) {
			while(v->next != NULL){
				w = v;
				v = v->next;
				free(w);
			}
			free(v);
		}
		else
			free(v);

	return 0;
}*/
