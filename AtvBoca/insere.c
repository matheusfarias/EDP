#include<stdio.h>
#include<stdlib.h>

typedef struct _node{
    int reg;
    int h;
    struct _node * esq;
    struct _node * dir;
}tnode;


int altura(tnode* pnode) {
    int ret;
    if(pnode == NULL)
        ret = -1;
    else
        ret = pnode->h;
    return ret;
}


int max(int a, int b) {
    return (a > b)?a:b;
}

void RE(tnode ** pnode){
    tnode * x;
    tnode * y;
    tnode * a;
    tnode * b;
    x = *pnode;
    y = x->dir;
    a = x->esq;
    b = y->esq;
    printf("RE %d\n", x->reg);

    x->esq = a;
    x->dir = b;
    y->esq = x;
    *pnode = y;

    x->h = max(altura(x->esq), altura(x->dir)) + 1;
    y->h = max(altura(y->esq), altura(y->dir)) + 1;

}

void RD(tnode ** pnode){
    tnode * x;
    tnode * y;
    tnode * a;
    tnode * b;
    y = *pnode;
    x = y->esq;
    a = x->esq;
    b = x->dir;
    printf("RD %d\n", y->reg);

    x->esq = a;
    x->dir = y;
    y->esq = b;
    *pnode = x;

    y->h = max(altura(y->esq), altura(y->dir)) + 1;
    x->h = max(altura(x->esq), altura(x->dir)) + 1;

}



void rebalancear(tnode** pnode) {
    int fb;                             //fator balanceamento
    int fbf;                            // fator de balanceamento filho
    

    tnode* filho;
    tnode* pai;
    pai = *pnode;

    fb = altura(pai->esq) - altura(pai->dir);

    if(fb == 2) {
        filho = pai->esq;
        fbf = altura(filho->esq) - altura(filho->dir);
        if(fbf == -1) {
            RE(&(pai->esq));
        }
        RD(pnode);

    }else if(fb == -2) {
        filho = pai->dir;
        fbf = altura(filho->esq) - altura(filho->dir);
        if(fbf == 1) {
            RD(&(pai->dir));
        }
        RE(pnode);
    }

}

void insere(tnode ** parv,int num){
    if (*parv == NULL){
        *parv = (tnode *) malloc(sizeof(tnode));
        (*parv)->reg = num;
        (*parv)->esq = NULL;
        (*parv)->dir = NULL;
        (*parv)->h = 0;
    }else{
        if (num > (*parv)->reg){
            insere(&(*parv)->dir,num);
        }else{
            insere(&(*parv)->esq,num);
        }
        (*parv)->h = max(altura((*parv)->esq), altura((*parv)->dir)) + 1;
        rebalancear(parv);
    }
}

void imprime_arv(tnode * pnode,int p){
    int i;
    if (pnode != NULL){
        imprime_arv(pnode->esq,p+1);
        for (i=0;i<p;i++)
            printf("   ");
        printf("%d\n",pnode->reg);
        imprime_arv(pnode->dir,p+1);
    }
}

void destroi_arv(tnode * pnode){
    if (pnode != NULL){
        destroi_arv(pnode->esq);
        destroi_arv(pnode->dir);
        free(pnode);
    }
}

void pre_ordem(tnode *pnode){
    if (pnode != NULL){
        printf("%d ",pnode->reg);
        pre_ordem(pnode->esq);
        pre_ordem(pnode->dir);
    }
}

tnode ** busca_pont(tnode ** pnode, int reg){
    tnode ** ret;
    if (*pnode == NULL){
        ret = NULL;
    }else if ((*pnode)->reg == reg){
        ret = pnode;
    }else{
        if (reg > (*pnode)->reg){
            ret = busca_pont(&(*pnode)->dir,reg);
        }else{
            ret = busca_pont(&(*pnode)->esq,reg);
        }

    }
    return ret;
}

/*

void preorder(tnode* pnode) {
    if(pnode != NULL)  {
        printf("%d ",pnode->reg.id);
        preorder(pnode->esq);
        preorder(pnode->dir);
    }
}


*/
void par_preorder(tnode* pnode) {
    if(pnode != NULL) {
        par_preorder(pnode->esq);
        printf("(%d,%d) ", pnode->reg, pnode->h);
        par_preorder(pnode->dir);
    }
}





int main(void){
    int num,n,test,i,j;
    char rot;

    tnode * arv;
    tnode ** parv;
    arv = NULL;

    scanf("%d ", &test);
    for (i = 0; i < test; i++) {
        scanf("%d", &num);
        insere(&arv, num);
    }  
   par_preorder(arv);



    return 0;
}
