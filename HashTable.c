#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMANHO 50
#define true 1
#define false 0
#define bool int

struct item {
  int index;
  char senha[TAMANHO];
};

struct heap { // Max Heap
  struct item *vetor;
  int tamanho;
  int final;
};

void setHeap(struct heap *heap) {
  heap->vetor = (struct item *)calloc(TAMANHO, sizeof(struct item));
  heap->tamanho = TAMANHO;
  heap->final = -1;
}

void recebeSenha(char senha[]) {

  while ((getchar()) != '\n') {
  }
  printf("Digite sua senha: ");
  fgets(senha, TAMANHO, stdin);

  bool isTamanhoMax = strlen(senha) > 50;
  bool isTamanhoMin = strlen(senha) < 10;

  if (isTamanhoMax || isTamanhoMin) {
    printf("\nSua senha deve possuir entre 10 e 50 caracteres!\nClique Enter "
           "para tentar novamente");
    recebeSenha(senha);
  }
}
int getHash(char senha[]) {
  // https://www.ime.usp.br/~pf/estruturas-de-dados/aulas/st-hash.html
  int tamanhoDaSenha = strlen(senha);
  int hash = 0;

  for (int i = 0; i < tamanhoDaSenha; i++) {
    hash += senha[i] * (i + 1);
  }

  return hash % TAMANHO;
}

bool isNaTabela(struct heap *heap, char senha[]) {

  int index = getHash(senha);
  for (int i = 0; i <= heap->final; i++) {

    if (heap->vetor[i].index == index) {
      printf("Já se encontra na tabela!\nEncontrado no index: %d", i);
      return true;
    }
  }
  return false;
}

int getNodePai(i) { return (i - 1) / 2; }

bool isCheio(struct heap *heap) {

  if (heap->final >= (heap->tamanho)) {
    printf("\nHeap Cheio\n");
    return true;
  } else
    return false;
}
bool isVazio(struct heap *heap) {

  if (heap->final == -1) {
    printf("\nHeap está vazio\n");
    return true;
  }
  return false;
}
bool isNode(struct heap *heap, int i) {
  return i > getNodePai(heap->final) && i <= heap->final;
}
bool isIndexValido(struct heap *heap, int i) {
  return i >= 0 && i <= heap->tamanho;
}

int getMaxIndex(struct heap *heap, int pai, int nodeAdireita,
                int nodeAesquerda) {

  int nodePaiMaiorQueNodeAEsquerda =
      heap->vetor[pai].index > heap->vetor[nodeAesquerda].index;

  int nodeDireitoMaiorQueEsquerdo =
      heap->vetor[nodeAesquerda].index < heap->vetor[nodeAdireita].index;

  int nodeDireitoMaiorQuePai =
      heap->vetor[pai].index < heap->vetor[nodeAdireita].index;

  int direitaValido = isIndexValido(heap, nodeAdireita);

  if (nodePaiMaiorQueNodeAEsquerda) {
    if (direitaValido) {
      if (nodeDireitoMaiorQuePai) { return nodeAdireita;}
    } else {return pai;}
  } else if (direitaValido) {
    if (nodeDireitoMaiorQueEsquerdo)
      return nodeAdireita;
  } else
    return nodeAesquerda;
}

struct heap *insere(struct heap *heap, char senha[]) {

  int index = getHash(senha);
  bool isEncontrado = isNaTabela(heap, senha);

  if (isEncontrado) {
    return heap;
  } else {
    if (isCheio(heap)) {
      return heap;
    }

    heap->final += 1;

    struct item temp;
    temp.index = index;
    strcat(temp.senha, senha);
    heap->vetor[heap->final] = temp;

    int i = heap->final;

    while (i > 0 && heap->vetor[getNodePai(i)].index < heap->vetor[i].index) {

      struct item auxiliar = heap->vetor[i];
      heap->vetor[i] = heap->vetor[getNodePai(i)];
      heap->vetor[getNodePai(i)] = auxiliar;
      i = getNodePai(i);
    }

    return heap;
  }
}

void heapify(struct heap *heap, int indice) {
  if (isNode(heap, indice) || !isIndexValido(heap, indice))
    return;

  int esquerda = 2 * indice + 1;
  int direita = 2 * (indice + 1);

  int indexMaximo = getMaxIndex(heap, indice, esquerda, direita);

  if (indexMaximo != indice) {
    struct item temp = heap->vetor[indice];
    heap->vetor[indice] = heap->vetor[indexMaximo];
    heap->vetor[indexMaximo] = temp;
    heapify(heap, indexMaximo);
  }
}

struct heap *removeHeap(struct heap *heap) {
  if (isVazio(heap)) {
    return heap;
  }

  heap->vetor[0] = heap->vetor[heap->final];
  heap->vetor[heap->final].index = 0;
  memset(heap->vetor[heap->final].senha, 0, TAMANHO);
  heap->final -= 1;

  heapify(heap, 0);
  printf("\nExcluido!\n");
  return heap;
}

bool main() {
  int opcaoMenuSelecionada;
  char senha[TAMANHO];
  struct heap *heap = (struct heap *)malloc(sizeof(struct heap));

  setHeap(heap);

  while (true) {
    printf("\n\nDigite uma das seguintes opções:\n\n\t0 - Sair da aplicação\n\t"
           "1 - Inserir nova senha\n\t2 - Excluir Ultimo\n\t3 - Buscar por uma "
           "senha\n\nopção: ");
    scanf("%d", &opcaoMenuSelecionada);
    switch (opcaoMenuSelecionada) {
    case 0:
      return false;
    case 1:
      recebeSenha(senha);
      heap = insere(heap, senha);
      break;
    case 2:
      printf("\n");
      removeHeap(heap);
      break;
    case 3:
      printf("\nBuscar\n");
      recebeSenha(senha);
      bool encontrado = isNaTabela(heap, senha);
      if (!encontrado) {
        printf("Não foi encontrada a senha");
      }
      break;
    }
  }
}
