/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 * Atualizado em 09/09/2025 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* aqui vem a struct racional propriamente dita, nao modifique! */
struct racional {
  long num;          /* numerador   */
  long den;          /* denominador */
};

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/

/* Maximo Divisor Comum entre a e b      */
/* calcula o mdc pelo metodo de Euclides */
long mdc (long a, long b)
{
    long resto;
    while(b != 0){
        resto = a % b;
        a = b;
        b = resto;
    }
    return a; 
}

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b)
{
	return (a * b) / mdc(a, b);
}

/* Simplifica o número racional indicado no parâmetro.
 * Por exemplo, se o número for 10/8 muda para 5/4.
 * Retorna 1 em sucesso e 0 se r for inválido ou o ponteiro for nulo.
 * Se ambos numerador e denominador forem negativos, o resultado é positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador. */
int simplifica_r (struct racional *r)
{
    long x = mdc(r->num,r->den);
    if(!r)
        return 0;
    r->num /= x;
    r->den /= x;
    if(r->den < 0){ /*den < 0 inverte tanto para num>0 (para deixar o sinal negativo no numerador) quanto para num<0*/
        r->num *= -1;
        r->den *= -1;
    }
    return 1;
}

/* implemente as demais funções de racional.h aqui */

long numerador_r (struct racional *r){
	return r->num;
}

long denominador_r (struct racional *r){
	return r->den;
}

struct racional *cria_r (long numerador, long denominador){
	struct racional *r;
	if(!(r = malloc(sizeof(struct racional))))
		return NULL;
	r->num = numerador;
	r->den = denominador;
	simplifica_r(r);
	return r;
}

void destroi_r (struct racional **r){
	free(*r);
	*r = NULL;
}

int valido_r (struct racional *r){
	if(!r || r->den == 0 )
		return 0;
	return 1;
}

/*nao precisa chamar simplifica_r porque ja foi chamado em cria_r */
void imprime_r (struct racional *r){
	if(!r){
		printf("NULL");
		return;
	}
    if(!valido_r(r)){
        printf("NaN");
        return;
    }
    if(r->num == 0){
        printf("0");
        return;
    }
    if(r->den == 1){
        printf("%ld", r->num);
        return;
    }
    if(r->den == r->num){
        printf("1");
        return;
    }
    printf("%ld/%ld",r->num,r->den);
}

int compara_r (struct racional *r1, struct racional *r2){
    if(!valido_r(r1) || !valido_r(r2))
        return -2;
    long num1, num2, x = mmc(r1->den,r2->den);
    num1 = r1->num * x/r1->den;
    num2 = r2->num * x/r2->den;
    if(num1 < num2)
        return -1;
    if(num1 == num2)
        return 0;
    return 1;
}


int soma_r (struct racional *r1, struct racional *r2, struct racional *r3){
    if(!valido_r(r1) || (!valido_r(r2)))
        return 0;
    long aux = (mmc(r1->den,r2->den));/*variavel auxiliar para armazenar o mmc*/
    r3->num = r1->num * aux/r1->den + r2->num * aux/r2->den;
    r3->den = aux;
    simplifica_r(r3);/*ja armazena simplificado para facilitar*/
    return 1;    
}


int subtrai_r (struct racional *r1, struct racional *r2, struct racional *r3){
     if(!valido_r(r1) || (!valido_r(r2)))
        return 0;
    long aux = (mmc(r1->den,r2->den));/*variavel auxiliar para armazenar o mmc*/
    r3->num = r1->num * aux/r1->den - r2->num * aux/r2->den;
    r3->den = aux;
    simplifica_r(r3);/*ja armazena simplificado para facilitar*/
    return 1;
}


int multiplica_r (struct racional *r1, struct racional *r2, struct racional *r3){
    if(!valido_r(r1) || (!valido_r(r2)))
        return 0;
    r3->num = r1->num * r2->num;
    r3->den = r1->den * r2->den;
    simplifica_r(r3);/*ja armazena simplificado para facilitar*/
    return 1;
}

int divide_r (struct racional *r1, struct racional *r2, struct racional *r3){
    if(!valido_r(r1) || (!valido_r(r2)))
        return 0;
    r3->num = r1->num * r2->den;
    r3->den = r1->den * r2->num;
    simplifica_r(r3);/*ja armazena simplificado para facilitar*/
    return 1;
}



