#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//Fila de prioridade - implementada com fila duplamente encadeada com sentinela
//Prioridade declarada na struct tipo_celula

typedef struct tipo_item{
	int chave;
}item;

typedef struct tipo_celula{
	struct tipo_item item;
	struct tipo_celula *prox;
	struct tipo_celula *ant;
	int prioridade;
}celula;

typedef struct tipo_fila_p{
	struct tipo_celula *primeiro;
}fila;

void inicializa(fila* f){
	f->primeiro = (celula*)malloc(sizeof(celula));
	f->primeiro->prox = f->primeiro;
	f->primeiro->ant = f->primeiro;
}

int vazia(fila* f){
	return f->primeiro->prox == f->primeiro;
}

void insere(fila* f, item x, int prioridade){
	celula *novo = (celula*)malloc(sizeof(celula));

	novo->prioridade = prioridade;
	novo->item = x;
	
	novo->prox = f->primeiro;
	novo->ant = f->primeiro->ant;
	f->primeiro->ant->prox = novo;
	f->primeiro->ant = novo;
}

celula* buscar(fila* f){ //Busca o elemento com maior prioridade
	celula *ptr = f->primeiro->prox;
	celula *maior = ptr;

	while(ptr != f->primeiro){
		if(ptr->prioridade > maior->prioridade){
			maior = ptr;
		}
		ptr = ptr->prox;
	}

	if(maior != f->primeiro)
		return maior;
	else return NULL;
}



int remove_fila_p(fila* f, item* retorno, int* prioridade){ //Remove o elemento com maior prioridade
	celula *ptr = buscar(f);

	if(ptr != NULL){
		ptr->ant->prox = ptr->prox;
		ptr->prox->ant = ptr->ant;
		*prioridade = ptr->prioridade;
		*retorno = ptr->item;
		free(ptr); 
		return 1;
	}
	return 0;
}

void escreve(fila* f){
	celula *ptr = f->primeiro->prox;

	while(ptr != f->primeiro){
		cout << "Item: " << ptr->item.chave << " (" << ptr->prioridade << ")" << endl;
		ptr = ptr->prox;
	}
	cout << endl;
}