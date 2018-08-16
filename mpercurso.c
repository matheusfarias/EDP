#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct _reg {
  int id;
}treg;


typedef struct _node {
  treg reg;
  struct _node* esq;
  struct _node* dir;
}tnode;


void preorder(tnode* pnode) {
	if(pnode != NULL) {
		printf("%d ", pnode->reg.id);
		preorder(pnode->esq);
		preorder(pnode->dir);

	}
}



tnode* aloca_node(int id) {

	tnode* aux;
	aux = (tnode*)malloc(sizeof(tnode));
	aux->reg.id = id;
	aux->dir = NULL;
	aux->esq = NULL;
	return aux;
}




void drawt(tnode* pnode, int prof) {

	int i;
	if (pnode != NULL) {
		drawt(pnode->esq, prof+1);
		for	(i = 0; i < prof; i++)
			printf("     ");
		printf("%d\n", pnode->reg.id);
		drawt(pnode->dir, prof+1);
	}
}




int main(void){
    tnode *arv;
    arv = aloca_node(20);
    arv->esq = aloca_node(10);
    arv->dir = aloca_node(30);

    arv->esq->esq = aloca_node(5);
    arv->esq->dir = aloca_node(15);

    arv->dir->esq = aloca_node(25);
    arv->dir->dir = aloca_node(35);

    arv->esq->dir->esq = aloca_node(13);
    arv->esq->dir->dir = aloca_node(17);

    


	preorder(arv);

	printf("\n");

    //drawt(arv,0);

    return 0;
}















