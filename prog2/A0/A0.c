#include <stdio.h>
#include <stdlib.h>

struct robo{
    int id;
    int ciclos;
    struct robo *prox;
};

struct lista{
    struct robo *ini;
    struct robo *fim;
    int tam;
};

int lista_vazia(struct lista *l){
    if(l->tam == 0)
        return 1;

    return 0;
}

void lista_imprime(struct lista *l){
    struct robo *aux;

    if(lista_vazia(l))
        printf("lista vazia\n");

    aux = l->ini;

    if(l->tam == 1)
        printf("robo %d precisa de mais %d ciclos\n", l->ini->id, l->ini->ciclos);

    while(aux != l->fim){
        printf("robo %d precisa de mais %d ciclos\n", aux->prox->id, aux->prox->ciclos);
        aux = aux->prox;
    }

}

struct lista *lista_cria(){
    struct lista *l;
    l = malloc(sizeof(struct lista));
    
    l->ini = NULL;
    l->fim = NULL;
    l->tam = 0;

    
    return l;
}

struct lista *lista_destroi(struct lista *l){
    struct robo *aux, *prox;

    aux = l->ini;

    while(aux != l->fim){
        prox = aux->prox;
        free(aux);
        aux = prox;
    }

    free(l->fim);
    free(l);
    l = NULL;

    return l;
}

void lista_insere(struct lista *l, int id, int ciclos){
    struct robo *r;

    r = malloc(sizeof(struct robo));

    r->id = id;
    r->ciclos = ciclos;

    if(lista_vazia(l)){
        l->ini = r;
        l->fim = r;
        l->ini->prox = r;
        l->fim->prox = r;
        l->tam++;
        
        return;
    }

    l->fim->prox = r;
    l->fim = r;
    r->prox = l->ini;
    l->tam++;
}

struct robo *lista_remove(struct lista *l, int id){
    struct robo *aux, *prox;

    aux = l->ini;

    /*caso 1: remover do inicio*/
    if(aux->id == id){
        l->ini = l->ini->prox;
        l->fim->prox = l->ini;
        l->tam--;

        return aux;
    }

    while(prox->id != id){
        aux = aux->prox;
        prox = aux->prox;
    }

    /*caso 2: remover do fim*/
    if(prox == l->fim){
        aux->prox = l->ini;
        l->tam--;

        return prox;
    }

    /*caso 3: remover do meio*/
    aux->prox = aux->prox->prox;
    l->tam--;

    return prox;
}

void executa_ciclo(struct lista *l){
    struct robo *aux, *prox, *rm;
    int recargas = 0, flag = 0; 
    /*flag serve para quando tamanho for 1, garantir que so faz uma recarga*/

    if(lista_vazia(l))
        printf("lista esta vazia\n");

    aux = l->ini;

    while((l->tam == 1 && !flag) || (aux != l->fim && recargas < 2)){
        aux->ciclos--;
        printf("robo %d recebeu recarga parcial, restam %d ciclos\n", aux->id, aux->ciclos);
        prox = aux->prox;
        if(l->tam == 1)
            flag = 1;
        if(l->ini->ciclos == 0){
            rm = lista_remove(l,aux->id);
            printf("robo %d removido\n", rm->id);
            recargas++;
            free(rm);
        }
        aux = prox;
    }
}

int main(){
    int executar, id, ciclos, operacao;
    struct lista *l;

    l = lista_cria();
    

    executar = 1;

    while(executar){
        printf("Digite o numero correspondente a operacao desejada\n\n");
        printf("1.Cadastrar novo robo\n");
        printf("2.Executar ciclo de recarga\n");
        printf("3.Encerrar programa\n\n");

        scanf("%d", &operacao);

        switch(operacao){
            case 1:
                printf("\nDigite o id do robo a ser cadastrado\n");
                scanf("%d", &id);

                printf("Digite o numero de ciclos necessarios para o robo\n");
                scanf("%d", &ciclos);
                lista_insere(l,id,ciclos);
                break;
            case 2:
                executa_ciclo(l);
                break;
            case 3:
                executar = 0;
        }
    }

    

    return 0;
}