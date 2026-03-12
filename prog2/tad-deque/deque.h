#ifndef DEQUE
#define DEQUE

struct deque_nodo_t{
    struct deque_nodo_t *ant;
    struct deque_nodo_t *prox;
    int chave;
};

struct deque_t{
    struct deque_nodo_t *ini;
    struct deque_nodo_t *fim;
    int tam;
};

struct deque_t *deque_cria();

void deque_destroi(struct deque_t **deque);

int deque_vazio(struct deque_t *deque);

int deque_tamanho(struct deque_t *deque);



#endif
