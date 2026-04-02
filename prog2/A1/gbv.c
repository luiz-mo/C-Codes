#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "gbv.h"

struct superBloco{
    int num_docs;
    long offset;
};

int gbv_create(const char *filename){
    struct superBloco sb;
    FILE *f;

    if(!(f = fopen(filename, "wb"))){
        perror("erro ao criar arquivo");
        return 1;
    }

    sb.num_docs = 0;
    sb.offset = sizeof(int) + sizeof(long); /*tamanho do num_docs+offset em bytes*/

    fwrite(&sb.num_docs,sizeof(int),1,f);
    fwrite(&sb.offset,sizeof(long),1,f);

    fclose(f);

    return 0;
}

int gbv_open(Library *lib, const char *filename){
    struct superBloco sb;
    FILE *f;    

    if(!(f = fopen(filename, "rb")))
        return 1;

    fread(&sb.num_docs,sizeof(int),1,f);
    fread(&sb.offset,sizeof(long),1,f);

    lib->count = sb.num_docs;

    fseek(f,sb.offset,SEEK_SET);

    if(sb.num_docs > 0)
        if(!(lib->docs = malloc(sb.num_docs * sizeof(Document))))
            return 1;
    else
        lib->docs = NULL;

    fread(lib->docs,sizeof(Document),sb.num_docs,f);

    fclose(f);

    return 0;
}

int gbv_add(Library *lib, const char *archive, const char *docname){


}

int gbv_remove(Library *lib, const char *docname){

}   

int gbv_list(const Library *lib){
    struct superBloco sb;
    FILE *f;

    fopen()
}

int gbv_view(const Library *lib, const char *docname){

}

int gbv_order(Library *lib, const char *archive, const char *criteria){

}
