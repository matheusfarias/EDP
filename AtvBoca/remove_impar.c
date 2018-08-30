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

/*
tnode** sucessor(tnode** pnode) {
	tnode** aux;
	aux = &((*pnode)->dir);
	while((*aux)->esq != NULL)
		aux = &(*aux)->esq;
	return aux;

}

*/


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

/*
void in_order(tnode *pnode){
    if (pnode != NULL){
        in_order(pnode->esq);
        printf("%d ",pnode->reg.id);
        in_order(pnode->dir);
    }
}




*/


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




void remove_so_impar(tnode* pnode) {

	if (pnode != NULL){
        remove_so_impar(pnode->esq);
        if(pnode->reg.id % 2 != 0) {
        	printf("removendo %d\n", pnode->reg.id);
        	remover(&pnode, pnode->reg.id);
        }
        remove_so_impar(pnode->dir);
    }
}


int main() {


	tnode* tree = NULL;
    int n, x, i;
    tnode** paux = NULL;


    
    scanf("%d", &x);
    for(i = 0; i < x; i++) {
        scanf("%d", &n);
        insertTree(&tree, n);
    }


   remove_so_impar(tree);

   printf("\n");


   preorder(tree);

   printf("\n");

    /*
    #ifdef	DEBUG
    freopen("remove.in", "r", stdin);
    #endif
	*/

    //printf("OK\n");

    return 0;

}

