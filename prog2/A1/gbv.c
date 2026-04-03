#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    fwrite(&sb,sizeof(struct superBloco),1,f);

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

    if(sb.num_docs > 0){
        if(!(lib->docs = malloc(sb.num_docs * sizeof(Document)))){
            fclose(f);
            return 1;
        }   
    
        fread(lib->docs,sizeof(Document),sb.num_docs,f);
    }     
    else
        lib->docs = NULL;

    fclose(f);

    return 0;
}

int gbv_add(Library *lib, const char *archive, const char *docname){
    size_t data_read;
    struct superBloco sb;
    FILE *gbv, *doc;
    char buffer[BUFFER_SIZE];
    Document new_doc;
    long doc_size = 0;

    /*abre a biblioteca*/
    if(!(gbv = fopen(archive,"rb+")))
        return 1;

    /*cria o documento a ser inserido*/
    if(!(doc = fopen(docname, "rb"))){
        fclose(gbv);

        return 1;
    }

    /*le superbloco*/
    if(fread(&sb,sizeof(struct superBloco),1,gbv) != 1){
        fclose(gbv);
        fclose(doc);

        return 1;
    }

    /*procura a posicao de escrever o novo documento*/
    fseek(gbv,sb.offset,SEEK_SET);
    
    /*itera enquanto ainda houverem bytes nao lidos*/
    while((data_read = fread(buffer,1,BUFFER_SIZE,doc) > 0)){
        fwrite(buffer,1,data_read,gbv); /*escreve na biblioteca o que esta no buffer*/
        doc_size += data_read;
    }

    strcpy(new_doc.name,docname); 
    new_doc.offset = ftell(gbv);
    new_doc.size = doc_size;

    lib->docs[lib->count] = new_doc;
    
    sb.offset
}

int gbv_remove(Library *lib, const char *docname){

}   

int gbv_list(const Library *lib){
    int i;
    
    if(lib->count == 0){
        printf("Biblioteca vazia\n");
        return 0;
    }

    for(i=0; i<lib->count; i++){
        Document d = lib->docs[i];

        printf("Nome: %s\n", d.name);
        printf("Tamanho: %ld bytes\n", d.size);
        printf("Data de inserção: %s", d.date);
        printf("Offest: %d", d.offset);
    }

    return 0;
}

int gbv_view(const Library *lib, const char *docname){

}

int gbv_order(Library *lib, const char *archive, const char *criteria){
    if(strcmp(criteria, "nome"))

    else if(strcmp(criteria, "data"))

    else if(strcmp(criteria, "tamanho"))

    else{
        printf("Criterio invalido");
        return 1;
    }


}
