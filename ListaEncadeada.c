#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAMANHO_MIN 200000


struct item {
  int valor;
  struct item* proximo_item;
};

void insere(struct item** encabecado, int valor) {
  struct item* novo_item = (struct item*)malloc(sizeof(struct item));
  novo_item->valor = valor;
  novo_item->proximo_item = (*encabecado);
  (*encabecado) = novo_item;
}

void deleta(struct item** encabecado) {
  clock_t before = clock();
  struct item* atual = *encabecado;
   struct item* proximo;
 
   while (atual != NULL)
   {
       proximo = atual->proximo_item;
       free(atual);
       atual = proximo;
   }
   
  *encabecado = NULL;
  clock_t dif = clock() - before;
  int msec = dif * 1000 / CLOCKS_PER_SEC;
  printf("\nTempo para DELETAR a lista encadeada: %f\n", (double) msec/1000);
}

int procura(struct item** encabecado, int valor) {
  struct item* item_atual = *encabecado;
  while (item_atual != NULL) {
    if (item_atual->valor == valor) return 1;
    item_atual = item_atual->proximo_item;
  }
  return 0;
}

void reverte(struct item** encabecado) {
    clock_t before = clock();
    struct item* anterior = NULL;
    struct item* atual = *encabecado;
    struct item* proximo = NULL;
    while (atual != NULL) {
        proximo = atual->proximo_item;
        atual->proximo_item = anterior;
        anterior = atual;
        atual = proximo;
    }
    *encabecado = anterior;
    clock_t dif = clock() - before;
    int msec = dif * 1000 / CLOCKS_PER_SEC;
    printf("\nTempo para REVERTER a lista encadeada: %f\n", (double) msec/1000);
}

int itemMeio(struct item** encabecado){
  clock_t before = clock();
  struct item* atual = *encabecado;
  for(int i = 0; i <= (TAMANHO_MIN/2)+1; i++){
    atual = atual->proximo_item;
  }
  clock_t dif = clock() - before;
  int msec = dif * 1000 / CLOCKS_PER_SEC;
  printf("\nTempo para encontrar o item do meio na lista encadeada: %f\n", TAMANHO_MIN, (double) msec/1000);
  return atual->valor;
}


int main() {
  struct item* comeco = NULL;

  clock_t before = clock();
  for(int i= 0; i<= TAMANHO_MIN; i++){
    int aleatorio = rand() % 1000000;
    insere(&comeco, aleatorio);
  }
  clock_t dif = clock() - before;
  int msec = dif * 1000 / CLOCKS_PER_SEC;
  printf("Tempo para inserção de %d items na lista encadeada: %f\n", TAMANHO_MIN, (double) msec/1000);

  int meio = itemMeio(&comeco);
  printf("Item do meio da lista encadeada:%d\n", meio);

  // Reverte toda a lista encadeada
  reverte(&comeco);
  // Deleta toda a lista encadeada
  deleta(&comeco);

}
