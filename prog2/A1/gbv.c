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

    fread(&sb,sizeof(struct superBloco),1,f);

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

    /*abre o documento a ser inserido*/
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
    
    strncpy(new_doc.name,docname,MAX_NAME);
    new_doc.offset = ftell(gbv);

    /*itera enquanto ainda houverem bytes nao lidos*/
    while((data_read = fread(buffer,1,BUFFER_SIZE,doc)) > 0){
        fwrite(buffer,1,data_read,gbv); /*escreve na biblioteca o que esta no buffer*/
        doc_size += data_read;
    } 

    new_doc.size = doc_size;
    new_doc.date = time(NULL);

    /*aloca memoria para adicionar mais um doc*/
    if(!(lib->docs = realloc((lib->docs),(lib->count+1) * sizeof(Document)))){
        fclose(gbv);
        fclose(doc);
        
        return 1;
    }

    lib->docs[lib->count] = new_doc;
    lib->count++;
    
    sb.offset = ftell(gbv);
    sb.num_docs = lib->count;

    fwrite(lib->docs,sizeof(Document),lib->count,gbv);

    /*volta para o inicio e atualiza o superbloco*/
    fseek(gbv,0,SEEK_SET);
    fwrite(&sb,sizeof(struct superBloco),1,gbv);

    fclose(gbv);
    fclose(doc);

    return 0;
}

int gbv_remove(Library *lib, const char *archive, const char *docname){
    FILE *gbv;
    struct superBloco sb;
    int i;

    i = 0;

    /*procura o documento a ser removido*/
    while(i < lib->count && strcmp(docname,lib->docs[i].name) != 0)
        i++;

    /*caso elemento nao seja encontrado*/
    if(i == lib->count)
        return 1;

    for(;i < lib->count-1;i++)
        lib->docs[i] = lib->docs[i+1];

    lib->count--;

    if(!(gbv = fopen(archive, "rb+")))
        return 1;

    if(fread(&sb,sizeof(struct superBloco),1,gbv) != 1){
        fclose(gbv);
        return -1;
    }

    /*atualiza a area de diretorio*/
    fseek(gbv,sb.offset,SEEK_SET);
    fwrite(lib->docs,sizeof(Document),lib->count,gbv);

    /*atualiza o superbloco*/
    fseek(gbv,0,SEEK_SET);
    sb.num_docs = lib->count;
    fwrite(&sb.num_docs,sizeof(int),1,gbv);

    return 0;
}   

int gbv_list(const Library *lib){
    int i;

    if(lib->count == 0){
        printf("Biblioteca vazia\n");
        return 0;
    }

    for(i=0; i<lib->count; i++){
        Document d = lib->docs[i];
        char date[32];

        format_date(d.date,date,64);

        printf("Nome: %s\n", d.name);
        printf("Tamanho: %ld bytes\n", d.size);
        printf("Data de inserção: %s\n", date);
        printf("Offset: %ld\n\n", d.offset);
    }

    return 0;
}

int gbv_view(const Library *lib, const char *archive, const char *docname){
    FILE *gbv;
    char buffer[BUFFER_SIZE];
    struct superBloco sb;
    int i = 0;
    long offset;


    gbv = fopen(archive, "rb");

    /*vai para a area de diretorio*/
    fread(&sb,sizeof(struct superBloco),1,gbv);
    fseek(gbv,sb.offset,SEEK_SET);

    /*procura o documento*/
    while(i < lib->count && strcmp(docname,lib->docs[i].name) != 0)
        i++;

    offset = lib->docs[i].offset;
    fseek(gbv,offset,SEEK_SET);

    for(i=0;i < 5; i++){
        fread(buffer,1,BUFFER_SIZE,gbv);
        printf("%s", buffer);
    }
}

