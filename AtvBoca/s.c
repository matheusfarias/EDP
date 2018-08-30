


tnode **sucessor(tnode** pnode) {
	tnode *aux;
	tnode **paux;


}


leaf




void remove_raiz(tnode** pnode) {
	tnode* aux;
	tnode** paux;

	if((*pnode)->esq == NULL && (*pnode)->dir == NULL) {
		aux = *pnode;
		(*pnode) = NULL;
		printf("first if: %d\n", aux->reg.id );
		free(aux);
	}else if((*pnode)->esq == NULL && (*pnode)->dir != NULL) {
		aux = *pnode;
		(*pnode) = (*pnode)->dir;
		printf("2 if: %d\n", aux->reg.id );
		free(aux);
	}else if((*pnode)->esq != NULL && (*pnode)->dir != NULL) {
		aux = *pnode;
		(*pnode) = (*pnode)->esq;
		printf("3 if: %d\n", aux->reg.id );
		free(aux);
	}else {
		printf("first else: %d\n", aux->reg.id );
		paux = sucessor(pnode);
		(*pnode)->reg = (*paux)->reg;

		remove_raiz(paux);
	}
}
