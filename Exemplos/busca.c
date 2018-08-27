#include<stdio.h>
#include<stdlib.h>



typedef struct _reg{
    int id;
}treg;


typedef struct _lista{
    treg * v;
    int tam;
    int (*compara)(const void *a,const void *b);
}tlista;

int meucompara(const void *a, const void *b){
    return (((treg *)a)->id - ((treg *)b)->id);  
}


int constroi_lista(tlista * l, int tam, int (*cmp)(const void *a, const void *b)){
    int ret = 1;
    l->v = (treg *)malloc(sizeof(treg)*tam);
    if (l->v == NULL)
        ret = 0;
    l->tam = tam;
    l->compara = cmp;
    return ret;
}

void preenche_lista(tlista *l){
    int i;
    for (i=0;i<l->tam;i++){
        l->v[i].id = rand()%100;
      /*  printf("%d %d\n",i,l->v[i].id);*/
    }
}


int busca1(tlista *l, treg * reg){
    int i = 0;
    while(l->compara(&l->v[i],reg) != 0 && i<l->tam)
        i++;
    if (l->compara(&l->v[i],reg) != 0) 
        i = -1;
    return i;
    
}

int busca2(tlista *l, treg * reg){
    bsearch(reg,l->v,l->tam,sizeof(treg),l->compara);
}

int main(void){
    tlista l;
    int tam = 1000000000;
    int tbusca = 100000;
    int i;
    int pos;
    treg reg;

    constroi_lista(&l,tam,meucompara);
    preenche_lista(&l);
    for (i = 0;i<tbusca;i++){
        reg.id = rand()%100;
        pos = busca1(&l,&reg);
/*        if (pos >=0 ){
            printf("Achei, o numero %d esta em %d\n",reg.id,pos);
        }else{
            printf("nao achei =(\n");
        }*/
        if (i%10000==0)
            printf(".");
    }

    qsort(l.v,l.tam,sizeof(treg),meucompara);
  /*  for(i=0;i<l.tam;i++){
        printf("%d ",l.v[i].id);
    }*/
    for (i = 0;i<tbusca;i++){
        reg.id = rand()%100;
        pos = busca2(&l,&reg);
    }






    return 0;
}
