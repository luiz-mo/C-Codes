#define MAX(a,b) (((a)> (b)) ? (a) : (b))
#define HEIGHT(a) ((a) ? (a->height) : (-1))
#define FB(a) ((ALT(a->right)) - (ALT(a->left)))

typedef struct{
    avl_node *root;
} avl_t;

typedef struct{
    avl_node *p;
    avl_node *left;
    avl_node *right;
    int key;
    int height;
} avl_node;   

avl_t *avl_create();

avl_node *node_create(int key);

void inorder_avl_walk(avl_node *x);

void preorder_avl_walk(avl_node *x);

void postorder_avl_walk(avl_node *x);

avl_node *avl_search(avl_node *x, int k);

avl_node *avl_maximum(avl_node *x);

avl_node *avl_minimum(avl_node *x);

avl_node *avl_successor(avl_node *x);

void avl_insert(avl_t *t, avl_node *z);

void transplant(avl_t *t, avl_node *u, avl_node *v);

avl_node *avl_delete(avl_t *t, avl_node *z);