#include <stdio.h>
#include <stdlib.h>

#define PRETO 2
#define VERMELHO 1
#define DDIR 1
#define DESQ -1

typedef struct _node{
    int reg;
    struct _node * esq;
    struct _node * dir;
    int h;
    struct _node * pai;
    int cor;
}tnode;

typedef struct _arv{
    tnode * raiz;
    tnode * nil;
}tarv;

void RD(tnode** pnode){
    tnode *x,*y,*b;
    printf("RD %d\n",(*pnode)->reg);
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

void RE(tnode** pnode){
    tnode *x,*y,*b;
    y = *pnode;
    x = y->dir;
    b = x->esq;
    printf("RE %d\n",(*pnode)->reg);
    
    y->dir = b;
    x->esq = y; 
    *pnode = x;

    b->pai = y;

    x->pai = y->pai;
    y->pai = x;

}

void rb_constroi(tarv ** parv){
    *parv = (tarv *)(malloc(sizeof(tarv)));
    
    (*parv)->nil = (tnode *)(malloc(sizeof(tnode)));
    (*parv)->raiz = (*parv)->nil;
}

int obtem_cor(tarv * parv, tnode * node){
    int ret = PRETO;
    if (node == parv->nil || node == NULL){
        ret = PRETO;
    }else{
        ret = node->cor;
    }
    return ret;
}

void _fix_up(tarv * parv, tnode * filho){
    tnode * pai;
    tnode * avo;
    tnode * tio;
    tnode ** pavo;
    int seta_pai, seta_filho;
    pai = filho->pai;
    while(obtem_cor(parv,pai) == VERMELHO){
        avo = pai->pai;
        if (pai->esq == filho){
            seta_filho = DESQ;
        }else{
            seta_filho = DDIR;
        }
        if (avo->esq == pai){
            seta_pai = DESQ;
        }else{
            seta_pai = DDIR;
        }
        if (seta_pai == DESQ){
            tio = avo->dir;
        }else{
            tio = avo->esq;
        }
        
        if (obtem_cor(parv,tio)==VERMELHO){
            tio->cor = PRETO;
            pai->cor = PRETO;
            avo->cor = VERMELHO;
            filho = avo;
            pai = filho->pai;
        }else{
            if (seta_pai * seta_filho < 0){ 
                if (seta_filho == DESQ){
                    RD(&(avo->dir));
                }else{
                    RE(&(avo->esq));
                }
            }
            if (parv->raiz == avo){ 
                pavo = &(parv->raiz);
            }else{
                if (avo->pai->esq == avo){
                    pavo = &(avo->pai->esq);
                }else{
                    pavo = &(avo->pai->dir);
                }
            }

            if (seta_pai == DESQ){  
                RD(pavo);
            }else{
                RE(pavo);
            }
            avo = *pavo;
            avo->cor = PRETO;
            avo->esq->cor = VERMELHO;
            avo->dir->cor = VERMELHO;
            pai = avo; 
        }
    }
}

int rb_insere(tarv * parv, int reg){
    tnode * filho;
    tnode * pai;
    int ret=0;
    filho = parv->raiz;
    pai = parv->raiz;
    
    while(filho != parv->nil){
        pai = filho;
        if (filho->reg < reg){
            filho = filho->dir;
        }else{
            filho = filho->esq;
        }
    }
    filho = (tnode *)malloc(sizeof(tnode));
    if (filho == parv->nil){
        ret = 0;
    }else{
        filho->reg = reg;
        filho->esq = parv->nil;
        filho->dir = parv->nil;
        filho->cor = VERMELHO;
        filho->pai = pai;
        if (parv->raiz == parv->nil){
            parv->raiz = filho;
        }else{
            if (pai->reg < reg){
                pai->dir  = filho;
            }else{
                pai->esq  = filho;
            }
            _fix_up(parv,filho);
            ret = 1;
        }
    }
    parv->raiz->cor = PRETO;
    return ret;
}

void _destroi(tarv * parv,tnode * pnode){
    if (pnode != parv->nil){
        _destroi(parv,pnode->esq);
        _destroi(parv,pnode->dir);
        free(pnode);
    }
}
void rb_destroi(tarv * arv){
    _destroi(arv,arv->raiz);
    free(arv->raiz);
}

void imprime(tnode * pnode,int d){
    int i;
    if (pnode != NULL){
        imprime(pnode->dir,d+1);
        i = d;
        while(i--) printf("      ");
        printf("(%d %c)\n",pnode->reg,(pnode->cor==PRETO)?'p':'v');
        imprime(pnode->esq,d+1);
    }
}

void in_ordem(tarv * parv,tnode *pnode){
    if (pnode!=parv->nil){
        in_ordem(parv,pnode->esq);
        printf("(%d,0,%c) ",pnode->reg,(pnode->cor==PRETO)?'p':'v');
        in_ordem(parv,pnode->dir);
    }
}

int main(void){
    int n,i,v;
    tarv * arv;
    rb_constroi(&arv);
    scanf("%d ",&n);
    for(i = 0; i < n; i++) {
        scanf("%d ",&v);
        rb_insere(arv,v);
        //imprime(arv->raiz,0);
        in_ordem(arv,arv->raiz);
        printf("\n");
    }

    return 0;
}

