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


tnode** sucessor(tnode** pnode) {
	tnode** aux;
	aux = &((*pnode)->dir);
	while((*aux)->esq != NULL)
		aux = &(*aux)->esq;
	return aux;

}



void remove_raiz(tnode** pnode) {
	tnode* aux;
	tnode** paux;

	if((*pnode)->esq == NULL && (*pnode)->dir == NULL) {
		aux = *pnode;
		(*pnode) = NULL;
		free(aux);
	}else if((*pnode)->esq == NULL && (*pnode)->dir != NULL) {
		aux = *pnode;
		(*pnode) = (*pnode)->dir;
		free(aux);
	}else if((*pnode)->esq != NULL && (*pnode)->dir != NULL) {
		aux = *pnode;
		(*pnode) = (*pnode)->esq;
		free(aux);
	}else {
		paux = sucessor(pnode);
		(*pnode)->reg = (*paux)->reg;
		remove_raiz(paux);
	}
}




int remover(tnode** pnode, int n) {
	int ret = 0;
	tnode** aux;
	aux = NULL;
	aux = busca(pnode, n);
	remove_raiz(aux);
	if(aux != NULL)
		ret = 1;
	return ret;
}














int main() {


	tnode* tree = NULL;
    int n, x, i;
    



    
    scanf("%d", &x);
    for(i = 0; i < x; i++) {
        scanf("%d", &n);
        insertTree(&tree, n);
    }




    
    tnode** search = NULL;

    search = busca(&tree, 12);

    if(search != NULL)
    	printf("achou: %d\n", (*search)->reg.id);
    else
    	printf("NAO ENCONTRADO\n");
   	




    


    //printf("OK\n");

    return 0;

}

