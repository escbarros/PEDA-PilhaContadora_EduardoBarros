//Eduardo Scaburi Costa Barros - PEDA

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>


#define TAMANHO 20
int adjMatrix[TAMANHO][TAMANHO];

struct aresta {
  int vertice;
  struct aresta* prox;
};

struct grafo {
  int numVertices;
  struct aresta** listaAdjacencia;
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
        //printf("%d\n", temp);
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
int menorDistancia(int dist[], bool sptSet[])
{

    int min = INT_MAX, minIndex;
 
    for (int v = 0; v < TAMANHO; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], minIndex = v;
 
    return minIndex;
}
 

void printDijkstra(int dist[])
{
    printf("Vértice \t\t Distancia\n");
    for (int i = 0; i < TAMANHO; i++) printf("%d \t\t\t\t %d\n", i, dist[i]);
}

void dijkstra(int grafo[TAMANHO][TAMANHO], int origem)
{
    int dist[TAMANHO];
 
    bool sptSet[TAMANHO]; 

    for (int i = 0; i < TAMANHO; i++) dist[i] = INT_MAX, sptSet[i] = false;

    dist[origem] = 0;
 
    for (int count = 0; count < TAMANHO - 1; count++) {
        int u = menorDistancia(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < TAMANHO; v++){
            if (!sptSet[v] && grafo[u][v] && dist[u] != INT_MAX && dist[u] + grafo[u][v] < dist[v]){
                dist[v] = dist[u] + grafo[u][v];
            }
        }
    }
 

    printDijkstra(dist);
}
 
int main(){
  struct grafo* grafo = criaGrafo(TAMANHO);

  srand(time(NULL));
  for(int i = 0; i <= TAMANHO; i++ ){
    int quantArestasAleatorias =  1+rand()%3;
    int numArestas = 0;
    while(numArestas != quantArestasAleatorias){
      int arestasAleatorias =  1+rand()%TAMANHO;
      addAdjacencia(grafo, i, arestasAleatorias);
      numArestas++;
    }
  }
  for(int j=0; j< TAMANHO; j++){
    printf("Vértice %d\n", j);
    dijkstra(adjMatrix, j);
    printf("\n\n");
  }
  return 0;
}


