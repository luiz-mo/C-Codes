/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
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
	long resto;
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
	return (a*b)/mdc(a,b);
}

int valido_r (struct racional r){
	if(r.den == 0) /*invalido se denominador = 0*/       
		return 0;
    return 1;
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


long numerador_r (struct racional r){
	return r.num;
}

long denominador_r (struct racional r){
	return r.den;
}

struct racional cria_r (long numerador, long denominador){
	struct racional r;
    r.num = numerador;
    r.den = denominador;
    return simplifica_r(r);
}

struct racional sorteia_r (long min, long max){
    struct racional r;
    r.num = aleat(min,max);
    r.den = aleat(min,max);
    return simplifica_r(r);

}

void imprime_r (struct racional r){
	if(!valido_r(r)){
        printf("NaN");
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

int compara_r (struct racional r1, struct racional r2){
	if(!valido_r(r1) || !valido_r(r2))
		return -2;
	if(r1.num * r2.den < r2.num * r1.den)
		return -1;
	if(r1.num * r2.den > r2.num * r1.den)
		return 1;
	return 0;
}

int soma_r (struct racional r1, struct racional r2, struct racional *r3){
    long aux = (mmc(r1.den,r2.den));/*variavel auxiliar para armazenar o mmc*/
    r3->num = r1.num * aux/r1.den + r2.num * aux/r2.den;
	r3->den = aux;
	*r3 = simplifica_r(*r3);/*ja armazena simplificado para facilitar*/
	if(!valido_r(r1) || !(valido_r(r2) || r3->num == 0))
		return 0;
	return 1;
}

int subtrai_r (struct racional r1, struct racional r2, struct racional *r3){
    long aux = (mmc(r1.den,r2.den));/*variavel auxiliar para armazenar o mmc*/
    r3->num = r1.num * aux/r1.den - r2.num * aux/r2.den;
    r3->den = aux;
    *r3 = simplifica_r(*r3);/*ja armazena simplificado para facilitar*/
    if(!valido_r(r1) || !(valido_r(r2) || r3->num == 0))
        return 0;
    return 1;
}

int multiplica_r (struct racional r1, struct racional r2, struct racional *r3){
	r3->num = r1.num * r2.num;
	r3->den = r1.den * r2.den;
	*r3 = simplifica_r(*r3);/*ja armazena simplificado para facilitar*/
	if(!valido_r(r1) || !(valido_r(r2) || r3->num == 0))
			return 0;
	return 1;
}

int divide_r (struct racional r1, struct racional r2, struct racional *r3){
	r3->num = r1.num * r2.den;
    r3->den = r1.den * r2.num;
    *r3 = simplifica_r(*r3);/*ja armazena simplificado para facilitar*/
    if(!valido_r(r1) || !(valido_r(r2) || r3->num == 0))
            return 0;
    return 1;
}




