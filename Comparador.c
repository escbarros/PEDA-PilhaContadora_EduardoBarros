#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000000

typedef struct{
  int items[SIZE], front, rear;
}fila;
typedef struct{
  int lista[SIZE];
  int topo;
} Pilha_Soma;


void Pilha_Soma_init(Pilha_Soma *p){
  p->topo = -1;
}
int Pilha_Soma_isEmpty(Pilha_Soma *p){
  if(p->topo < 0) return 1;
  else return 0;
}
int Pilha_Soma_isFull(Pilha_Soma *p){
    if(p->topo > SIZE - 1) return 1;
    else return 0;
}
void Pilha_Soma_push(Pilha_Soma *p, int x){
    if(Pilha_Soma_isFull(p) == 1){
      printf("A pilha já está cheia");
      return;
    }else{
      p->topo += 1;
      p->lista[p->topo] = x;
      return;
    }
}
int Pilha_Soma_remove(Pilha_Soma *p){
  if(Pilha_Soma_isEmpty(p) == 1){
    printf("A pilha está vazia");
    return NULL;  
  }else{
    int aux;
    aux = p->lista[p->topo];
    p->topo--;
    return aux;
  }
}

void init_fila(fila *p){
  p->front = -1;
  p->rear = -1;
}
void enQueue(fila *p, int value) {
  if (p->rear == SIZE - 1)
    printf("\nA fila está cheia");
  else {
    if (p->front == -1)
      p->front = 0;
    p->rear++;
    p->items[p->rear] = value;
  }
}
int deQueue(fila *p) {
  if (p->front == -1)
    printf("\nA fila está vazia");
  else {
    int aux = p->items[p->front];
    p->front++;
    if (p->front > p->rear){
      p->front = p->rear = -1;
    }
    return aux;
  }
}

void adicionaAteMilhao(fila *p){
  clock_t before = clock();
  for (int i = 1; i < SIZE +1; i++){
    enQueue(p, i);
  }
  clock_t dif = clock() - before;
  int msec = dif * 1000 / CLOCKS_PER_SEC;
  printf("Tempo para inserção até 1 milhão: %f\n", (double) msec/1000);
}
void encontraNumero(fila *p, int num){
  for (int i = 0; i < SIZE; i++){
    if(p->items[i] == num) {
      printf("\nEncontrei %ld !", p->items[i]);
      return;
    }
  }
}
void somaUmMilhao(fila *p){
  long somaTotal = 0;
  clock_t before = clock();
  for (int i = 0; i < SIZE; i++){
    somaTotal += deQueue(p);
  }
  clock_t dif = clock() - before;
  int msec = dif * 1000 / CLOCKS_PER_SEC;
  printf("\n\nSoma total: %ld",somaTotal);
  printf("\nTempo para adição: %f\n", (double) msec/1000);
}

void adicionaAteMilhaoReverso(fila *p){
  clock_t before = clock();
  for (int i = SIZE; i > 0; i--){
    enQueue(p, i);
  }
  clock_t dif = clock() - before;
  int msec = dif * 1000 / CLOCKS_PER_SEC;
  printf("\nTempo para inserção até 1 milhão de forma reversa: %f\n", (double) msec/1000);
}
void encontraNumeroReverso(fila *p, int num){
  for (int i = SIZE; i > 1; i--){
    if(p->items[i] == num) {
      printf("\nEncontrei %ld !", p->items[i]);
      return;
    }
  }
}
void somaUmMilhaoReverso(fila *p){
  long somaTotal = 0;
  clock_t before = clock();
  for (int i = SIZE; i > 0; i--){
    somaTotal += deQueue(p);
  }
  clock_t dif = clock() - before;
  int msec = dif * 1000 / CLOCKS_PER_SEC;
  printf("\n\nSoma total: %ld",somaTotal);
  printf("\nTempo para adição: %f\n", (double) msec/1000);
}

void operacoesFila() {
  fila* estruturaFila = (fila*)malloc(sizeof(fila)); 
  init_fila(estruturaFila);
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-==-
  
  adicionaAteMilhao(estruturaFila);
  clock_t before = clock();
  encontraNumero(estruturaFila, 589875);
  clock_t dif = clock() - before;
  int msec = dif * 1000 / CLOCKS_PER_SEC;
  printf("\nTempo para encontrar 123 000: %f\n", (double) msec/1000);
  somaUmMilhao(estruturaFila);
  
  // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-==-
  printf("\n-=-=-=-\tOperacoes Reversas\t-=-=-=-=\n");
  adicionaAteMilhaoReverso(estruturaFila);
  before = clock();
  encontraNumeroReverso(estruturaFila, 589875);
  dif = clock() - before;
  msec = dif * 1000 / CLOCKS_PER_SEC;
  printf("\nTempo para encontrar 589875 de forma reversa: %f\n", (double) msec/1000);
  somaUmMilhaoReverso(estruturaFila);
}
void operacoesPilha() {
  Pilha_Soma *pilha = (Pilha_Soma *)malloc(sizeof(Pilha_Soma));
  Pilha_Soma_init(pilha);

 // =-=-=-=-=-=-=-=
    
  clock_t before = clock();
  for(int i = 0; i <= SIZE; i++){
    Pilha_Soma_push(pilha, i);
  }
  clock_t dif = clock() - before;
  int msec = dif * 1000 / CLOCKS_PER_SEC;
  printf("Tempo para inserção: %f\n", (double) msec/1000);
  
 // =-=-=-=-=-=-=-=
  
  before = clock();
  long soma = 0;
  for (int i = 0; i <= SIZE; i++){
    soma += pilha->lista[i];
  }
  dif = clock() - before;
  msec = dif * 1000 / CLOCKS_PER_SEC;
  printf("\nTempo para adição: %f", (double) msec/1000);
  printf("\nSoma: %ld\n", soma);
 
  // =-=-=-=-=-=-=-=

  clock_t inicioSomaReversa = clock();
  long somaReversa = 0;
  for (int i = SIZE; i >= 0; i--){
    somaReversa += pilha->lista[i];
  }
  clock_t difSomaReversa = clock() - inicioSomaReversa;
  int tempoSimaReversa = difSomaReversa * 1000 / CLOCKS_PER_SEC;
  printf("\nTempo para adição reversa: %f", (double)tempoSimaReversa/1000);
  printf("\nSoma reversa: %ld\n", somaReversa);

  // =-=-=-=-=-=-=-=

  clock_t encontrarNum = clock();
  int numeroParaEncontrar = 78543;
  for (int i = SIZE; i >= 0; i--){
    if(pilha->lista[i] == numeroParaEncontrar){
      break;
    }
  }
  clock_t difProcura = clock()- encontrarNum;
  int tempoProcura = difProcura * 1000 /CLOCKS_PER_SEC;
  printf("\nTempo para encontrar 78543: %f\n", (double) tempoProcura /1000);
  
  
  // =-=-=-=-=-=-=-=
    clock_t encontrarNumReverso= clock();
    for (int i = SIZE; i >= 0; i--){
      if(pilha->lista[i] == numeroParaEncontrar){
        break;
      }
    }
    clock_t difProcuraReversa = clock()- encontrarNumReverso;
    int tempoProcuraReversa = difProcuraReversa * 1000 /CLOCKS_PER_SEC;
    printf("\nTempo para encontrar 78543 de forma reversa: %f\n", (double) tempoProcuraReversa /1000);
  
  return 0; 
}

int main(){
  printf("\n-=-=\tOperações fila\t-=-=\n");
  clock_t before = clock();
  operacoesFila();
  clock_t dif = clock() - before;
  int tempoFila = dif * 1000 / CLOCKS_PER_SEC;
  printf("\n-=-=\tOperações Pilha\t-=-=\n");
  before = clock();
  operacoesPilha();
  dif = clock() - before;
  int tempoPilha = dif * 1000 / CLOCKS_PER_SEC;

  printf("\nTempo total de operações fila: %d ms\nTempo total de operações fila: %d ms", tempoFila, tempoPilha);
}
