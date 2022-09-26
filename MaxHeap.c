
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int tamanho = 0;

void altera(int *a, int *b)
{
  int temp = *b;
  *b = *a;
  *a = temp;
}

void heapify(int array[], int tamanho, int i)
{
  //essa função cria um max-heap a partir de uma árvore binária, 
  int maior = i; //por padrão, define o item atual como o maior
  int esq = 2 * i + 1; //calcula o valor do item a esquerda
  int dir = 2 * i + 2;//calcula o valor do item a direita
  if (esq < tamanho && array[esq] > array[maior]) //verifica se o valor da esquerda dentro do array for maior que o atual valor
    maior = esq; //define ele como maior valor
  if (dir < tamanho && array[dir] > array[maior]) //verifica se o valor da direita dentro do array for maior que o atual valor
    maior = dir; //define ele como maior valor
  if (maior != i)
  {
    altera(&array[i], &array[maior]); //muda o valor atual pelo maior valor da array
    heapify(array, tamanho, maior); //repete até o max-heap for satisfeito
  }
}

void insere(int array[], int novoItem)
{
  if (tamanho == 0) //verifica se a array ja possui algum item inserido nela
  {
    array[0] = novoItem; //adiciona o item no array
    tamanho += 1; //incrementa o tamanho
  }
  else
  {
    array[tamanho] = novoItem; // adiciona o novo item numa nova posição onde não sobre-escreverá outro item
    tamanho += 1; //incrementa o tamnaho
    for (int i = tamanho / 2 - 1; i >= 0; i--) //começa a partir de um item que não seja uma folha da árvore
    {
      heapify(array, tamanho, i);
    }
  }
}

void deleta(int array[], int num)
{
  int i;
  for (i = 0; i < tamanho; i++)
  {
    if (num == array[i]) //verifica se o valor é igual ao procurado
      break;
  }

  altera(&array[i], &array[tamanho - 1]); //troca o valor pelo ultimo inserido
  tamanho -= 1;//decrementa o tamanho do array
  for (int i = tamanho / 2 - 1; i >= 0; i--)
  {
    heapify(array, tamanho, i); //realiza o max_heap
  }
}

void printArray(int array[], int tamanho)
{
  for (int i = 0; i < tamanho; ++i) //varre a array imprimindo todos os items inseridos nela
    printf("%d ", array[i]);
  printf("\n");
}

void encontra(int array[], int valor){
    for (int i = 0; i < tamanho; ++i){//varre a array imprimindo todos os items inseridos nela
      if(array[i] == valor){//verifica se o valor é igual ao procurado        
        printf("%d ", array[i]);
        return;
      }
    }
}

int main()
{
  //gera um array que comporta 500 items
  int array[500];
  // gera uma seed aleatória
  srand(time(NULL));
  //insere 500 numeros aleatórios dentro do array
  for(int i=0; i<=500; i++){
    int valor = 1 + rand()%500;
    insere(array, valor);
  }

  printf("Array Max-Heap: ");
  printArray(array, tamanho);

  deleta(array, array[0]);

  printf("Primeiro elemento deletado: ");
  printArray(array, tamanho);

  printf("Procurando o décimo elemeto: ");
  encontra(array, array[9]);

}
