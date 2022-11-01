//Eduardo Scaburi Costa Barros - PEDA

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 100

int adjMatrix[TAMANHO][TAMANHO];
struct aresta {
  int vertice;
  struct aresta* prox;
};
struct grafo {
  int numVertices;
  int* visitado;
  struct aresta** listaAdjacencia;
};
struct fila {
  int items[TAMANHO];
  int frente;
  int fim;
};

struct aresta* criaAdjacencia(int v) {
  struct aresta* novaAdj = malloc(sizeof(struct aresta));
  novaAdj->vertice = v;
  novaAdj->prox = NULL;
  return novaAdj;
}
void initMatriz(){
  int i, j;
  for (i = 0; i < TAMANHO; i++)
    for (j = 0; j < TAMANHO; j++)
      adjMatrix[i][j] = 0;
}
struct grafo* criaGrafo(int vertices) {
  initMatriz();
  struct grafo* grafo = malloc(sizeof(struct grafo));
  grafo->numVertices = vertices;

  grafo->listaAdjacencia = malloc(vertices * sizeof(struct aresta*));

  int i;
  for (i = 0; i < vertices; i++)
    grafo->listaAdjacencia[i] = NULL;

  return grafo;
}
void addNaMatriz(int i, int j){
    adjMatrix[i][j] = 1;
    adjMatrix[j][i] = 1;
}
void addAdjacencia(struct grafo* grafo, int s, int d) {
  if(d <= 99) addNaMatriz(s, d);
  struct aresta* novaAdj = criaAdjacencia(d);
  novaAdj->prox = grafo->listaAdjacencia[s];
  grafo->listaAdjacencia[s] = novaAdj;
  novaAdj = criaAdjacencia(s);
  novaAdj->prox = grafo->listaAdjacencia[d];
  grafo->listaAdjacencia[d] = novaAdj;
}
void listaAdjacencia(struct grafo* grafo) {
  int v;
  for (v = 0; v < grafo->numVertices; v++) {
    struct aresta* temp = grafo->listaAdjacencia[v];
    int count = 0;
    printf("\n Vértice %d: ", v);
    while (temp) {
      if(count < 3){
        if(temp->vertice > TAMANHO) temp->vertice = TAMANHO;
        printf("%d -> ", temp->vertice);
      }
      count++;
      temp = temp->prox;
    }
    printf("\n");
  }
}
void printAdjMatrix() {
  int i, j;
  
  for (i = 0; i < TAMANHO; i++) {
    printf("%d: ", i);
    for (j = 0; j < TAMANHO; j++) {
      printf("%d ", adjMatrix[i][j]);
    }
    printf("\n");
  }
}


int main() {
  struct grafo* grafo = criaGrafo(TAMANHO);  
  srand(time(NULL));
  for(int i = 0; i <= TAMANHO; i++ ){
    int quantArestasAleatorias =  1+rand()%3;
    int numArestas = 0;
    while(numArestas != quantArestasAleatorias){
      int quantArestasAleatorias =  1+rand()%100;
      addAdjacencia(grafo, i, quantArestasAleatorias);
      numArestas++;
    }
  }

  DFS(grafo, 1);
  return 0;
}
