#include "insere.h"

int menor(int a, int b) {
	return a<b?a:b;
}

tnode* aloca_node(tarv* parv) {
	tnode* aux;
	aux = (tnode*)malloc(sizeof(tnode));
	if(aux == NULL) {
		aux->n = 0;
       		aux->folha = 0;	
	}else
		printf("Falha na alocacao");
	return aux;
}	

void btree_constroi(tarv* parv, int t) {
	parv->t = t;
	parv->raiz = aloca_node(parv);
	parv->raiz->n = 0;
	parv->raiz->folha = TRUE;
}

int procura_chave(tnode* x, int k) {
	int ret, i;
	ret = -1;
	for(i = 0; i < x->n; i++) {
		if(k == x->chaves[i]) 
			ret = i;
	}
	return ret;	
}
int procura_ic(tnode* x, int k) {
	
}

void insere_node(tarv* arv, 





