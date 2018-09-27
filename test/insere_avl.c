#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  int reg;
  int h;
  struct node* esq;
  struct node* dir;
}tnode;

int altura(tnode* pnode) {
  int ret;
  if(pnode == NULL)
    ret = -1;
  else
    ret = pnode->h;
  return ret;
}

int max(int a, int b) {
  (a>b)?a:b;
}

void LR (tnode** pnode) { //x, y, a, b
  //declaração
  tnode* x;
  tnode* y;
  tnode* a;
  tnode* b;
  //atribuição
  x = *pnode;
  y = x->dir;
  a = x->esq;
  b = y->esq;
  //print
  printf("LR %d\n", x->reg);
  //rotacao
  x->dir = b;
  y->esq = x;
  *pnode = y;
  //att altura
  x->h = max(altura(x->esq), altura(x->dir)) + 1;
  y->h = max(altura(y->esq), altura(y->dir)) + 1;
}

void RR (tnode** pnode) {
  //declaração
  tnode* x;
  tnode* y;
  tnode* a;
  tnode* b;
  //atribuição
  y = *pnode;
  x = y->esq;
  a = x->esq;
  b = x->dir;
  //print
  printf("RR %d\n", y->reg);
  //rotacao
  y->esq = b;
  x->esq = a;
  x->dir = y;
  *pnode = x;
  //att altura
  y->h = max(altura(y->esq), altura(y->dir)) + 1;
  x->h = max(altura(x->esq), altura(x->dir)) + 1;
}

tnode** sucessor(tnode** pnode) {
  tnode* aux;
  tnode** paux;
  aux = (*pnode)->dir;
  paux = &(*pnode)->dir;
  while (aux->esq != NULL) {
    paux = &(aux->esq);
    aux = aux->esq;
  }
  return paux;
}

void rebalancear(tnode** pnode) {
  int fb, fbf;
  tnode* pai;
  tnode* filho;
  pai = *pnode;
  fb = altura(pai->esq) - altura(pai->dir);
  if(fb == 2) {
    filho = pai->esq;
    fbf = altura(filho->esq) - altura(filho->dir);
    if(fbf == -1)
      LR(&(pai->esq));
    RR(pnode);
  }else if(fb == -2) {
    filho = pai->dir;
    fbf = altura(filho->esq) - altura(filho->dir);
    if(fbf == 1)
      RR(&(pai->dir));
    LR(pnode);
  }
}

void insere(tnode** pnode, int n) {
  if(*pnode == NULL) {
    *pnode = (tnode*)malloc(sizeof(tnode));
    (*pnode)->num = n;
    (*pnode)->h = 0;
    (*pnode)->dir = NULL;
    (*pnode)->esq = NULL;

  }else {
    if(n > (*pnode)->)
  }
}
//
int main() {

  printf("ok\n");

  /*
  int i, x, n;
  tnode* tree;

  scanf("%d", &x);
  for(i = 0; i < x; i++) {
    scanf("%d", &n);
    insere(&tree, n);
  }

  printf("\n");
  pre_order(tree);
  printf("\n");
  */
  return 0;
}
