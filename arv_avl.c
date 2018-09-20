#include <stdio.h>
#include <stdlib.h>

typedef struct reg{
    int valor;
}treg;

typedef struct _node{
    treg reg;
    int altura;
    struct _node *esq;
    struct _node *dir;
}tnode;

tnode *cria_arvore(int num){

    tnode *arvore = (tnode *)malloc(sizeof(tnode));
    arvore->reg.valor = num;
    arvore->altura = 0;
    arvore->esq = NULL;
    arvore->dir = NULL;

    return arvore;
}

int altura_no(tnode *no){//calcula a altura do no
    if(no == NULL){
        return -1;
    }else{
        return no->altura;
    }
}

int max(int a, int b){
	return (a>b)?a:b;
}


void rotacao_esq(tnode ** tree){
    tnode * x;
    tnode * y;
    tnode * a;
    tnode * b;
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

void rotacao_dir(tnode ** tree){
    tnode * x;
    tnode * y;
    tnode * a;
    tnode * b;
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
	
	if(fator_balanco == 2){
		filho = pai->esq;
		fator_balanco_filho = altura_no(filho->esq) - altura_no(filho->dir);
		if(fator_balanco_filho == -1){
			rotacao_esq(&(pai->esq));
		}
		rotacao_dir(tree);
	}

	else if(fator_balanco == -2){
		filho = pai->dir;
		fator_balanco_filho = altura_no(filho->esq) - altura_no(filho->dir);
		if(fator_balanco_filho == 1){
			rotacao_dir(&(pai->dir));
		}
		rotacao_esq(tree);
	}
}

void in_order(tnode *tree){
    if (tree != NULL){
        in_order(tree->esq);
        printf("(%d,%d) ", tree->reg.valor, tree->altura);
        in_order(tree->dir);
    }
}

void insere_avl(tnode **tree, int num){
    if(*tree == NULL){
        *tree = cria_arvore(num);
    }else{
        if((*tree)->reg.valor < num){
            insere_avl(&(*tree)->dir, num);
        }else{
            insere_avl(&(*tree)->esq, num);
        }
        (*tree)->altura = max(altura_no((*tree)->esq), altura_no((*tree)->dir)) + 1;
        rebalancear(tree);
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
    int t, n, i;

    scanf("%d", &t);
    for(i = 0; i < t; i++){
    	scanf("%d", &n);
    	insere_avl(&arvore, n);
    }
    //imprime_arvore(arvore, 0);
    in_order(arvore);
    

    return 0;
}