#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 2
#define DDIR 1
#define DESQ -1

typedef struct _node {
    int key;
    int color;
    int h;
    struct _node* esq;
    struct _node* dir;
    struct _node* p;
}tnode;

typedef struct _arv {
    tnode* root;
    tnode* nil;
}tarv;


void RD(tnode** pnode) {
    tnode* x;
    tnode* y;
    tnode* b;
    printf("RD %d\n",(*pnode)->key);
    x = *pnode;
    y = x->esq;
    b = y->dir;

    x->esq = b;
    y->dir = x;
    *pnode

}