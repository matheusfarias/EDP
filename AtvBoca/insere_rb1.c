#include <stdio.h>
#include <stdlib.h>
#define TAM 17
#define RED 1
#define BLACK 2

typedef struct _node{
    int key;
    int color;
    struct _node* left;
    struct _node* right;
    struct _node* p;
}tnode;

typedef struct _arv{
    tnode* nil;
    tnode* root;
}tarv;


tarv* build_arv() {
    tarv* ret;
    ret = (tarv*)malloc(sizeof(tarv));
    ret->nil = NULL;
    ret->root = NULL;
    return ret;
}

tnode* build_node(int n) {
    tnode* ret;
    ret = (tnode*)malloc(sizeof(tnode));
    ret->key = n;
    ret->color = RED;
    ret->right = NULL;
    ret->left = NULL;
    ret->p = NULL;
    return ret;
}

void rotate_left(tarv** parv, tnode** pnode) {
    tnode* y;
    tnode* x;
    x = *pnode;
    y = x->right;
    x->right = y->left;
    printf("RE %d\n", x->key);
    if(y->left != (*parv)->nil)
        y->left->p = *pnode;
    y->p = x->p;
    if(x->p == (*parv)->nil)
        (*parv)->root = y;
    else if(x == x->p->left)
        x->p->left = y;
    else    
        x->p->left = y;
    y->left = x;
    x->p = y;
}

void rotate_right(tarv** parv, tnode** pnode) {
    tnode* y;
    tnode* x;
    y = *pnode;
    x = y->left;
    y->left = x->right;  
    printf("RD %d\n", y->key); 
    if (x->right != (*parv)->nil)
        x->right->p = y;
    x->p = y->p;  
    if (y->p == (*parv)->nil)
       (*parv)->root = x;
    else if (y == y->p->right)
       y->p->right = x;
    else
       y->p->left  = x;
    x->right  = y;         
    y->p = x;
}

void fix_up(tarv** parv, tnode* pnode) {
    tnode* aux;
    
   while(pnode->p->color == RED) {
        if(pnode->p->key == pnode->p->p->key) {
            aux = pnode->p->p->right;
            if(aux->color == RED) {
                pnode->p->color = BLACK;
                aux->color = BLACK;
                pnode->p->p->color = RED;
                pnode = pnode->p->p;
            }
            else if(pnode->key == pnode->p->right->key) {
                pnode = pnode->p;
                rotate_left(parv,&pnode);
            }
            pnode->p->color = BLACK;
            pnode->p->p->color = RED;
            rotate_right(parv,&pnode->p->p);
        }
        else {
            aux = pnode->p->p->left;
            if(aux->color == RED) {
                pnode->p->color = BLACK;
                pnode->color = BLACK;
                pnode->p->p->color = RED;
                pnode = pnode->p->p;
            }
            else if(pnode->key == pnode->p->left->key) {
                pnode = pnode->p;
                rotate_right(parv,&pnode);
            }
            pnode->p->color = BLACK;
            pnode->p->p->color = RED;
            rotate_left(parv, &pnode->p->p);
        }
    }
    (*parv)->root->color = BLACK;
}




void rb_insert(tarv** parv, int n) {
    tnode* z;
    tnode* y;
    tnode* x;

    z = build_node(n);
    y = (*parv)->nil;
    x = (*parv)->root;

    while(x != (*parv)->nil) {
        y = x;
        if(z->key < x->key)
            x = x->left;
        else   
            x = x->right;
    }

    z->p = y;
    if(y == (*parv)->nil)
        (*parv)->root = z;
    else if(z->key < y->key)
        y->left = z;
    else 
        y->right = z;

    z->left  = (*parv)->nil;
    z->right = (*parv)->nil;
    z->color = RED;

    fix_up(parv, z);
}


int max(int a, int b) {
    return (a > b)?a:b;
}

int get_altura(tarv* parv, tnode* pnode) {
    int aux;
    aux = 0;
    int ret;
    ret = 0;
    if(parv->root != NULL) {
        if(parv->root == parv->nil)
            ret = 1;
        else {
            int altura_esq = get_altura(parv, parv->root->left);
            int altura_dir = get_altura(parv, parv->root->right);
            aux = max(altura_esq, altura_dir) + 1;
        }
    }

    return ret;
}

void in_order(tarv* parv, tnode* pnode) {
    if(pnode != NULL) {
        in_order(parv, pnode->left);
        int altura = get_altura(parv, pnode);
        if(pnode->color == BLACK) {
            printf("(%d,%d,p) ", pnode->key, altura);
        }else{
            printf("(%d,%d,v) ", pnode->key, altura);
        }
        in_order(parv, pnode->right);
    }
}

int main() {


    tarv* raiz;
    raiz = NULL;
    raiz = build_arv();
    int n, x;
    int i;
    scanf("%d", &x);
    for(i = 0; i < x; i++) {
        scanf("%d", &n);
        rb_insert(&raiz,n);
        //in_order(raiz, raiz->root);
        printf("\n");
    }

    return 0;


}