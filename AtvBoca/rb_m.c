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

void build_arv(tarv** parv) {
    *parv = (tarv*)malloc(sizeof(tarv));
    (*parv)->nil = (tnode*)malloc(sizeof(tnode));
    (*parv)->root = (*parv)->nil;
}

void RE(tnode ** pnode){
    tnode *x,*y,*b;
    y = *pnode;
    x = y->right;
    b = x->left;
    printf("RE %d\n",(*pnode)->key);
    
    y->right = b;
    x->left = y; 
    *pnode = x;

    b->p = y;

    x->p = y->p;
    y->p = x;

}

void RD(tnode ** pnode){
    tnode* x;
    tnode* y;
    tnode* b;
    printf("RD %d\n",(*pnode)->key);
    x = *pnode;
    y = x->left;
    b = y->right;

    x->left = b;
    y->right = x;
    *pnode = y;


    b->p = x;

    y->p = x->p;
    x->p = y;

}

int cor(tarv* arv, tnode* pnode) {
    int ret = BLACK;
    if(pnode == arv->nil || pnode == NULL)
        ret = BLACK;
    else    
        ret = RED;
    return ret;
}

void fix_up(tarv * parv, tnode * filho){
    tnode * pai;
    tnode * avo;
    tnode * tio;
    tnode ** pavo;
    int seta_pai, seta_filho;
    pai = filho->p;
    int i = 0;
    while(cor(parv,pai) == RED){
        avo = pai->p;
        if (pai->left == filho){
            seta_filho = DESQ;
        }else{
            seta_filho = DDIR;
        }
        if (avo->left == pai){
            seta_pai = DESQ;
        }else{
            seta_pai = DDIR;
        }
        if (seta_pai == DESQ){
            tio = avo->right;
        }else{
            tio = avo->left;
        }
        
        i++;
        
        if (cor(parv,tio) == RED ){
            tio->color = BLACK;
            pai->color = BLACK;
            avo->color = RED;
            filho = avo;
            pai = filho->p;    
        }else{
            if (seta_pai * seta_filho < 0){ 
                if (seta_filho == DESQ){
                    RD(&(avo->right));
                }else{
                    RE(&(avo->left));
                }
            }
            
            if (parv->root == avo){ 
                pavo = &(parv->root);
            }else{
                if (avo->p->left == avo){
                    pavo = &(avo->p->left);
                }else{
                    pavo = &(avo->p->right);
                }
            }
            
            if (seta_pai == DESQ){ 
                RD(pavo);
            }else{
                RE(pavo);
            }
            
            avo = *pavo;
            avo->color = BLACK;
            avo->left->color = RED;
            avo->right->color = RED;
            pai = avo; 
            
        }
        
    }
    
}

void insere_rb(tarv* arv,int n) {
    tnode* aux;
    aux = build_node(arv, n);
    if(arv->root == arv->nil) {
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
    arv->root->color = BLACK;
}


int rb_insere(tarv * parv, int n){
    tnode * filho;
    tnode * pai;
    int ret=0;
    filho = parv->root;
    pai = parv->root;
    
    while(filho != parv->nil){
        pai = filho;
        if (filho->key < n){
            filho = filho->right;
        }else{
            filho = filho->left;
        }
    }
    filho = (tnode *)malloc(sizeof(tnode));
    if (filho == parv->nil){
        ret = 0;
    }else{
        filho->key = n;
        filho->left = parv->nil;
        filho->right = parv->nil;
        filho->color = RED;
        filho->p = pai;
        if (parv->root == parv->nil){
            parv->root = filho;
        }else{
            if (pai->key < n){
                pai->right = filho;
            }else{
                pai->right = filho;
            }
            fix_up(parv,filho);
            ret = 1;
        }
    }
    parv->root->color = BLACK;
    return ret;
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
    build_arv(&arv);

    int x, n, i;
    scanf("%d", &x);
    for(i = 0; i < x; i++) {
        scanf("%d ", &n);
        //insere_rb(arv, n);
        rb_insere(arv, n);
        in_order(arv, arv->root);
        
        printf("\n");
    }
    
    return 0;
}