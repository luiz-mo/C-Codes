#include <stdio.h>

int main(){
    int n, l;
    FILE *arq;
    arq = fopen("teste","w");

    if(!arq){
        perror("erro ao abrir arquivo\n");
        return 1;
    }

    
    n = 10;
    l = 1;
    while(l <= n){
        if(l % 2 == 0)
            fputs("m\n",arq);
        else
            fputs("l\n",arq);
        l++;
    }
    
/*
    char linha[256];
    while(fgets(linha, sizeof(linha), arq) != NULL)
        printf("%s", linha);
*/
    fclose(arq);

    return 0;
}