#include <iostream>
#include <stdio.h>
#define TAM 51

using namespace std;

typedef struct tipo_item{
	int chave;
}item;

typedef struct tipo_fila{
	int primeiro, ultimo;
	struct tipo_item dados[TAM];
}fila;

void inicializa(fila* f){
	f->primeiro = 0;
	f->ultimo = 0;
}

int vazia(fila* f){
	return f->primeiro == f->ultimo;
}

int proximo(int pos){
	return (pos+1)%TAM;
}

int cheia(fila* f){
	return proximo(f->ultimo) == f->primeiro;
}

int insere_fila(fila* f, item x){
	if(!cheia(f)){
		f->dados[f->ultimo] = x;
		f->ultimo = proximo(f->ultimo);
		return 1;
	}
	return 0;
}

int remove_fila(fila* f, item* retorno){
	if(!vazia(f)){
		*retorno = f->dados[f->primeiro];
		f->primeiro = proximo(f->primeiro);
		return 1;
	}
	return 0;
}

void mostra_fila(fila* f){
	for(int i=f->primeiro; i!=f->ultimo; i = proximo(i)){
		cout << f->dados[i].chave << " ";
	}
	cout << endl;
}

void inverte(fila* f){ //exercício 1
	item x;

	if(!vazia(f)){
		remove_fila(f, &x);
		inverte(f);
		insere_fila(f, x);
	}
}

item* get_first(fila* f){
	if(vazia(f)) return NULL;
	return &(f->dados[f->primeiro]);
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
		cout << "[2] Cheia?" << endl;
		cout << "[3] Insere na fila" << endl;
		cout << "[4] Remove fila" << endl;
		cout << "[5] Inverte fila" << endl;
		cout << "[6] Mostra fila" << endl;
		cout << "[7] Mostra primeiro" << endl;
		cin >> opt;
		switch(opt){
			case 1:
				if(vazia(&A))
					cout << "Fila vazia" << endl;
				else cout << "Fila não vazia" << endl;
				pause_screen();
			break;

			case 2:
				if(cheia(&A))
					cout << "Fila cheia" << endl;
				else cout << "Fila nao cheia" << endl;
				pause_screen();
			break;

			case 3:
				clear_screen();
				cout << "Qual elemento inserir? ";
				cin >> insere.chave;
				if(insere_fila(&A, insere))
					cout << "Elemento inserido com sucesso" << endl;
				else cout << "Erro na insercao" << endl;
				pause_screen();
			break;

			case 4:
				if(remove_fila(&A, &retorno))
					cout << retorno.chave << " removido com sucesso" << endl;
				else cout << "Erro na remocao" << endl;
				pause_screen();
			break;

			case 5:
				inverte(&A);
				cout << "Filha invertida!" << endl << "Nova fila: ";
				mostra_fila(&A);
				pause_screen();
			break;

			case 6:
				cout << "Fila completa: " << endl;
				mostra_fila(&A);
				pause_screen();
			break;

			case 7:
				ret = get_first(&A);
				cout << "PRIMEIRO ELEMENTO: " << ret->chave << endl;
				pause_screen();
			break;
		}
	}while(opt != 0);
}
