#include <stdio.h>
#include <stdlib.h>

typedef struct reg {
    int id;
}treg;

typedef struct node {
    treg reg;
    struct node* esq;
    struct node* dir;
}tnode;

typedef struct cel_resp {
    int id;
    struct cel_resp* prox;
}tresp;

void insertResult(tresp** presp , int n) {

    tresp* aux;
    aux = (tresp*) malloc(sizeof(tresp));
    aux->id = n;
    aux->prox = NULL;

    if(*presp == NULL)
        *presp = aux;
    else {
        tresp* p = *presp;
        while(p->prox != NULL)
            p = p->prox;

        p->prox = aux;
    }
}

tnode* alocaNode (int id) {
    tnode* aux;
    aux = (tnode*) malloc(sizeof(tnode));
    aux->reg.id = id;
    aux->esq = NULL;
    aux->dir = NULL;

    return aux;
}

void insertTree(tnode** pnode, int n) {
    if(*pnode == NULL) {
        *pnode = alocaNode(n);
    }else if((*pnode)->reg.id < n) {
        insertTree(&(*pnode)->dir, n);
    }else {
        insertTree(&(*pnode)->esq, n);
    }
}

void preorder(tnode* pnode) {
	if(pnode != NULL)  {
		printf("%d ",pnode->reg.id);
		preorder(pnode->esq);
		preorder(pnode->dir);
	}
}

tnode** busca(tnode** pnode, int n) {
	tnode** ret;
	if(*pnode == NULL)
		ret = NULL;
	else if((*pnode)->reg.id == n)
		ret = pnode;
	else {
		if((*pnode)->reg.id < n)
			ret = busca(&(*pnode)->dir, n);
		else
			ret = busca(&(*pnode)->esq, n);
	}
	return ret;
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

void remove_raiz(tnode** pnode) {
	tnode* aux;
	tnode** paux;

	if((*pnode)->esq == NULL && (*pnode)->dir == NULL) {
		aux = *pnode;
		(*pnode) = NULL;
		free(aux);
	}else if((*pnode)->esq != NULL && (*pnode)->dir == NULL) {
		aux = *pnode;
		(*pnode) = (*pnode)->dir;
		free(aux);
	}else if((*pnode)->esq == NULL && (*pnode)->dir != NULL) {
		aux = *pnode;
		(*pnode) = (*pnode)->esq;
		free(aux);
	}else {
		paux = sucessor(pnode);
		(*pnode)->reg = (*paux)->reg;
		remove_raiz(paux);
	}
}

void desenha_arv(tnode *pnode,int prof){
    int i;
    if (pnode != NULL){
        desenha_arv(pnode->esq,prof+1);
        for (i=0;i<prof;i++)
            printf("     ");
        printf("%d\n",pnode->reg.id);
        desenha_arv(pnode->dir,prof+1);
    }
}

int remover(tnode** pnode, int n) {
	int ret = 0;
	tnode** aux;
	aux = NULL;
	aux = busca(pnode, n);
	if(aux != NULL) {
		remove_raiz(aux);
		ret = 1;
	}
	return ret;
}

void busca_impar(tnode* pnode, tresp** presp) {

	if(pnode != NULL) {
		if(pnode->reg.id % 2 != 0)
			insertResult(presp, pnode->reg.id);
		busca_impar(pnode->esq, presp);
		busca_impar(pnode->dir, presp);
	}
}

void remove_so_impar(tnode** pnode, tresp* presp) {
	tresp* aux = presp;

	while(aux != NULL) {
		printf("removendos %d\n", aux->id);
		remover(pnode, aux->id);
		aux = aux->prox;
	}
}

void imprime(tresp* presp) {
    tresp* p;
    for(p = presp; p!= NULL; p = p->prox)
        printf("%d\n", p->id);
}

int main() {
	tnode* tree = NULL;
    int n, x, i;

    tresp* resposta = NULL;

    scanf("%d", &x);
    for(i = 0; i < x; i++) {
        scanf("%d", &n);
        insertTree(&tree, n);
    }

   busca_impar(tree, &resposta);

   remove_so_impar(&tree, resposta);

   preorder(tree);

   return 0;
}
