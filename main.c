#include <stdio.h>
#include <time.h>
#define TAMANHO_MAX 1000000


typedef struct{
  int lista[TAMANHO_MAX];
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
    if(p->topo > TAMANHO_MAX - 1) return 1;
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

int main(void) {
  Pilha_Soma *pilha = (Pilha_Soma *)malloc(sizeof(Pilha_Soma));
  Pilha_Soma_init(pilha);

 // =-=-=-=-=-=-=-=
    
  clock_t before = clock();
  for(int i = 0; i <= TAMANHO_MAX; i++){
    Pilha_Soma_push(pilha, i);
  }
  clock_t dif = clock() - before;
  int msec = dif * 1000 / CLOCKS_PER_SEC;
  printf("Tempo para inserção: %f\n", (double) msec/1000);
  
 // =-=-=-=-=-=-=-=
  
  before = clock();
  long soma = 0;
  for (int i = 0; i <= TAMANHO_MAX; i++){
    soma += pilha->lista[i];
  }
  dif = clock() - before;
  msec = dif * 1000 / CLOCKS_PER_SEC;
  printf("\nTempo para adição: %f", (double) msec/1000);
  printf("\nSoma: %ld\n", soma);
 
  // =-=-=-=-=-=-=-=

  clock_t inicioSomaReversa = clock();
  long somaReversa = 0;
  for (int i = TAMANHO_MAX; i >= 0; i--){
    somaReversa += pilha->lista[i];
  }
  clock_t difSomaReversa = clock() - inicioSomaReversa;
  int tempoSimaReversa = difSomaReversa * 1000 / CLOCKS_PER_SEC;
  printf("\nTempo para adição reversa: %f", (double)tempoSimaReversa/1000);
  printf("\nSoma reversa: %ld\n", somaReversa);

  // =-=-=-=-=-=-=-=

  clock_t encontrarNum = clock();
  int numeroParaEncontrar = 78543;
  for (int i = TAMANHO_MAX; i >= 0; i--){
    if(pilha->lista[i] == numeroParaEncontrar){
      break;
    }
  }
  clock_t difProcura = clock()- encontrarNum;
  int tempoProcura = difProcura * 1000 /CLOCKS_PER_SEC;
  printf("\nTempo para encontrar 78543: %f\n", (double) tempoProcura /1000);
  
  
  // =-=-=-=-=-=-=-=
    clock_t encontrarNumReverso= clock();
    for (int i = TAMANHO_MAX; i >= 0; i--){
      if(pilha->lista[i] == numeroParaEncontrar){
        break;
      }
    }
    clock_t difProcuraReversa = clock()- encontrarNumReverso;
    int tempoProcuraReversa = difProcuraReversa * 1000 /CLOCKS_PER_SEC;
    printf("\nTempo para encontrar 78543 de forma reversa: %f\n", (double) tempoProcuraReversa /1000);
  
  return 0; 
}
