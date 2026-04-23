#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "gbv.h"

struct superBloco{
    long offset;
    int num_docs;
};

int gbv_create(const char *filename){
    struct superBloco sb;
    FILE *f;

    if(!(f = fopen(filename, "wb"))){
        perror("erro ao criar arquivo");
        return 1;
    }

    sb.num_docs = 0;
    sb.offset = sizeof(struct superBloco);

    fwrite(&sb,sizeof(struct superBloco),1,f);

    fclose(f);

    return 0;
}

int gbv_open(Library *lib, const char *filename){
    struct superBloco sb;
    FILE *f;    

    if(!(f = fopen(filename, "rb"))){
        return 1;
    }

    if(fread(&sb,sizeof(struct superBloco),1,f) != 1){
        fclose(f);

        return 1;
    }
    lib->count = sb.num_docs;

    fseek(f,sb.offset,SEEK_SET);

    if(sb.num_docs > 0){
        if(!(lib->docs = malloc(sb.num_docs * sizeof(Document)))){
            fclose(f);

            return 1;
        }   
    
        if(fread(lib->docs,sizeof(Document),sb.num_docs,f) != sb.num_docs){
            fclose(f);
            free(lib->docs);
            lib->docs = NULL;

            return 1;
        }
    }     
    else
        lib->docs = NULL;

    fclose(f);

    return 0;
}

int gbv_replace(Library *lib, const char *archive, const char *docname, FILE *gbv, FILE *doc, struct superBloco sb, int i){
    
    Document old_doc = lib->docs[i];
    
    gbv_remove(lib,archive,docname);

    if(!(doc = fopen(docname, "rb"))){
        return 1;
    }
}

int gbv_add(Library *lib, const char *archive, const char *docname){
    size_t data_read;
    struct superBloco sb;
    FILE *gbv, *doc;
    char buffer[BUFFER_SIZE];
    Document new_doc, *tmp;
    long doc_size = 0;
    int i;

    if((strcmp(archive, docname)) == 0)
        return 1;
            
    if((strlen(docname)) >= MAX_NAME)
        return 1;

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

    for(i=0;i < lib->count;i++)
        if(strcmp(lib->docs[i].name,docname) == 0)
            gbv_replace(lib,archive,docname,gbv,doc,sb,i);

    /*procura a posicao de escrever o novo documento*/
    fseek(gbv,sb.offset,SEEK_SET);
    
    strncpy(new_doc.name,docname,MAX_NAME-1);
    new_doc.name[MAX_NAME-1] = '\0'; /*strncpy pode nao terminar com \0*/
    new_doc.offset = ftell(gbv);

    /*itera enquanto ainda houverem bytes nao lidos*/
    while((data_read = fread(buffer,1,BUFFER_SIZE,doc)) > 0){
        fwrite(buffer,1,data_read,gbv); /*escreve na biblioteca o que esta no buffer*/
        doc_size += data_read;
    }

    new_doc.size = doc_size;
    new_doc.date = time(NULL);

    /*aloca memoria para adicionar mais um doc*/
    if(!(tmp = realloc((lib->docs),(lib->count+1) * sizeof(Document)))){
        fclose(gbv);
        fclose(doc);
        
        return 1;
    }

    lib->docs = tmp;

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
    Document *temp;
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

    temp = realloc(lib->docs,lib->count * sizeof(Document));

    if(temp || lib->count == 0)
        lib->docs = temp;

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
    fwrite(&sb,sizeof(struct superBloco),1,gbv);

    fclose(gbv);

    return 0;
}   

int gbv_list(const Library *lib){
    int i;

    if(lib->count == 0){
        printf("Biblioteca vazia\n");
    }

    for(i=0; i<lib->count; i++){
        Document d = lib->docs[i];
        char date[32];

        format_date(d.date,date,32);

        printf("Nome: %s\n", d.name);
        printf("Tamanho: %ld bytes\n", d.size);
        printf("Data de inserção: %s\n", date);
        printf("Offset: %ld\n\n", d.offset);
    }

    return 0;
}

void print_bloco(FILE *gbv, size_t *remaining){
    size_t size_read,read;
    char buffer[BUFFER_SIZE];
    int i = 0;

    while(*remaining > 0 && i < BLOCK_SIZE){
        if(*remaining > BUFFER_SIZE)
            size_read = BUFFER_SIZE;
        else
            size_read = *remaining;

        read = fread(buffer,1,size_read,gbv);
        
        if(read == 0)
            break;

        fwrite(buffer,1,read,stdout);
        printf("\n");

        *remaining -= read;
        i++;
    }
}

int gbv_view(const Library *lib, const char *archive, const char *docname){
    FILE *gbv;
    Document doc;
    char op = 'n';
    struct superBloco sb;
    int i = 0;
    size_t remaining, total_blocks, block_bytes;

    block_bytes = BUFFER_SIZE * BLOCK_SIZE;

    if(!(gbv = fopen(archive, "rb")))
        return -1;

    /*vai para a area de diretorio*/
    if(fread(&sb,sizeof(struct superBloco),1,gbv) != 1){
        fclose(gbv);
        return -1;
    }

    fseek(gbv,sb.offset,SEEK_SET);

    while(i < lib->count && strcmp(docname,lib->docs[i].name) != 0)
        i++;
        
    /*procura o documento*/
    if(i == lib->count){
        fclose(gbv);

        return 1;
    }

    doc = lib->docs[i];
    
    total_blocks = (doc.size + block_bytes -1) / block_bytes; /*isso calcula o teto*/

    i = 0;
    do{
        switch(op){
            case('n'):
                if(i >= total_blocks){
                    printf("Documento chegou ao fim\n");
                    break;
                }

                fseek(gbv,doc.offset + (i * block_bytes),SEEK_SET);
                if(i * block_bytes >= doc.size)
                    remaining = 0;
                else
                    remaining = doc.size - (i * block_bytes);

                print_bloco(gbv,&remaining);

                i++;
                break;
    
            case('p'):
                if(i <= 1){
                    printf("Ja esta no primeiro bloco\n");
                    break;
                }

                i -= 2;

                fseek(gbv,doc.offset + (i * block_bytes),SEEK_SET);

                if(i * block_bytes >= doc.size)
                    remaining = 0;
                else
                    remaining = doc.size - (i * block_bytes);

                print_bloco(gbv,&remaining);
                
                i++;
                break;

            default:
                printf("Operacao invalida\n");
        }

        printf("--------------------------------------\n");
        printf("n -> proximo bloco\n");
        printf("p -> bloco anterior\n");
        printf("q -> sair da visualizacao\n");
        scanf(" %c", &op);
        printf("--------------------------------------\n");
    } while(op != 'q');
    fclose(gbv);
    
    return 0;
}

