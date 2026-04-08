#include <stdio.h>
#include <stdlib.h>


#include "bst.h"

tree_t *tree_create(){
    tree_t *t;

    if(!(t = malloc(sizeof(tree_t))))
        return NULL;

    t->root = NULL;
    t->tamanho = 0;

    return t;
}

node_t *node_create(int key){
    node_t *n;

    if(!(n = malloc(sizeof(node_t))))
        return NULL;

    n->p = NULL;
    n->key = key;
    n->left = NULL;
    n->right = NULL;
}

void inorder_tree_walk(node_t *x){
    if(x != NULL){
        inorder_tree_walk(x->left);
        printf("%d", x->key);
        inorder_tree_walk(x->right);
    }
}

void preorder_tree_walk(node_t *x){
    if(x != NULL){
        printf("%d", x->key);
        preorder_tree_walk(x->left);
        preorder_tree_walk(x->right);
    }
}

void postorder_tree_walk(node_t *x){
    if(x != NULL){
        postorder_tree_walk(x->left);
        postorder_tree_walk(x->right);
        printf("%d", x->key);
    }
}

node_t *tree_search(node_t *x, int k){
    while(x != NULL && x->key != k){
        if(x->key > k)
            x = x->left;
        else
            x = x->right;
    }

    return x;
}

node_t *tree_maximum(node_t *x){
    while(x != NULL)
        x = x->right;

    return x;
}

node_t *tree_minimum(node_t *x){
    while(x != NULL)
        x = x->left;

    return x;
}

node_t *tree_successor(node_t *x){
    node_t *y;
    
    if(x->right != NULL)
        return tree_minimum(x->right);

    y = x->p;

    while(y != NULL && x == y->right){
        x = y;
        y = x->p;
    }

    return y;
}

void tree_insert(tree_t *t, node_t *z){
    node_t *x = t->root;
    
    if(x = NULL)
        t->root = z;

    while(x != NULL){
        if(x->key < z->key)
            x = x->right;
        else
            x = x->left;
    }

    z->p = x;

    if(x->key < z->key)
        x->right = z;
    else
        x->left = z;
}

void transplant(tree_t *t, node_t *u, node_t *v){
    if(u->p == NULL)
        t->root = v;
    else if(u = u->p->left)
        u->p->left = v;
    else
        u->p->right = v;
    
    if(v != NULL)
        v->p = u->p;
}

node_t *tree_delete(tree_t *t, node_t *z){
    node_t *y;

    if(z->left == NULL)
        transplant(t,z,z->right);
    else if(z->right == NULL)
        transplant(t,z,z->left);
    else{
        y = tree_minimum(z->right);
        if(y != z->right){
            transplant(t,y,y->right);
            y->right = z->right;
            y->right->p = y;
        }    
        transplant(t,z,y);
        y->left = z->left;
        y->left->p = y;
    }
}