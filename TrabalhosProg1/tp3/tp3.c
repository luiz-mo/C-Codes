/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 09/09/2025 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

struct racional **cria_vetor(int n){
	struct racional **v;
	if(!(v = malloc((sizeof(struct racional *)) * n)))
		return 0;
	return v;
}

/* coloque aqui as funções auxiliares que precisar neste arquivo */
void preenche_vetor(struct racional *v[],int n) {
	int i;
	for(i=0;i<n;i++) {
		int num, den;
		scanf("%d %d", &num, &den);
		v[i] = cria_r(num, den);
	}
}

void imprime_vetor(struct racional *v[], int n){
	int i;
	printf("VETOR = ");
	for(i=0;i<n-1;i++){
		imprime_r(v[i]);
		printf(" ");
	}
	if(n>0){
		imprime_r(v[n-1]);
	}
	printf("\n");
}

void elimina_invalidos_vetor(struct racional *v[], int *novo_tam){
	struct racional *aux;
	int i=0;
	while(i<*novo_tam)
		if(!valido_r(v[i])){
			aux = v[i];
			v[i] = v[*novo_tam-1]; /*troca o invalido com o ultimo elemento do vetor*/
			v[*novo_tam-1] = aux;
			(*novo_tam)--;
		}
		else
			i++; /*caso seja valido, continua percorrendo o vetor*/
}

/*realiza ordenacao pelo algoritmo de select sort*/
void ordena_vetor(struct racional *v[], int n){
    struct racional *aux;
    int i, j, menor;
    for(i=0;i<n-1;i++){
        menor = i;
        for(j=i+1;j<n;j++)
            if(compara_r(v[j],v[menor]) == -1)
                menor = j;
        aux = v[menor];
        v[menor] = v[i];
        v[i] = aux;
    }
}

void soma_vetor(struct racional *v[], int n, struct racional **soma){
    int i;
    *soma = cria_r(0,1); /*inicializa soma com 0*/
    for(i=0;i<n;i++)
    	soma_r(*soma,v[i],*soma);
}

void destroi_vetor(struct racional *v[], int n){
	int i;
	for(i=0;i<n;i++)
		destroi_r(&v[i]);
}

/* programa principal */
int main ()
{
	struct racional **v, *soma;
	int n, novo_tam;
	scanf("%d", &n);
	if (n < 0 || n>100)
		return 1;
	
	v = cria_vetor(n);
	preenche_vetor(v,n);
	imprime_vetor(v,n);

	novo_tam = n;
	elimina_invalidos_vetor(v,&novo_tam);
	imprime_vetor(v,novo_tam);
	
	ordena_vetor(v,novo_tam);
	imprime_vetor(v,novo_tam);

	soma_vetor(v,novo_tam,&soma);
	printf("SOMA = ");
	imprime_r(soma);
	destroi_r(&soma);
	
	printf("\n");

	destroi_vetor(v,n);
	imprime_vetor(v,novo_tam);
	free(v);
	
	printf("\n");
	return 0;
}
