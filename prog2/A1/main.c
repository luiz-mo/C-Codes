#include <stdio.h>
#include <string.h>
#include "gbv.h"

int main(int argc, char *argv[]) {
    int ret;

    if (argc < 3) {
        printf("Uso: %s <opção> <biblioteca> [documentos...]\n", argv[0]);
        return 1;
    }

    const char *opcao = argv[1];
    const char *biblioteca = argv[2];    

    Library lib;
    if (gbv_open(&lib, biblioteca) != 0) {
        gbv_create(biblioteca);
        return 1;
    }

    if (strcmp(opcao, "-a") == 0) {
        for (int i = 3; i < argc; i++) {
            if(gbv_add(&lib, biblioteca, argv[i]) == 0)
                printf("Documento %s adicionado\n", argv[i]);
            else
                printf("Erro ao adicionar documento %s\n", argv[i]);
        }
    }
    else if (strcmp(opcao, "-r") == 0) {
        for (int i = 3; i < argc; i++) {
            ret = gbv_remove(&lib, biblioteca, argv[i]);
            if(ret == 0)
                printf("Documento %s removido\n", argv[i]);
            else if(ret == 1)
                printf("Documento %s nao encontrado\n", argv[i]);
            else
                printf("Erro ao remover\n");
        }
    }
    else if (strcmp(opcao, "-l") == 0) {
        gbv_list(&lib);
    }
    else if (strcmp(opcao, "-v") == 0 && argc >= 4) {
        gbv_view(&lib, biblioteca, argv[3]);
    }
    else {
        printf("Opção inválida.\n");
    }

    return 0;
}

