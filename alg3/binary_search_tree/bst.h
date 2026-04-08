typedef struct{
    node_t *root;
    int tamanho;
} tree_t;

typedef struct{
    int key;
    node_t *p;
    node_t *left;
    node_t *right;
} node_t;

tree_t *tree_create();

node_t *node_create(int key);

void inorder_tree_walk(node_t *x);

void preorder_tree_walk(node_t *x);

void postorder_tree_walk(node_t *x);

node_t *tree_search(node_t *x, int k);

node_t *tree_maximum(node_t *x);

node_t *tree_minimum(node_t *x);

node_t *tree_successor(node_t *x);

void tree_insert(tree_t *t, node_t *z);

void transplant(tree_t *t, node_t *u, node_t *v);

node_t *tree_delete(tree_t *t, node_t *z);