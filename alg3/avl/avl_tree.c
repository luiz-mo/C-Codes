#include <stdio.h>
#include <stdlib.h>

#include "avl_tree.h"

avl_node *l_rotate(avl_node *p){
    avl_node *q;

    q = p->right;
    p->right = q->left;

    if(p->right != NULL)
        p->right->p = p;

    q->left = p;

    q->p = p->p;
    p->p = q;

    p->height = 1 + MAX(HEIGHT(p->left),HEIGHT(p->right));
    q->height = 1 + MAX(HEIGHT(q->left),HEIGHT(q->right));

    return q;
}

avl_node *r_rotate(avl_node *p){
    avl_node *q;

    q = p->left;
    p->left = q->right;

    if (p->left != NULL)
        p->left->p = p;
    
    q->right = p;

    q->p = p->p;
    p->p = q;

    p->height = 1 + MAX(HEIGHT(p->left), HEIGHT(p->right));
    q->height = 1 + MAX(HEIGHT(q->left), HEIGHT(q->right));

    return q;
}

avl_node *lr_rotate(avl_node *p){
    p->left = l_rotate(p->left);
    return r_rotate(p);
}

avl_node *rl_rotate(avl_node *p){
    p->right = r_rotate(p->right);
    return l_rotate(p);
}

avl_node *avl_balance(avl_node *r){
    int fb;
    avl_node *y;
    y = r;
    fb = HEIGHT(r->right) - HEIGHT(r->left);

    if(fb < -1){
        if(HEIGHT(r->left->left) < HEIGHT(r->left->right))
            y = lr_rotate(r);
        else
            y = r_rotate(r);
    }
    else if(fb > 1){
        if(HEIGHT(r->right->right) < HEIGHT(r->right->left))
            y = rl_rotate(r);
        else
            y = l_rotate(r);
    }

    return y;
}

avl_t *avl_create(){
    avl_t *t;

    if(!(t = malloc(sizeof(avl_t))))
        return NULL;

    t->root = NULL;
    return t;
}

avl_node *node_create(int key){
    avl_node *n;

    if(!(n = malloc(sizeof(avl_node))))
        return NULL;

    n->p = NULL;
    n->left = NULL;
    n->right = NULL;
    n-> key = key;
    n->height = 0;

    return n;
}

void inorder_avl_walk(avl_node *x){
    if(x != NULL){
        inorder_tree_walk(x->left);
        printf("%d", x->key);
        inorder_tree_walk(x->right);
    }
}

void preorder_avl_walk(avl_node *x){
    if(x != NULL){
        preorder_tree_walk(x->left);
        preorder_tree_walk(x->right);
        printf("%d", x->key);
    }
}

void postorder_avl_walk(avl_node *x){
    if(x != NULL){
        printf("%d", x->key);
        postorder_tree_walk(x->left);
        postorder_tree_walk(x->right);
    }
}

avl_node *avl_search(avl_node *x, int k){
    while(x != NULL && x->key != k){
        if(x->key > k)
            x = x->left;
        else
            x = x->right;
    }

    return x;
}

avl_node *avl_maximum(avl_node *x){
    while(x != NULL)
        x = x->right;

    return x;
}

avl_node *avl_minimum(avl_node *x){
    while(x != NULL)
        x = x->left;

    return x;
}

avl_node *avl_successor(avl_node *x){
    avl_node *y;

    if(x->right != NULL)
        return tree_minimum(x->right);

    y = x->p;

    while(y != NULL && x == y->right){
        x = y;
        y = y->p;
    }

    return y;
}

avl_node *tree_insert(avl_t *t, avl_node *z){
    avl_node *x, *y;
    x = t->root;
    y = NULL;
    
    while(x != NULL){
        y = x;
        if(z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->p = y;

    if(y == NULL)
        t->root = z;
    else if(z->key < y->key)
        y->left = z;
    else
        y->right = z;

    return z->p;
}
    

void avl_insert(avl_t *t, avl_node *z){
    avl_node *x, *r;
    int fb;

    x = tree_insert(t,z);

    if(x != NULL)
        x->height = 1 + MAX(HEIGHT(x->left),HEIGHT(x->right));

    while(x != NULL){
        r = avl_balance(x);

        if(r != x){
            if(r->p == NULL)
                t->root = r;
            else if(r->p->left == x)
                r->p->left = r;
            else
                r->p->right = r;
        }

        x = r->p;
        if(x != NULL)
            x->height = 1 + MAX(HEIGHT(x->left),HEIGHT(x->right));
    }
}

void transplant(avl_t *t, avl_node *u, avl_node *v){
    if(u->p == NULL)
        t->root = v;
    else if(u == u->p->left)
        u->p->left = v;
    else
        u->p->right = v;
    
    if(v != NULL)
        v->p = u->p;
}

avl_node *avl_delete(avl_t *t, avl_node *z){

}