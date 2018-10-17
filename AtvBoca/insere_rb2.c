#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 2

#define DESQ -1
#define DDIR 1

typedef struct _node {
    int key;
    int color;
    struct _node* left;
    struct _node* right;
    struct _node* p;
}tnode;

typedef struct _arv {
    tnode* root;
    tnode* nil;
}tarv;

tnode* build_node(tarv* parv, int n) {
    tnode* ret;
    ret = (tnode*)malloc(sizeof(tnode));
    ret->key = n;
    ret->color = RED;
    ret->right = parv->nil;
    ret->left = parv->nil;
    ret->p = parv->nil;
    return ret;
}

tnode* build_nil() {
    tnode* aux;
    aux = (tnode*)malloc(sizeof(tnode));
    aux->key = 0;
    aux->color = 0;
    aux->right = NULL;
    aux->left = NULL;
    aux->p = NULL;
    return aux;
}

tarv* build_arv() {
    tarv* aux;
    aux = (tarv*)malloc(sizeof(tarv));
    aux->root = NULL;
    aux->nil = build_nil();
    return aux;
}

void rotate_left(tarv* T, tnode* x) {
    tnode* y;
    y = x->right;
    x->right = y->left;
    printf("RE %d\n", x->key);
    if(y->left != T->nil)
        y->left->p = x;
    y->p = x->p;
    if(x->p == T->nil)
        T->root = y;
    else if(x == x->p->left)
        x->p->left = y;
    else   
        x->p->right = y;
    y->left = x;
    x->p = y;
}

void rotate_right(tarv* T, tnode* y) {
    tnode* x;
    x = y->left;
    y->left = x->right;
    printf("RD %d\n", y->key);
    if(x->right != T->nil)
        x->right->p = y;
    x->p = y->p;
    if(y->p == T->nil)
        T->root = x;
    else if(y == y->p->right)
        y->p->right = x;
    else 
        y->p->left = x;
    x->right = y;
    y->p = x;
}

int cor(tarv* arv, tnode* pnode) {
    int ret;
    if(pnode == arv->nil)
        ret = BLACK;
    else    
        ret = RED;
    return ret;
}

void new_fix_up(tarv* arv, tnode* z) {
    tnode* temp;
    while(z->p->color == RED) {
        if(z->p->key == z->p->p->key) {
            temp = z->p->p->right;
            if(temp->color == RED) {
                z->p->color = BLACK;
                temp->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }else if(z->key == z->p->right->key) {
                z = z->p;
                rotate_left(arv, z);
            }
            z->p->color = BLACK;
            z->p->p->color = RED;
            rotate_right(arv, z->p->p);
        }else {
            temp = z->p->p->left;
            if(temp->color == RED) {
                z->p->color = BLACK;
                z->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }else if(z->key == z->p->left->key) {
                z = z->p;
                rotate_right(arv, z);
            }
            z->p->color = BLACK;
            z->p->p->color = BLACK;
            rotate_left(arv, z->p->p);
        }
    }
    arv->root->color = BLACK;
}


void fix_up(tarv* arv, tnode* filho) {
    tnode* pai;
    tnode* avo;
    tnode* tio;
    int seta_pai, seta_filho;
    pai = filho->p;
    avo = pai->p;
    seta_filho = (pai->left == filho)?DESQ:DDIR;
    seta_pai = (avo->left == pai)?DESQ:DDIR;
    tio = (seta_pai == DESQ)?avo->right:avo->left;
    while(cor(arv, pai) == RED) {
        //caso 1
        if(cor(arv,tio) == RED) {
            pai->color = BLACK;
            tio->color = BLACK;
            avo->color = RED;
            filho = avo;
            pai = filho->p;
            avo = pai->p;
            tio = (seta_pai==DESQ)?avo->right:avo->left;
        }else {
            //caso 2
            if((seta_pai * seta_filho) < 0) {
                if(seta_filho == DESQ)
                    rotate_right(arv, pai);
                else
                    rotate_left(arv, pai);
                //caso 3
                if(seta_pai == DESQ) 
                    rotate_right(arv, avo);
                else
                    rotate_left(arv, avo);
            }
            pai = filho->p;
            avo = pai->p;
            tio = (seta_pai == DESQ)?avo->right:avo->left;
        }
    }
}

void insere_rb(tarv* arv,int n) {
    tnode* aux;
    aux = build_node(arv, n);
    if(arv->root == NULL) {
        arv->root = aux;
    }else{
        tnode* f;
        tnode* p;
        f = arv->root;
        p = arv->root;
        while(f != arv->nil) {
            p = f;
            if(n < p->key)
                f = p->left;
            else   
                f = p->right;
        }
        f = aux;
        f->p = p;
        if(n < p->key)
            p->left = f;
        else    
            p->right = f;

       
        //fix_up(arv, f);
    } 
    new_fix_up(arv, aux);
}

void desenha(tarv* parv,tnode* pnode, int n) {
    int i;

    if(pnode != parv->nil) {
        desenha(parv, pnode->right, n + 1);
        for(i = 0; i < n; i++) {
            printf("      ");
        }
        if(pnode->color == RED) 
            printf("[%d,V]\n", pnode->key);
        else    
            printf("[%d,P]\n", pnode->key);
        desenha(parv, pnode->left, n + 1);
    }
}

int max(int a, int b) {
    return (a > b)?a:b;
}


int altura(tarv* arv, tnode* pnode)  {
    int ret = 0;

    if(pnode != NULL) {
        if(pnode == arv->nil)
            ret = 1;
        else {
            int altura_esq = altura(arv, pnode->left);
            int altura_dir = altura(arv, pnode->right);
            ret = max(altura_esq, altura_dir) + 1;
        }
    }
    return ret;
}

void in_order(tarv* arv, tnode* pnode) {
    if(pnode != arv->nil) {
        in_order(arv, pnode->left);
        if(pnode->color == RED)
            printf("(%d,0,v) ", pnode->key);
        else
            printf("(%d,0,p) ", pnode->key);
        in_order(arv, pnode->right);
    }
}

int main() {

    tarv* arv;
    arv = NULL;
    arv = build_arv();

    int x, n, i;
    scanf("%d", &x);
    for(i = 0; i < x; i++) {
        scanf("%d", &n);
        insere_rb(arv, n);
        //in_order(arv, arv->root);
        //desenha(arv, arv->root, 0);
        printf("\n");
    }
    /*
    desenha(arv, arv->root, 0);
    printf("\n");
    rotate_right(arv, arv->root);
    desenha(arv, arv->root, 0);
    printf("\n");
    */
    return 0;
}