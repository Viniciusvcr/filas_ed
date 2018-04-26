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

void insere_fila(fila* f, item x, int prioridade){
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

int qntd_prioridade(fila* f, int prioridade){ //exercício 1
	celula *ptr = f->primeiro->prox;
	int cont = 0;

	while(ptr != f->primeiro){
		if(ptr->prioridade == prioridade)
			cont++;	
		ptr = ptr->prox;
	}
	return cont;
}

int altera_prioridade(fila* f, int chave, int n_prioridade, int* a_prioridade){ //exercício 2
	celula *ptr;

	if(!vazia(f)){
		ptr = f->primeiro->prox;
		while(ptr != f->primeiro){
			if(ptr->item.chave == chave){
				*a_prioridade = ptr->prioridade;
				ptr->prioridade = n_prioridade;
				return 1;
			}else ptr = ptr->prox;
		}
	}
	return 0;
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
	int opt, prioridade, chave, a_priori;
	item insere, retorno;

	inicializa(&A);
	do{
		fflush(stdin);
		clear_screen();
		cout << "[1] Vazia?" << endl;
		cout << "[2] Inserir na fila" << endl;
		cout << "[3] Remove fila" << endl;
		cout << "[4] Mostra fila" << endl;
		cout << "[5] Quantidade de certa prioridade" << endl;
		cout << "[6] Alterar prioridade" << endl;
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
				cout << "Qual a prioridade? ";
				cin >> prioridade;
				insere_fila(&A, insere, prioridade);
				cout << "ELEMENTO INSERIDO COM SUCESSO" << endl;
				pause_screen();
			break;

			case 3:
				if(remove_fila_p(&A, &retorno, &prioridade))
					cout << retorno.chave << " (" << prioridade << ") EXCLUIDO COM SUCESSO" << endl;
				else cout << "ERRO NA OPERACAO" << endl;
				pause_screen();
			break;

			case 4:
				cout << "FILA COMPLETA: " << endl;
				escreve(&A);
				pause_screen();
			break;

			case 5:
				cout << "Qual prioridade? ";
				cin >> prioridade;
				cout << "Prioridade " << prioridade << ": " << qntd_prioridade(&A, prioridade) << " elementos" << endl;
				pause_screen();
			break;

			case 6:
				clear_screen();
				cout << "Digite a chave a ser alterada: ";
				cin >> chave;
				cout << "Digite a nova prioridade: ";
				cin >> prioridade;
				if(altera_prioridade(&A, chave, prioridade, &a_priori))
					cout << "Prioridade alterada de " << a_priori << " para " << prioridade << " com sucesso!" << endl;
				else cout << "ERRO NA OPERACAO" << endl;
				pause_screen();
			break;
		}
	}while(opt != 0);
}