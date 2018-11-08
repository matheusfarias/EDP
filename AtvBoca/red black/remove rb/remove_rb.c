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

tnode* busca(tarv* arv, int num) {
    tnode* aux;
    aux = arv->raiz;
    while(aux != arv->nil && aux->key != num)
        aux = (aux->key < num)?aux->dir:aux->esq;
    return aux;
}

tnode** get_ppai(tarv* arv, tnode* pnode) {
    tnode** ret = NULL;
    if(pnode == arv->raiz)
        ret = &(arv->raiz);
    else {
        if(pnode->pai->esq == pnode)
            ret = &(pnode->pai->esq);
        else
            ret = &(pnode->pai->dir);
    }
    return ret;
}

void transplant(tarv* arv, tnode* filho, tnode* neto) {
    tnode* pai;
    pai = filho->pai;
    if(pai == arv->nil)
        arv->raiz = neto;
    else {
        if(pai->esq == filho)
            pai->esq = neto;
        else
            pai->dir = neto;
    }
    neto->pai = filho->pai;
}

tnode* _sucessor(tarv* arv, tnode* pnode) {
    tnode* aux;
    aux = pnode->dir;
    while(aux->esq != arv->nil)
        aux = aux->esq;
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

void remove_fix_up(tarv *arv, tnode *x) {
    int seta_irmao, seta_sobrinho_vermelho;
    tnode* irmao;
    tnode* s_esq;
    tnode* s_dir;
    tnode* pai;
    
    while(fcolor(arv,x) == PRETO && arv->raiz != x) {
        pai = x->pai;
        irmao = (pai->esq == x)?pai->dir:pai->esq;
        seta_irmao = (pai->esq == irmao)?DESQ:DDIR;

        if (fcolor(arv,irmao)==VERMELHO) { 
            if(pai->key > 200) {
                printf("C1 (P,0,%c)\n",_cor_char(arv,pai));
            }else {
                printf("C1 (P,%d,%c)\n",pai->key,_cor_char(arv,pai));
            }
            irmao->cor = PRETO;
            pai->cor = VERMELHO;
            if (seta_irmao == DDIR) {
                re(get_ppai(arv,pai));
                irmao = x->pai->dir;
            }else {
                rd(get_ppai(arv,pai));
                irmao = x->pai->esq;
            }
        }
        s_esq = irmao->esq;
        s_dir = irmao->dir;
        seta_sobrinho_vermelho = (fcolor(arv,s_esq)==VERMELHO)?DESQ:DDIR;

        if ((fcolor(arv,s_esq)==PRETO)&&(fcolor(arv,s_dir)==PRETO)) { 
            if(x->key > 200) {
                printf("C2 (atual,0,%c) (pai,%d,%c) (irmao,%d,%c)\n",_cor_char(arv,x),pai->key,_cor_char(arv,pai),irmao->key,_cor_char(arv,irmao));
            }else {
                printf("C2 (atual,%d,%c) (pai,%d,%c) (irmao,%d,%c)\n",x->key,_cor_char(arv,x),pai->key,_cor_char(arv,pai),irmao->key,_cor_char(arv,irmao));
            }
        
            irmao->cor = VERMELHO;
            x = pai;
        }else {
            if (seta_sobrinho_vermelho * seta_irmao < 0) {
                if(x->key > 200)
                    printf("C3 (atual,0,%c) (pai,%d,%c) (irmao,%d,%c)\n",_cor_char(arv,x),pai->key,_cor_char(arv,pai),irmao->key,_cor_char(arv,irmao));
                else
                    printf("C3 (atual,%d,%c) (pai,%d,%c) (irmao,%d,%c)\n",x->key,_cor_char(arv,x),pai->key,_cor_char(arv,pai),irmao->key,_cor_char(arv,irmao));
                
                if (seta_sobrinho_vermelho == DESQ) {
                    s_esq->cor = PRETO;
                    irmao->cor = VERMELHO;
                    rd(get_ppai(arv,irmao));
                }else {
                    s_dir->cor = PRETO;
                    irmao->cor = VERMELHO;
                    re(get_ppai(arv,irmao));
                }
            }
            irmao = (pai->esq == x)?pai->dir:pai->esq;
            s_esq = irmao->esq;
            s_dir = irmao->dir;

            if(x->key > 200) 
                printf("C4 (atual,0,%c) (pai,%d,%c) (irmao,%d,%c)\n",_cor_char(arv,x),pai->key,_cor_char(arv,pai),irmao->key,_cor_char(arv,irmao));
            else
                printf("C4 (atual,%d,%c) (pai,%d,%c) (irmao,%d,%c)\n",x->key,_cor_char(arv,x),pai->key,_cor_char(arv,pai),irmao->key,_cor_char(arv,irmao));

            if (seta_irmao == DDIR) {
                irmao->cor = pai->cor;
                pai->cor = PRETO;
                s_dir->cor = PRETO;
                re(get_ppai(arv,pai));
            }else {
                irmao->cor = pai->cor;
                pai->cor = PRETO;
                s_esq->cor = PRETO;
                rd(get_ppai(arv,pai));
            }

            break;
        }
    }
    x->cor = PRETO;
}

void remove_rb(tarv* arv, int num) {
    tnode* pnode;
    tnode* x;
    tnode* sucessor;
    int cor_removido;
    pnode = busca(arv, num);
    if(pnode != arv->nil) {
        if(pnode->esq == arv->nil) {
            cor_removido = pnode->cor;
            x = pnode->dir;
            transplant(arv, pnode, x);
        }else if(pnode->dir == arv->nil) {
            cor_removido = pnode->cor;
            x = pnode->esq;
            transplant(arv, pnode, x);
        }else {
            sucessor = _sucessor(arv, pnode);
            x = sucessor->dir;
            cor_removido = sucessor->cor;
            if(sucessor->pai == pnode)
                x->pai = sucessor;
            else {
                transplant(arv, sucessor, x);
                sucessor->dir = pnode->dir;
                sucessor->dir->pai = sucessor;
            }
            transplant(arv, pnode, sucessor);
            sucessor->esq = pnode->esq;
            sucessor->esq->pai = sucessor;
            sucessor->cor = pnode->cor; 
        }
        if(cor_removido == PRETO)
            remove_fix_up(arv, x);
        free(pnode);
    }
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

void imprime(tarv* arv, tnode* pnode, int d) {
    int i;
    if (pnode != arv->nil){
        imprime(arv, pnode->dir,d+1);
        i = d;
        while(i--) printf("      ");
        printf("(%d %c)\n",pnode->key,(pnode->cor==PRETO)?'p':'v');
        imprime(arv, pnode->esq,d+1);
    }
}


int main() {

    int num, qtd, i;
    tarv* arv;
    build_arv(&arv);

    FILE* point;
    point = fopen("insert.txt", "r");
   
    scanf("%d", &qtd);
    for(i = 0; i < qtd; i++) {
        scanf("%d", &num);
        insere_rb(arv, num);
       imprime(arv, arv->raiz, 0);
        printf("\n");
    }
    for(i = 0; i < qtd; i++) {
        printf("remove %d\n", arv->raiz->key);
        remove_rb(arv, arv->raiz->key);
        imprime(arv, arv->raiz, 0);
        printf("\n");
    }
    
    return 0;
}