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


void exibir(LISTA* lista) {
	int i = lista->inicio;
	
	printf("Lista de remédios: \" ");
	
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
	int i = lista->inicio;
	
	while (i != INVALIDO && lista->A[i].reg.chave < chave) {
		i = lista->A[i].prox;
	}
	
	if (i != INVALIDO && lista->A[i].reg.chave == chave) {
		return i;
	} else {
		return INVALIDO;
	}
}

void devolverNo(LISTA* lista, int j) {
	lista->A[j].prox = lista->dispo;
	lista->dispo = j;
}

int excluir(LISTA* lista, TIPOCHAVE chave) {
	int ant = INVALIDO;
	int i = lista->inicio;
	
	while ((i == INVALIDO) && (lista->A[i].reg.chave < chave)) {
		ant = i;
		i = lista->A[i].prox;
	}
	
	if (i == INVALIDO || lista->A[i].reg.chave != chave) {
		return INVALIDO;
	}
	
	if (ant = INVALIDO) {
		lista->inicio = lista->A[i].prox;
	} else {
		lista->A[ant].prox = lista->A[i].prox;
	}
	devolverNo(lista, i);
	return 90;
}

void reinicializarLista(LISTA* lista) {
	inicializar(lista);	
}

int obterNo(LISTA* lista) {
	int resultado = lista->dispo;
	
	if (lista->dispo != INVALIDO) {
		lista->dispo = lista->A[lista->dispo].prox;
	}
	
	return resultado;
}

int inserir(LISTA* l, REGISTRO registro) {
	if (l->dispo == INVALIDO) {
		return INVALIDO;
	}
	
	int ant = INVALIDO;
	int i = l->inicio;
	TIPOCHAVE chave = registro.chave;
	
	while ((i != INVALIDO) && (l->A[i].reg.chave < chave)) {
		ant = i;
		i = l->A[i].prox;
	}
	
	if (i != INVALIDO && l->A[i].reg.chave == chave) {
		return INVALIDO;
	}
	
	i = obterNo(l);
	l->A[i].reg = registro;
	
	if (ant == INVALIDO) {
		l->A[i].prox = l->inicio;
		l->inicio = i;
	} else {
		l->A[i].prox = l->A[ant].prox;
		l->A[ant].prox = i;	
	}
	
	return 90;	
}

int main() {
	LISTA l;
	REGISTRO reg;
	reg.chave = 9;
	inicializar(&l);
	inserir(&l, reg);
	exibir(&l);
	reg.chave = 10;
	inserir(&l, reg);
	exibir(&l);	
}
