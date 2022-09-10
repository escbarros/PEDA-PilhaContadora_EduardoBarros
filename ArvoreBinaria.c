
//Eduardo Scaburi Costa Barros - PEDA - Árvore Binária
#include <stdio.h>
#include <stdlib.h>

struct Item{
	struct Item* esquerda;
	int valor;
	struct Item* direita;
};


struct Item* novoItem(int valor){
	struct Item* auxiliar = (struct Item*)malloc(sizeof(struct Item));
	auxiliar->esquerda = NULL;
	auxiliar->valor = valor;
	auxiliar->direita = NULL;
  printf("\n\t%d", valor);

	return auxiliar;
}

void PostOrder(struct Item* raiz){
	if(raiz==NULL)
		return;

	PostOrder(raiz->esquerda);
	PostOrder(raiz->direita);
	printf("%d ",raiz->valor);
}
void InOrder(struct Item* raiz){
	if(raiz==NULL)
		return;

	InOrder(raiz->esquerda);
	printf("%d ",raiz->valor);
	InOrder(raiz->direita);
}
void PreOrder(struct Item* raiz){
	if(raiz==NULL)
		return;

	printf("%d ",raiz->valor);
	PreOrder(raiz->esquerda);
	PreOrder(raiz->direita);
}

struct Item* insereArvore(struct Item* raiz,int valor){
	if(raiz==NULL)
		raiz =  novoItem(valor);

	else if(valor <= raiz->valor)
		raiz->esquerda = insereArvore(raiz->esquerda,valor);
	
	else raiz->direita = insereArvore(raiz->direita,valor);

	return raiz;

}

void transversalidade(struct Item* raiz){
	printf("\n\nPreOrder:\t"); PreOrder(raiz);
	printf("\n\nInorder:\t"); InOrder(raiz);
	printf("\n\nPostOrder:\t"); PostOrder(raiz);
}

int main(){
	struct Item* raiz = NULL;
  int aleatorio = rand() % 26; if(aleatorio < 10) aleatorio = 10;
  int arrayVertices[aleatorio];
  
  printf("\nArray de Vertices:\n [");
  for(int i = 0; i <= aleatorio; i++){
	  int numGerado = rand()%1000000;
    arrayVertices[i] = numGerado;
    printf("%d, ", arrayVertices[i]);
    raiz = insereArvore(raiz,numGerado);
  }
  printf("]\n");
	transversalidade(raiz);

	return 0;
}
