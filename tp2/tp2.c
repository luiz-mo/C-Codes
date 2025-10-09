/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include "racional.h"

/* coloque aqui as funções auxiliares que precisar neste arquivo */

/*preenche o vetor com os numeros racionais lidos na entrada*/
void preenche_vetor(struct racional v[], int n){
	int i;
	long num,den;
	for(i=0;i<n;i++){
		scanf("%ld" "%ld", &num, &den);
		v[i] = cria_r(num,den);
	}
}

/*remove elemento invalido(NaN) do vetor*/
void elimina_invalido_vetor(struct racional v[], int *n, int i){
	int j;
	for(j=*n-1;j>i;j--)
		if(valido_r(v[j])){
			v[i] = v[j];
			break;
		}
	*n = j;
}

/*realiza ordenacao do pelo metodo de select sort*/
void ordena_vetor(struct racional v[], int n){
	struct racional aux;
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

/*imprime todos os elementos do vetor*/
void imprime_vetor(struct racional v[], int n){
	int i;
	printf("VETOR = ");
	for(i=0;i<n;i++){
		if (i>0)
			printf(" ");
		imprime_r(v[i]);
	}
	printf("\n");
}

/*retorna soma de todos os elementos do vetor e retorna o resultado simplificado*/
struct racional soma_vetor(struct racional v[], int n){
	struct racional soma;
	int i;
	soma = cria_r(0,1); /*inicializa soma com 0*/
	if(n>0)
		for(i=0;i<n;i++)
			soma_r(soma,v[i],&soma);
	return soma;
}

/* programa principal */
int main (){
	struct racional v[100], soma;
	int n, i;
	scanf("%d",&n);
	if(n<0 || n>100)
		return 1;
	preenche_vetor(v,n);
	imprime_vetor(v,n);
	for(i=0;i<n;i++)
		if(!valido_r(v[i]))
			elimina_invalido_vetor(v,&n,i);
	imprime_vetor(v,n);
	ordena_vetor(v,n);
    imprime_vetor(v,n);
	soma = soma_vetor(v,n);
	printf("SOMA = ");
	imprime_r(soma);
	printf("\n");
	return 0;
}
