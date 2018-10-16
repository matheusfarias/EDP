#include <stdio.h>
#include <stdlib.h>
int main() {

    char a;
    FILE* point;
    int i, b[4];
    point = fopen("teste.txt", "r");
    for(i = 0; i < 4; i++) {
        a = fgetc(point);
        b[i] = atoi(&a);    
    }

    fclose(point);

    for (i = 0; i < 4; i++) {
        printf("%d\n", b[i]);
    }

    return 0;


    FILE* f = fopen("teste.txt", "r");
    int number = 0;
    int sum = 0;
    

    while (fscanf(f, "%d,", &number) > 0) {
        sum += number;
    }


    printf("soma: %d\n", sum);

    fclose(f);


    return 0;

}