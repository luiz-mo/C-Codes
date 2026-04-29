#include <stdlib.h>

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define ALT(x) ((x) == NULL ? 0 : (x)->altura)

typedef struct no {
    int chave;
    int fb;
    int altura;
    struct no *pai;
    struct no *esq;
    struct no *dir;
} no;


typedef struct {
    no *raiz;
} arvore;


no* tree_insert(arvore *t, no *z) {
    no *x, *y;

    x = t->raiz;
    y = NULL;
    while(x != NULL) {
        y = x;
        if(z->chave < x->chave)
            x = x->esq;
        else
            x = x->dir;
    }
    z->pai = y;
    if(y == NULL)
        t->raiz = z;
    else if(z->chave < y->chave)
        y->esq = z;
    else
        y->dir = z;
    return y;
}


void transplant(arvore *t, no *u, no *v) {
    if(u->pai == NULL)
        t->raiz = v;
    else if(u == u->pai->esq)
        u->pai->esq = v;
    else
        u->pai->dir = v;
    if(v != NULL)
        v->pai = u->pai;
}


no* tree_minimum(no *x) {
    while(x->esq != NULL)
        x = x->esq;
    return x;
}


no* tree_delete(arvore *t, no *z) {
    no *x, *y;

    x = z->pai;
    if(z->esq == NULL)
        transplant(t, z, z->dir);
    else if(z->dir == NULL)
        transplant(t, z, z->esq);
    else {
        y = tree_minimum(z->dir);
        x = y->pai;
        if(y != z->dir) {
            transplant(t, y, y->dir);
            y->dir = z->dir;
            y->dir->pai = y;
        }
        transplant(t, z, y);
        y->esq = z->esq;
        y->esq->pai = y;
    }
    return x;
}


no* rot_esq(no *p) {
    no *q;

    q = p->dir;
    p->dir = q->esq;
    if(p->dir)
        p->dir->pai = p;
    q->esq = p;
    q->pai = p->pai;
    p->pai = q;    
    p->fb = p->fb - 1 - MAX(q->fb,0);
    q->fb = q->fb - 1 + MIN(p->fb,0);
    return q;
}


no* rot_dir(no *p) {
    no *q;

    q = p->esq;
    p->esq = q->dir;
    if(p->esq)
        p->esq->pai = p;
    q->dir = p;
    q->pai = p->pai;
    p->pai = q;    
    p->fb = p->fb + 1 - MIN(q->fb,0);
    q->fb = q->fb + 1 + MAX(p->fb,0);
    return q;
}


no* rot_esqdir(no *p) {
    p->esq = rot_esq(p->esq);
    p->esq->pai = p;
    return rot_dir(p);
}


no* rot_diresq(no *p) {
    p->dir = rot_dir(p->dir);
    p->dir->pai = p;
    return rot_esq(p);
}

no* avl_balance(no *x) {
    no *y;
    y = x;

    if(x->fb < -1)
        if(x->esq->fb > 0)
            y = rot_esqdir(x);
            
        else
            y = rot_dir(x);
    else if(x->fb > 1)
        if(x->dir->fb < 0)
            y = rot_diresq(x);
        else
            y = rot_esq(x);
    return y;
}


void troca_filho(arvore *t, no *u, no *v) {
    if(u->pai == NULL)
        t->raiz = v;
    else if(u == u->pai->esq)
        u->pai->esq = v;
    else
        u->pai->dir = v;

    if(v != NULL)
        v->pai = u->pai;
}


void avl_insert(arvore *t, no *z) {
    int fb;
    no *x, *y;

    z->fb = 0;
    x = tree_insert(t, z);
    while(x != NULL) {
        if(x->pai == NULL)
            break;

        if(x == x->pai->esq)
            x->pai->fb--;
        else
            x->pai->fb++;

        y = avl_balance(x);

        if(y != x) {
            troca_filho(t, x, y);
            break;
        }
        
        x = x->pai;
    }        
}

void avl_delete(arvore *t, no *z) {
    no *x, *y, *p;
    
    x = tree_delete(t, z);
    while(x != NULL) {
        y = avl_balance(x);
        if(y != x) {
            troca_filho(t, x, y);
            x = y;
        }
        x = x->pai;
    }        
}
