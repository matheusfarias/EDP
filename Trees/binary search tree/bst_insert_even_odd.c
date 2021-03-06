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

tnode* alocaFirstNode() {
    tnode* aux;
    aux = (tnode*) malloc(sizeof(tnode));
    aux->reg.id = (int)NULL;
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
	if(pnode != NULL) {
		printf("%d ", pnode->reg.id);
        preorder(pnode->esq);
        preorder(pnode->dir);
	}
}

int main() {

    tnode* tree = NULL;
    tree = alocaFirstNode();
    int n, x, i;

    scanf("%d", &x);
    for(i = 0; i < x; i++) {
        scanf("%d", &n);
        if((n % 2) == 0)
            insertTree(&tree->esq, n);
        else
            insertTree(&tree->dir, n);
    }

    preorder(tree->esq);
    printf("\n");
    preorder(tree->dir);
    printf("\n");
    
    return 0;
}