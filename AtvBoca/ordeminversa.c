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


void inorder(tnode *pnode){
    if (pnode != NULL){
        inorder(pnode->dir);
        printf("%d ",pnode->reg.id);
        inorder(pnode->esq);
    }
}

int main() {
    
    tnode* tree = NULL;
    int n, x, i;

    scanf("%d", &x);
    for(i = 0; i < x; i++) {
        scanf("%d", &n);
        insertTree(&tree, n);
    }

    printf("\n");

    inorder(tree);

    printf("\n");
    
    return 0;
}