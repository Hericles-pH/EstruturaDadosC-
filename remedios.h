#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define INVALIDO -404

typedef int TIPOCHAVE;

typedef struct {
	TIPOCHAVE chave;
	int codigo;
	char nomeC[50];
	char detentor[50];
	char pais[50];
	char validade[50];
	int preco;
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
	
	printf("Remedios: ");
	
	while (i != INVALIDO) {
		printf("\n");
		printf("%d ", lista->A[i].reg.codigo);
		printf("%s ", lista->A[i].reg.nomeC);
		printf("%s ", lista->A[i].reg.detentor);
		printf("%s ", lista->A[i].reg.pais);
		printf("%s ", lista->A[i].reg.validade);
		printf("%d ", lista->A[i].reg.preco);
		i = lista->A[i].prox;
	}
	printf("\n");	
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
	return 1;
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
	return 0;
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

int buscaSeq(TIPOCHAVE ch, LISTA* lista, int *ant){
  	*ant = INVALIDO;
  	int i = lista->inicio;
  	
	while ((i != INVALIDO) && (lista->A[i].reg.chave < ch)) {
    	*ant = i;
    	i = lista->A[i].prox;
  	}
  	
	if ((i != INVALIDO) && (lista->A[i].reg.chave == ch)) {
		return i;
	}
  	return INVALIDO;
}

int inserir(LISTA* l, REGISTRO registro) {
	registro.chave = registro.codigo;
	if (l->dispo == INVALIDO) {
		return INVALIDO;
	}
	
	int ant, i;
    
	i = buscaSeq(registro.chave, l, &ant);
    
	if (i != INVALIDO) {
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
    return 0;	
}

int carregar(LISTA* lista) {
	FILE *farq = fopen("remedios.txt", "r");
	
	if (farq == NULL) {
		return INVALIDO;
	}

	int codigo;
	char nomeC[50];
	char detentor[50];
	char pais[50];
	char validade[50];
	int preco;
	
	inicializar(lista);
	
	while (fscanf(farq, "%d %s %s %s %s %d", &codigo, &nomeC, &detentor, &pais, &validade, &preco) != EOF) {	
	
	REGISTRO registro;
	registro.codigo = codigo;
	int i = 0;
	for (i; i < sizeof(registro.nomeC); i++) {
		registro.nomeC[i] = nomeC[i];	
	}
	i = 0;
	for (i; i < sizeof(registro.detentor); i++) {
		registro.detentor[i] = detentor[i];	
	}
	i = 0;
	for (i; i < sizeof(registro.nomeC); i++) {
		registro.pais[i] = pais[i];	
	}
	i = 0;
	for (i; i < sizeof(registro.validade); i++) {
		registro.validade[i] = validade[i];	
	}
	i = 0;
	registro.preco = preco;
	
	inserir(lista, registro);
	
	}
	
	exibir(lista);
	
	fclose(farq);
	return 0;
}

void cadastroManual(LISTA* lista) {
	REGISTRO registro;
	printf("\n\n\nBEM VINDO AO CADASTRO\n");
	printf("Digite o codigo do rememdio: \n");
	scanf("%d", &registro.codigo);
	printf("Digite o nome comercial do remedio: \n");
	scanf("%s", &registro.nomeC);
	printf("Digite o detentor do remedio: \n");
	scanf("%s", &registro.detentor);
	printf("Digite a validade do remedio: \n");
	scanf("%s", &registro.validade);
	printf("Digite o pais do remedio: \n");
	scanf("%s", &registro.pais);
	printf("Digite o preco do remedio: \n");
	scanf("%d", &registro.preco);
	
	inserir(lista, registro);
}

int main(){
	LISTA lista;
	inicializar(&lista);
	carregar(&lista);
	cadastroManual(&lista);
	exibir(&lista);
}



