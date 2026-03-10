typedef struct{
    int id;
    int prob;
    no_t *prox;
    no_t *ant;    
} no_t;

typedef struct{
    int tam;
    no_t *ini;
    no_t *fim;
} lista_t;

/*inicializa lista vazia*/
lista_t *lista_cria();

/*destroi lista*/
void lista_destroi(lista_t **l);

/*insere ordenado na lista*/
void lista_insere(lista_t *l, int id, int prob);

/*remove no da lista e retorna o no removido*/
no_t *lista_remove(lista_t *l, int id);

/*retorna o tamanho da lista*/
int lista_tamanho(lista_t *l);

/*retorna 1 se a lista estiver vazia e 0 caso contrario*/
int lista_vazia(lista_t *l);


