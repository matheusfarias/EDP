#include <stdio.h>
#include <stdlib.h>

typedef struct reg{
    int valor;
} treg;

typedef struct _node{
    treg reg;
    int altura;
    struct _node *esq;
    struct _node *dir;
} tnode;

tnode *cria_arvore(int num){

    tnode *arvore = (tnode *)malloc(sizeof(tnode));
    arvore->reg.valor = num;
    arvore->altura = 0;
    arvore->esq = NULL;
    arvore->dir = NULL;

    return arvore;
}

int altura_no(tnode *no){ //calcula a altura do no
    if (no == NULL){
        return -1;
    }
    else{
        return no->altura;
    }
}

int max(int a, int b){
    return (a > b) ? a : b;
}

void rotacao_esq(tnode **tree){
    tnode *x;
    tnode *y;
    tnode *a;
    tnode *b;
    x = *tree;
    y = x->dir;
    a = x->esq;
    b = y->esq;

    printf("RE %d\n", (*tree)->reg.valor);

    x->esq = a;
    x->dir = b;
    y->esq = x;
    *tree = y;

    x->altura = max(altura_no(x->esq), altura_no(x->dir)) + 1;
    y->altura = max(altura_no(y->esq), altura_no(y->dir)) + 1;
}

void rotacao_dir(tnode **tree){
    tnode *x;
    tnode *y;
    tnode *a;
    tnode *b;
    y = *tree;
    x = y->esq;
    a = x->esq;
    b = x->dir;

    printf("RD %d\n", (*tree)->reg.valor);

    x->esq = a;
    x->dir = y;
    y->esq = b;
    *tree = x;

    y->altura = max(altura_no(y->esq), altura_no(y->dir)) + 1;
    x->altura = max(altura_no(x->esq), altura_no(x->dir)) + 1;
}

void rebalancear(tnode **tree){
    int fator_balanco, fator_balanco_filho;
    tnode *filho;
    tnode *pai;

    pai = *tree;
    fator_balanco = altura_no(pai->esq) - altura_no(pai->dir);

    if (fator_balanco == 2){
        filho = pai->esq;
        fator_balanco_filho = altura_no(filho->esq) - altura_no(filho->dir);
        if (fator_balanco_filho == -1){
            rotacao_esq(&(pai->esq));
        }
        rotacao_dir(tree);
    }

    else if (fator_balanco == -2){
        filho = pai->dir;
        fator_balanco_filho = altura_no(filho->esq) - altura_no(filho->dir);
        if (fator_balanco_filho == 1){
            rotacao_dir(&(pai->dir));
        }
        rotacao_esq(tree);
    }
}

tnode **sucessor(tnode **tree){
    tnode *aux;
    tnode **paux;
    aux = (*tree)->dir;
    paux = &(*tree)->dir;
    while (aux->esq != NULL){
        paux = &(aux->esq);
        aux = aux->esq;
    }
    return paux;
}

int remove_avl(tnode **tree, int num){

    int aux, fator_balanceamento;
    tnode **capivara;
    tnode *paux;
    tnode *pai;
    pai = *tree;

    fator_balanceamento = altura_no(pai->esq) - altura_no(pai->dir);
    if(*tree == NULL){
        printf("Arvore vazia\n");
        return 0;
    }
    if(num < (*tree)->reg.valor){
        if((aux = remove_avl(&(*tree)->esq, num)) == 1){
            if(fator_balanceamento >= 2){
                if(altura_no((*tree)->dir->esq) <= altura_no((*tree)->dir->dir)){
                    rotacao_dir(tree);
                }else{
                    rotacao_esq(tree);
                }
            }
        }
    }
    if(num > (*tree)->reg.valor){
        if((aux = remove_avl(&(*tree)->dir, num)) == 1){
            if(fator_balanceamento >= -2){
                if(altura_no((*tree)->esq->dir) <= altura_no((*tree)->esq->esq)){
                    rotacao_esq(tree);
                }else{
                    rotacao_dir(tree);
                }
            }
        }
    }
    if(num == (*tree)->reg.valor){
        if(((*tree)->esq == NULL || (*tree)->dir == NULL)){
            paux = (*tree);

            if((*tree)->esq != NULL){
                *tree = (*tree)->esq;
            }else{
                *tree = (*tree)->dir;
            }
            free(paux);
        }else{//no tem 2 filhos
            capivara = sucessor(&(*tree)->dir);
            (*tree)->reg.valor = (*capivara)->reg.valor;
            remove_avl(&(*tree)->dir, (*tree)->reg.valor);
            if(fator_balanceamento >= 2){
                if(altura_no((*tree)->esq->dir) <= altura_no((*tree)->esq->esq)){
                    rotacao_esq(tree);
                }else{
                    rotacao_dir(tree);
                }
            }
        }
        return 1;
    }
    return aux;
}

void pre_order(tnode *tree){
    if (tree != NULL){
        printf("%d ", tree->reg.valor);
        pre_order(tree->esq);
        pre_order(tree->dir);
    }
}

void in_order(tnode *tree){
    if (tree != NULL){
        in_order(tree->esq);
        printf("(%d,%d) ", tree->reg.valor, tree->altura);
        in_order(tree->dir);
    }
}

void pos_order(tnode *tree){
    if (tree != NULL){
        pos_order(tree->esq);
        pos_order(tree->dir);
        printf("%d", tree->reg.valor);
    }
}

void insere_avl(tnode **tree, int num){
    if (*tree == NULL){
        *tree = cria_arvore(num);
    }
    else{
        if ((*tree)->reg.valor < num){
            insere_avl(&(*tree)->dir, num);
        }
        else{
            insere_avl(&(*tree)->esq, num);
        }
        (*tree)->altura = max(altura_no((*tree)->esq), altura_no((*tree)->dir)) + 1;
        rebalancear(tree);
    }
}

tnode **busca(tnode **tree, int num){

    tnode **aux;
    if (*tree == NULL){
        aux = NULL;
    }
    else if ((*tree)->reg.valor == num){
        aux = tree;
    }
    else{
        if ((*tree)->reg.valor < num){
            aux = busca(&((*tree)->dir), num);
        }
        else{
            aux = busca(&((*tree)->esq), num);
        }
    }
}

void imprime_arvore(tnode *tree, int p){
    int i;

    if (tree != NULL){
        imprime_arvore(tree->esq, p + 1);
        for (i = 0; i < p; i++){
            printf("   ");
        }
        printf("%d\n", tree->reg.valor);
        imprime_arvore(tree->dir, p + 1);
    }
}

int main(){

    tnode *arvore = NULL;
    int t, n, i, j, a, x;

    scanf("%d", &t);
    for (i = 0; i < t; i++){
        scanf("%d", &n);
        insere_avl(&arvore, n);
    }

    pre_order(arvore);

    //remove_avl(&arvore, 10);

	
	
    printf("\n");
	
	imprime_arvore(arvore, 0);
	
	printf("\n");

    // for(j = 0; j < a; j++){
    //     scanf("%d", &x);
    //     remove_avl(&arvore, x);
    // }
    //imprime_arvore(arvore, 0);
    //in_order(arvore);
    pre_order(arvore);

    return 0;
}
