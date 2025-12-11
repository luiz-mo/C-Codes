/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/

/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max){
	return min+rand()%(max-min+1);/*max-min+1 delimita o intervalo, +min garante que o intervalo começa em min*/
}

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
long mdc (long a, long b){
	long resto; /*variavel para armazenar o resto*/
	while(b != 0){
		resto = a % b;
		a = b;
		b = resto;
	}
	return a;
}

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b){
	return(a*b)/mdc(a,b);
}

int valido_r(struct racional r){
    if(r.den != 0) /*invalido se denominador = 0*/
        return 1;
    return 0;
}

/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r (struct racional r){
	long x = mdc(r.num,r.den);
	struct racional simplificado;
	if(!valido_r(r))
        return r;
	simplificado.num = r.num/x;
	simplificado.den = r.den/x;
	if(simplificado.den < 0){ /*den < 0 inverte tanto para num>0 quanto para num<0*/
		simplificado.num *= -1;
		simplificado.den *= -1;
		}
	return simplificado;

	
}

/*nao utilizada nesse tp1*/
struct racional cria_r(long numerador, long denominador){ 
	struct racional r;
	r.num = numerador;
	r.den = denominador;
	return simplifica_r(r);
}

struct racional sorteia_r(long min, long max){
	struct racional r;
	r.num = aleat(min,max);
	r.den = aleat(min,max);
	return simplifica_r(r);
}


void imprime_r(struct racional r){
	if(!valido_r(r)){
		printf("INVALIDO");
		return;
	}
	if(r.num == 0){
		printf("0");
		return;
	}
	if(r.den == 1){
		printf("%ld", r.num);
		return;
	}
	if(r.den == r.num){
		printf("1");
		return;
	}
	printf("%ld/%ld",r.num,r.den);
}

struct racional soma_r(struct racional r1, struct racional r2){
	struct racional soma;
	long aux = (mmc(r1.den,r2.den));/*variavel auxiliar para armazenar o mmc*/
	soma.num = r1.num * aux/r1.den + r2.num * aux/r2.den;
	soma.den = aux;
	return simplifica_r(soma);
}

struct racional subtrai_r(struct racional r1, struct racional r2){
	r2.num *= -1;
	struct racional sub = soma_r(r1,r2);/*chama soma para fazer r1+(-r2)*/
	return simplifica_r(sub);
}

struct racional multiplica_r(struct racional r1, struct racional r2){
	struct racional multiplicacao;
	multiplicacao.num = r1.num * r2.num;
	multiplicacao.den = r1.den * r2.den;
	return simplifica_r(multiplicacao);
}

struct racional divide_r(struct racional r1, struct racional r2){		
	struct racional divisao;
	if(r2.num == 0){
		divisao.den = 0;
		return divisao;
	}
	divisao.num = r1.num * r2.den;
	divisao.den = r1.den * r2.num;
	return simplifica_r(divisao);
}



