#include <stdio.h>
#include <stdlib.h>

typedef struct regis {
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

void rd (tnode** pnode) {
    tnode* x = *pnode;
    tnode* y = x->esq;
    tnode* b = y->dir;
    x->esq = b;
    y->dir = x;
    *pnode = y;
}

void re(tnode** pnode) {
    tnode* x = *pnode;
    tnode* y = x->dir;
    tnode* b = y->esq;
    x->dir = b;
    y->esq = x;
    *pnode = y;
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

int main() {

    tnode* tree = NULL;
    tnode ** aux;
	int x, i;
    scanf("%d", &x);
    for (i = 0; i < x; i++) {
        tree = NULL;
        char op;
        int y = 0, j, n, m;
        scanf("%d" , &y);
        for(j = 0; j < y; j++) {
            scanf("%d", &n);
            insertTree(&tree, n);
        }
        scanf(" %c", &op);
        scanf("%d", &m);
        preorder(tree);
        printf("\n");
        aux = busca(&tree, m);
        if(op == 'D')
            rd(aux);
        if(op == 'E')
            re(aux);
            
        preorder(tree);
        printf("\n");


    }   
    return 0;

}

