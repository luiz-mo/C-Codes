void heapfy(int heap[], int n){
    int i;
    
    for(i = 2; i <= n; i++){
        insereHeap(heap, i);
    }
}

void insereHeap(int heap[], int n){
    int i = n;
    int aux;
    
    while(i > 1 && heap[i] > heap[i/2]){
        aux = heap[i];
        heap[i] = heap[i/2];
        heap[i/2] = aux;
        i = i/2;
    }
}

void removeHeap(int heap[], int n){

}

int checaHeap(int heap[], int n){
    int i;

    for(i=n;i > 1;i--){
        if(heap[i] > heap[i/2])
            return 0;
    }
    return 1;
}

void sacodeHeap(int heap[], int n){

}