#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
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

tnode** sucessor(tnode** pnode) {
	tnode *aux;
	tnode **paux;

	aux = (*pnode)->dir;
	paux = &(*pnode)->dir;
	while(aux->esq !=NULL) {
		paux = &(aux->esq);
		aux = aux->esq;
	}
	return paux;
}

void rebalancear(tnode** pnode) {
    int fb;
    int fbf;

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

void insere(tnode** parv,int num){
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

int remove_node(tnode** pnode, int n) {
    int ret = 0;
    if(*pnode == NULL)
        ret = 0;
    else if((*pnode)->reg < n) {
        ret = remove_node(&(*pnode)->dir, n);
    }else if((*pnode)->reg > n) {
        ret = remove_node(&(*pnode)-> esq, n);
    }else {
        ret = 1;
        tnode* aux;
      	tnode** paux;

       	if((*pnode)->esq == NULL && (*pnode)->dir == NULL) {
     		aux = *pnode;
       		(*pnode) = NULL;
       		free(aux);
       	}else if((*pnode)->esq != NULL && (*pnode)->dir == NULL) {
       		aux = *pnode;
       		(*pnode) = (*pnode)->esq;
       		free(aux);
       	}else if((*pnode)->esq == NULL && (*pnode)->dir != NULL) {
       		aux = *pnode;
       		(*pnode) = (*pnode)->dir;
       		free(aux);
       	}else {
       		paux = sucessor(pnode);
       		(*pnode)->reg = (*paux)->reg;
       		remove_node(&(*pnode)->dir, (*paux)->reg);
       	}
    }
    if((*pnode) != NULL) {
        (*pnode)->h = max(altura((*pnode)->esq), altura((*pnode)->dir)) + 1;

        int fb;
        int fbf;

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
    return ret;
}

void pre_order(tnode* pnode) {
    if(pnode != NULL) {
        printf("(%d,%d) ", pnode->reg, pnode->h);
        pre_order(pnode->esq);
        pre_order(pnode->dir);
    }
}

void in_order(tnode* pnode) {
    if(pnode != NULL) {
        in_order(pnode->esq);
        printf("(%d,%d) ", pnode->reg, pnode->h);
        in_order(pnode->dir);
    }
}

void pos_order(tnode* pnode) {
    if(pnode != NULL) {
        pos_order(pnode->esq);
        pos_order(pnode->dir);
        printf("(%d,%d) ", pnode->reg, pnode->h);
    }
}

void desenha_arv(tnode *pnode,int prof){
    int i;
    if (pnode != NULL){
        desenha_arv(pnode->esq,prof+1);
        for (i=0;i<prof;i++)
            printf("     ");
        printf("%d\n",pnode->reg);
        desenha_arv(pnode->dir,prof+1);
    }
}

int main() {

    tnode* tree;
    tree = NULL;
    int i, n, existe;
    int qtd_inserir, qtd_remover;

    scanf("%d %d", &qtd_inserir, &qtd_remover);
    for(i = 0; i < qtd_inserir; i++) {
        scanf("%d", &n);
        insere(&tree, n);
    }
    in_order(tree);
    for(i = 0; i < qtd_remover; i++) {
        scanf("%d", &n);
        existe = remove_node(&tree, n);
        if(existe == 0) {
            printf("NAOEXISTE\n");
        }else{
            pre_order(tree);
            printf("\n");
            in_order(tree);
            printf("\n");
            pos_order(tree);
            printf("\n");
            printf("\n");
        }
    }
    return 0;
}
