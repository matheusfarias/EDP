#include <stdio.h>
#include <stdlib.h>

#define PRETO 1
#define VERMELHO 0
#define DDIR 1
#define DESQ -1

typedef int treg;

typedef struct _node{
    treg reg;
    struct _node * esq;
    struct _node * dir;
    int h;
    struct _node * pai;
    int cor;
}tnode;



typedef struct _arv{
    tnode * raiz;
    int (*compara)(const void *a, const void *b);
    tnode * nil;
}tarv;

tnode ** obtem_pp(tarv * parv,tnode * pnode){
    tnode ** ret = NULL;
    if (pnode == parv->raiz){
        ret = &parv->raiz;
    }else{
        if (pnode->pai->esq == pnode){
            ret = &pnode->pai->esq;
        }else{
            ret = &pnode->pai->dir;
        }
    }
    return ret;

}




void RD(tnode ** pnode){
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
void RE(tnode ** pnode){
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



void   rb_constroi(tarv ** parv){
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
        
        if (obtem_cor(parv,tio)==VERMELHO){/*caso 1*/
            tio->cor = PRETO;
            pai->cor = PRETO;
            avo->cor = VERMELHO;
            filho = avo;
            pai = filho->pai;
        }else{
            if (seta_pai * seta_filho < 0){ /* caso 2 cotovelo*/
                if (seta_filho == DESQ){
                    RD(&(avo->dir));
                }else{
                    RE(&(avo->esq));
                }
            }
            if (parv->raiz == avo){ /* encontra o pont de pont do avo*/
                pavo = &(parv->raiz);
            }else{
                if (avo->pai->esq == avo){
                    pavo = &(avo->pai->esq);
                }else{
                    pavo = &(avo->pai->dir);
                }
            }

            if (seta_pai == DESQ){  /* Caso 3  sem cotovelo*/
                RD(pavo);
            }else{
                RE(pavo);
            }
            avo = *pavo;
            avo->cor = PRETO;
            avo->esq->cor = VERMELHO;
            avo->dir->cor = VERMELHO;
            pai = avo; /*necessario pois o pai e vermelho, fazendo o algoritmo entrar novamente no laco*/
        }
    }
}



int rb_insere(tarv * parv, treg reg){
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

void imprime(tarv * arv, tnode * pnode,int d){
    int i;
    if (pnode != arv->nil){
        imprime(arv, pnode->dir,d+1);
        i = d;
        while(i--) printf("      ");
        printf("(%d %c)\n",pnode->reg,(pnode->cor==PRETO)?'p':'v');
        imprime(arv, pnode->esq,d+1);
    }
}


void in_ordem(tarv * parv,tnode *pnode){
    if (pnode!=parv->nil){
        in_ordem(parv,pnode->esq);
        printf("(%d,%c) ",pnode->reg,(pnode->cor==PRETO)?'p':'v');
        in_ordem(parv,pnode->dir);
    }
}


tnode * busca_node(tarv *arv,treg reg){
    tnode * aux;
    aux = arv->raiz;
    while(aux != arv->nil && aux->reg != reg){
        aux = (aux->reg < reg)?aux->dir:aux->esq;
    }
    return aux;
    
}

void _transplante(tarv *arv, tnode *filho, tnode *neto){
    tnode * pai;
    pai = filho->pai;
    if (pai == arv->nil){ /*trata caso onde filho eh raiz*/
        arv->raiz = neto;
    }else{ /*verificar qual lado fica o filho*/
        if (pai->esq == filho){
            pai->esq = neto;
        }else{
            pai->dir = neto;
        }
    }
    neto->pai = filho->pai;
}

tnode * _sucessor(tarv * arv,tnode * pnode){
    tnode * aux;
    aux = pnode->dir;
    while(aux->esq != arv->nil){
        aux = aux->esq;
    }
    return aux;
}

char _cor_char(tarv *arv, tnode * node){
    char ret = 'p';
    if (node == arv->nil || node == NULL){
        ret = 'p';
    }else{
        ret = (node->cor == PRETO)?'p':'v';
    }
    return ret;
}

void _remove_fix_up(tarv *arv, tnode *x){
    /* VC DEVE IMPLEMENTAR ESTA PARTE*/
}

int rb_remove(tarv *arv, treg reg){
    tnode * pnode;
    tnode * x;
    tnode * sucessor;
    int ret = 0;
    int cor_removido;
    pnode = busca_node(arv,reg);
    if (pnode != arv->nil){
        /* tem um filho  */
        if (pnode->esq == arv->nil){ /*esquerda ou direita vazia entao tem filho a direita*/
            cor_removido = pnode->cor;
            x = pnode->dir;
            _transplante(arv,pnode,x);
        }else if (pnode->dir == arv->nil){
            cor_removido = pnode->cor;
            x = pnode->esq;
            _transplante(arv,pnode,x);
        }else{ /* tem dois filhos: coloca o sucessor no lugar de pnode */
            sucessor = _sucessor(arv,pnode);
            x = sucessor->dir;
            cor_removido = sucessor->cor;
            if (sucessor->pai == pnode){
                x->pai = sucessor;
            }else{
                _transplante(arv,sucessor,x);
                sucessor->dir = pnode->dir;
                sucessor->dir->pai = sucessor;
            }
            _transplante(arv,pnode,sucessor);
            sucessor->esq = pnode->esq;
            sucessor->esq->pai = sucessor;
            sucessor->cor = pnode->cor;
        }
        if (cor_removido == PRETO)
            _remove_fix_up(arv,x);
        free(pnode);
        ret  = 1;
    }
    return ret;
}

int main(void){
    int n,i,v;
    tarv * arv;
    rb_constroi(&arv);
    #ifdef TESTE
    freopen("removerb.in","r",stdin);
    #endif
    scanf("%d ",&n);

    for(i=0;i<n;i++){
        scanf("%d ",&v);
        rb_insere(arv,v);
        imprime(arv,arv->raiz,0);
        /*in_ordem(arv,arv->raiz);*/
        printf("\n");
    }
    for(i=0;i<n;i++){
        printf("remove %d\n",arv->raiz->reg);
        rb_remove(arv,arv->raiz->reg);
        imprime(arv,arv->raiz,0);
        /*in_ordem(arv,arv->raiz);*/
        printf("\n");
    }


    return 0;
}

