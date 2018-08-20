#include <stdio.h>
#include <stdlib.h>

typedef struct regis {
    int id;
}treg;


typedef struct cel_resp {
    int id;
    struct cel_resp* prox;
}tresp;


typedef struct node {
    treg reg;
    struct node* esq;
    struct node* dir;
}tnode;


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

void imprime(tresp* presp) {
    tresp* p;

    for(p = presp; p!= NULL; p = p->prox)
        printf("%d\n", p->id);

}

void insertTree(tnode** pnode, int id, int* profundidade) {

    tnode* aux;
    aux = (tnode*) malloc(sizeof(tnode));
    aux->reg.id = id;
    aux->dir = NULL;
    aux->esq = NULL;

    int prof = 0;

    if(*pnode == NULL)
        *pnode = aux;
    else{
        tnode* p = *pnode;
        tnode* r;
        while(p != NULL) {
            prof++;
            r = p;
            if(id < p->reg.id)
                p = p->esq;
            else
                p = p->dir;
        }

        if(id < r->reg.id)
            r->esq = aux;
        else
            r->dir = aux;


        if (prof > *profundidade) 
            *profundidade = prof;
        

            
    }
}

void destroys(tnode* pnode) {
    if(pnode != NULL) {
        destroys(pnode->esq);
        destroys(pnode->dir);
        free(pnode);
    }
}



int main() {

    
    tresp* resposta = NULL;
    tnode* tree = NULL;

    int n, depth = 0;

    int x, y, i, j;
    
    scanf("%d", &x);
    for(i = 0; i < x; i++) {
       scanf(" %d", &y);
       for(j = 0; j < y; j++) {
           scanf(" %d", &n);
           insertTree(&tree, n, &depth);
       }
       insertResult(&resposta, depth);
       destroys(tree);
       tree = NULL;
       depth = -1;
    }
    imprime(resposta);


    return 0;

}