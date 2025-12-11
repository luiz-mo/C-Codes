#ifndef Heap
#define Heap

/*Estrutura do paciente: nome e a prioridade*/
struct paciente {
    char nome[50];
    int prioridade; //Max heap
}; 

/*
Sacode o heap, elemento de heap[1] percorre o heap até se encontrar. 
Essa versão do SacodeHeap é adaptada ao resto do código para sua reutilização,
por isso "i" é passado como parâmetro
*/
void SacodeHeap (int i, int tam, struct paciente *heap[], int *comparacoes, int *trocas);

/*
Tenta alocar a heap
Em caso de falha, retorna NULL
em caso de sucesso, retorna o ponteiro para ponteiro da heap
*/  
struct paciente **InicHeap(int N, int *tam);

/*essa funcao eh o insere heap para o heapfy*/
void InsereHeap(struct paciente *heap[], int tam, int *comparacoes, int *trocas);

/*insere novo elemento na heap e retorna 1 em caso de sucesso e 0 caso contrario*/
int InsereNovoHeap(struct paciente *heap[], char NovoNome[], int NovaPrioridade, int *tam, int N);

/*
remove um elemento da heap
retorna o ponteiro para o paciente removido, em caso do vetor estar vazio, retorna NULL
*/
struct paciente *RemoveHeap(struct paciente *heap[], int *tam);

/*transforma o vetor em uma heap*/
void Heapfy(struct paciente *heap[], int tam, int *comparacoes, int *trocas);

/*retorna 0 se o vetor nao for heap e 1 em caso contrario*/
int ChecaHeap(struct paciente *heap[], int tam);

/*imprime os elementos da heap*/
int ImprimeHeap(struct paciente *heap[], int tam);

/*ordena a heap utilizando o Heap Sort*/
void HeapSort(struct paciente *heap[], int tam, int *comparacoes, int *trocas);

/*
altera a prioridade do paciente indicado pelo parametro nome[]. 
Retorna 1 em caso de sucesso e 0 caso contrário
*/
int AlteraHeap(struct paciente *heap[], char nome[], int prioridade, int tam);

#endif