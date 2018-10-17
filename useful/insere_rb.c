#include <stdio.h>
#include <stdlib.h>
#define RED 3
#define BLACK 2

typedef struct _reg {
    int key;
}treg;

typedef struct _node {
    treg reg;
    int cor;
    struct _node* left;
    struct _node* right;
    struct _node* p;
}tnode;

typedef struct _arv{
    tnode* nil;
    tnode* root;
}tarv;

tnode* build_node (int n) {
    tnode* aux;
    aux = (tnode*)malloc(sizeof(tnode));
    aux->reg.key = n;
    aux->cor = RED;
    aux->right = NULL;
    aux->left = NULL;
    aux->p = NULL;
    return aux;
}

tarv* build_arv() {
    tarv* raiz;
    raiz = (tarv*)malloc(sizeof(tarv));
    raiz->nil = NULL;
    raiz->root = NULL;
} 

void left_rotate(tnode** pnode) {
    tnode* y;
    tnode* x;
    x = *pnode;
    y =  x->right;
    x->right = y->left;
    if(y->left != NULL) {
        y->left->p = x;
    }
    y->p = x->p;
    if(x->p != NULL && x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    y->left = x;
    x->p = y;
}

void right_rotate(tnode** pnode) {

}

int get_cor(tnode* pnode) {
    int ret;
    if(pnode == NULL)
        ret = BLACK;
    else
        ret = pnode->cor;
    return ret;
}

void rb_fixup(tnode** pnode, tnode* z) {
    int color_node = get_cor(z->p);
    while(color_node == RED) {
        if(z->p == z->p->p->left) {
            
        }
    }
}

rb_insert(tnode** pnode, int n) {
    tnode* x;
    tnode* y;
    tnode* z;
    z = build_node(n);
    y = NULL;
    x = *pnode;
    while(x != NULL) {
        y = x;
        if(n < x->reg.key)
            x = x->left;
        else
            x = x->right;
    }
    z->p = y;
    if(y = NULL)
        *pnode = z;
    else if(z->reg.key < y->reg.key)
        y->left = z;
    else
        y->right = z;
    rb_fixup(&pnode, z);

}



int main() {





    return 0;
}