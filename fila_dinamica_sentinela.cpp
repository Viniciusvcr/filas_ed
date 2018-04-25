#include <iostream>
#include <stdlib.h>
#include <stdio.h>

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
	return f->primeiro->prox == NULL;
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
		if(vazia(f))
			f->ultimo = f->primeiro;
		free(aux);
		return 1;
	}
	return 0;
}

void inverte(fila* f){ //exercício 1
	item x;

	if(!vazia(f)){
		remove_fila(f, &x);
		inverte(f);
		insere_fila(f, x);
	}
}

void escreve(fila* f){
	celula *aux = f->primeiro->prox;

	while(aux != NULL){
		cout << aux->item.chave << " ";
		aux = aux->prox;
	}
	cout << endl;
}

item* get_first(fila* f){ //exercício 2
	if(!vazia(f)){
		item *ret = &(f->primeiro->prox->item);
		return ret;
	}else return NULL;
}

int esvazia_fila(fila* f){ //exercício 5
	item x;

	if(!vazia(f)){
		remove_fila(f, &x);
		return esvazia_fila(f);
	}else return 1;
}

void clear_screen(){
	system("cls");
}

void pause_screen(){
	system("pause");
	cout << endl;
}

int main(){
	fila A;
	int opt;
	item insere, retorno, *ret;

	inicializa(&A);
	do{
		fflush(stdin);
		clear_screen();
		cout << "[1] Vazia?" << endl;
		cout << "[2] Inserir na fila" << endl;
		cout << "[3] Remove fila" << endl;
		cout << "[4] Mostra fila" << endl;
		cout << "[5] Inverte fila" << endl;
		cout << "[6] Mostra primeiro" << endl;
		cout << "[7] Esvazia fila" << endl;
		cin >> opt;
		switch(opt){
			case 1:
				if(vazia(&A))
					cout << "LISTA VAZIA" << endl;
				else cout << "LISTA NAO VAZIA" << endl;
				pause_screen();
			break;

			case 2:
				clear_screen();
				cout << "Digite o elemento que quer inserir: ";
				cin >> insere.chave;
				insere_fila(&A, insere);
				cout << "ELEMENTO INSERIDO COM SUCESSO" << endl;
				pause_screen();
			break;

			case 3:
				if(remove_fila(&A, &retorno))
					cout << retorno.chave << " EXCLUIDO COM SUCESSO" << endl;
				else cout << "ERRO NA OPERACAO" << endl;
				pause_screen();
			break;

			case 4:
				cout << "FILA COMPLETA: ";
				escreve(&A);
				pause_screen();
			break;

			case 5:
				inverte(&A);
				cout << "FILA INVERTIDA!" << endl << "NOVA FILA: ";
				escreve(&A);
				pause_screen();
			break;

			case 6:
				ret = get_first(&A);
				if(ret != NULL)
					cout << "PRIMEIRO ELEMENTO: " << ret->chave << endl;
				else cout << "LISTA VAZIA" << endl;
				pause_screen();
			break;

			case 7:
				if(esvazia_fila(&A))
					cout << "FILA ESVAZIADA" << endl;
				pause_screen();
			break;
		}
	}while(opt != 0);
}
