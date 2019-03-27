#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define INVALIDO -404

typedef int TIPOCHAVE;

typedef struct {
	TIPOCHAVE chave;
} REGISTRO;

typedef struct {
	REGISTRO reg;
	int prox;
} ELEMENTO;

typedef struct {
	ELEMENTO A[MAX];
	int inicio;
	int dispo;
} LISTA;

void inicializar(LISTA* lista) {
	int i;
	lista->inicio = INVALIDO;
	lista->dispo = 0;
	
	for (i = 0; i < MAX - 1; i++) {
		lista->A[i].prox = i + 1;
	}
	
	lista->A[MAX - 1].prox = INVALIDO;	
}

bool carregar(LISTA*) {
	
}

void exibir(LISTA* lista) {
	int i = lista->inicio;
	
	printf("Lista de remédios: ");
	
	while (i != INVALIDO) {
		printf("%d ", lista->A[i].reg.chave);
		i = lista->A[i].prox;
	}
	printf("\"\n");	
}

int tamanho(LISTA* lista) {
	int i = lista->inicio;
	int tam = 0;
	
	while (i != INVALIDO) {
		tam++;
		i = lista->A[i].prox;
	}
	return tam;	
}

int buscar(LISTA* lista, TIPOCHAVE chave) {
	
}

bool excluir(LISTA* lista, TIPOCHAVE chave) {

}

void reinicializarLista(LISTA* lista) {
	
}

bool inserir(LISTA* l, REGISTRO registro) {
	
}

int main() {
	LISTA l;
	REGISTRO reg;
	reg.chave = 9;
	inicializar(&l);
	exibir(&l);	
}
