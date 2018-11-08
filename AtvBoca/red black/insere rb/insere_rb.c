#include <stdio.h>
#include <stdlib.h>

#define VERMELHO 1
#define PRETO 2
#define DDIR 1
#define DESQ -1

typedef struct node{
    int key;
    int cor;
    struct node* esq;
    struct node* dir;
    struct node* pai;
}tnode;

typedef struct arv{
    tnode* raiz;
    tnode* nil;
}tarv;

void rd(tnode** pnode) {
    tnode* x;
    tnode* y;
    tnode* b;
    printf("RD %d\n",(*pnode)->key);
    x = *pnode;
    y = x->esq;
    b = y->dir;

    x->esq = b;
    y->dir = x;
    *pnode = y;

    b->pai = x;
    y->pai = x->pai;
    x->pai = y;
}

void re(tnode** pnode) {
    tnode* x;
    tnode* y;
    tnode* b;
    printf("RE %d\n",(*pnode)->key);
    y = *pnode;
    x = y->dir;
    b = x->esq;

    y->dir = b;
    x->esq = y;
    *pnode = x;

    b->pai = y;
    x->pai = y->pai;
    y->pai = x;
}

void build_arv(tarv** arv) {
    *arv = (tarv*)malloc(sizeof(tarv));
    (*arv)->nil = (tnode*)malloc(sizeof(tnode));
    (*arv)->raiz = (*arv)->nil;
}

int fcolor(tarv* arv, tnode* pnode) {
    int ret = 0;
    if(pnode == NULL || pnode == arv->nil) 
        ret = PRETO;
    else
        ret = pnode->cor;
    return ret;
}

void insere_fix_up(tarv* arv, tnode* filho) {
    tnode* pai;
    tnode* tio;
    tnode* avo;
    tnode** p_avo;
    int seta_pai, seta_filho;

    pai = filho->pai;
    while(fcolor(arv, pai) == VERMELHO) {
        avo = pai->pai;
        if(pai->esq == filho)
            seta_filho = DESQ;
        else    
            seta_filho = DDIR;
        if(avo->esq == pai)
            seta_pai = DESQ;
        else    
            seta_pai = DDIR;
        if(seta_pai == DESQ)
            tio = avo->dir;
        else
            tio = avo->esq;


        if(fcolor(arv, tio) == VERMELHO) {
            tio->cor = PRETO;
            pai->cor = PRETO;
            avo->cor = VERMELHO;
            filho = avo;
            pai = filho->pai;
        }else {
            if (seta_pai * seta_filho < 0) {
                if(seta_filho == DESQ)
                    rd(&(avo->dir));
                else    
                    re(&(avo->esq));
            }
            if(arv->raiz == avo) 
                p_avo = &(arv->raiz);
            else {
                if(avo->pai->esq == avo)
                    p_avo = &(avo->pai->esq);
                else    
                    p_avo = &(avo->pai->dir);
            }
            if(seta_pai == DESQ)
                rd(p_avo);
            else    
                re(p_avo);
            avo = *p_avo;
            avo->cor = PRETO;
            avo->esq->cor = VERMELHO;
            avo->dir->cor = VERMELHO;
            pai = avo;
        }
    } 
}

void insere_rb(tarv* arv, int num) {
    tnode* filho;
    tnode* pai;

    filho = arv->raiz;
    pai = arv->raiz;

    while(filho != arv->nil) {
        pai = filho;
        if (filho->key < num)
            filho = filho->dir;
        else    
            filho = filho->esq;
    }

    filho = (tnode*)malloc(sizeof(tnode));
    filho->key = num;
    filho->cor = VERMELHO;
    filho->esq = arv->nil;
    filho->dir = arv->nil;
    filho->pai = pai;

    if(arv->raiz == arv->nil) 
        arv->raiz = filho;
    else {
        if(pai->key < num)
            pai->dir = filho;
        else
            pai->esq = filho;
        insere_fix_up(arv, filho);
    }
    arv->raiz->cor = PRETO;
}

void in_order(tarv* arv, tnode* pnode) {
    if(pnode != arv->nil) {
        in_order(arv, pnode->esq);
        printf("(%d,0,%c) ", pnode->key, (pnode->cor == PRETO)?'p':'v');
        in_order(arv, pnode->dir);
    }
}

int main() {

    int num, qtd, i;
    tarv* arv;
    build_arv(&arv);

    scanf("%d", &qtd);
    for(i = 0; i < qtd; i++) {
        scanf("%d", &num);
        insere_rb(arv, num);
        in_order(arv, arv->raiz);
        printf("\n");
    }

    return 0;
}