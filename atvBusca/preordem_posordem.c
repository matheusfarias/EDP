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


void insere_em_tree(tnode** pnode, int id) {


	tnode* aux;
	aux = (tnode*) malloc(sizeof(tnode));
	aux->reg.id = id;
	aux->dir = NULL;
	aux->esq = NULL;



	if(*pnode == NULL) {		
		*pnode = aux;

		

		//
	}else {
		tnode* p = *pnode;
		tnode* r;
		while(p != NULL) {
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

	}

}


void posorder(tnode *pnode){
    if (pnode != NULL){
        posorder(pnode->esq);
        posorder(pnode->dir);
        printf("%d\n",pnode->reg.id);
    }
}


int main() {

	tnode* tree = NULL;

	int n;

	while(scanf("%d ", &n) == 1) {
		insere_em_tree(&tree, n);
	}

	posorder(tree);

	
	/*
	scanf("%d", &n);
	while(n != 0) {
		insere_em_tree(&tree, n);
		scanf("%d", &n);
	}

	*/
	
	return 0;
}