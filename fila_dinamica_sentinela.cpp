#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct tipo_item{
	int chave;
}item;

typedef struct tipo_celula{
	struct tipo_item item;
	struct tipo_celula *prox;
}celula;

typedef struct tipo_fila{
	struct tipo_celula *primeiro;
	struct tipo_celula *ultimo;
}fila;

void inicializa(fila* f){
	f->primeiro = (celula*)malloc(sizeof(celula));
	f->ultimo = f->primeiro;
	f->ultimo->prox = NULL;
}

int vazia(fila* f){
	return f->primeiro == NULL;
}

void insere_fila(fila* f, item x){
	celula *novo = (celula*)malloc(sizeof(celula));

	novo->item = x;
	novo->prox = f->ultimo->prox;
	f->ultimo->prox = novo;
	f->ultimo = novo;
}

int remove_fila(fila* f, item* retorno){
	celula *aux;

	if(!vazia(f)){
		aux = f->primeiro->prox;
		*retorno = aux->item;
		f->primeiro->prox = aux->prox;
		free(aux);
		return 1;
	}
	return 0;
}

void escreve(fila* f){
	celula *aux = f->primeiro->prox;

	while(aux != NULL){
		cout << aux->item.chave << " ";
		aux = aux->prox;
	}
	cout << endl;
}