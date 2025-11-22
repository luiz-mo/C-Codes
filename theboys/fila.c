#include <stdio.h>
#include <stdlib.h>

// descreve um nodo da fila 
struct fila_nodo_t
{
	int item ;			// item associado ao nodo
	struct fila_nodo_t *prox;	// próximo nodo
};

// descreve uma fila 
struct fila_t
{
	struct fila_nodo_t *prim ;	// primeiro nodo da fila
	struct fila_nodo_t *fim;	// último nodo da fila
	int num ;			// número de itens na fila
} ;

struct fila_t *fila_cria (){
    struct fila_t *f;

    if(!(f = malloc(sizeof(struct fila_t))))
        return NULL;

    f->prim = NULL;
    f->fim = NULL;
    f->num = 0;
    return f;
}

struct fila_t *fila_destroi (struct fila_t *f){
    struct fila_nodo_t *aux, *prox;

    if(!f)
        return NULL;

    aux = f->prim;

    while(aux != NULL){
        prox = aux->prox;
        free(aux);
        aux = prox;
    }

    free(f);
    f = NULL;

    return NULL;
}

int fila_insere (struct fila_t *f, int item){
    struct fila_nodo_t *n, *aux;

    if(!f)
        return 0;

    if(!(n = malloc(sizeof(struct fila_nodo_t))))
        return 0;

    n->item = item;
    n->prox = NULL;

    /*checa se fila esta vazia ou nao*/
    if(f->num == 0)
        f->prim = n;
    else
        f->fim->prox = n;

    f->fim = n;
    f->num++;

    return 1;
}

int fila_retira (struct fila_t *f, int *item){
    struct fila_nodo_t *aux;

    if(!f || f->num == 0)
        return 0;

    aux = f->prim; /*guarda o ponteiro para o nodo para liberar depois*/
    *item = f->prim->item; /*retorna o item retirado no parametro *item*/

    f->prim = f->prim->prox; /*remove o primeiro*/
    free(aux);

    f->num--;
    if(f->num == 0)
        f->fim = NULL;

    return 1;
}

int fila_tamanho (struct fila_t *f){
    if(!f)
        return -1;

    return f->num;
}

void fila_imprime (struct fila_t *f){
    struct fila_nodo_t *aux;

    if(!f || f->num == 0)
        return;

    aux = f->prim;

    while(aux->prox != NULL){
        printf("%d ", aux->item);
        aux = aux->prox;
    }

    printf("%d", f->fim->item); /*para imprimir o ultimo sem espaco no fim*/
}
