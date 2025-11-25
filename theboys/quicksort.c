int escolhePivo(int v[], int ini, int fim){
    int meio = (ini+fim)/2, aux;

    if(v[ini] > v[meio]){
        aux = v[ini];
        v[ini] = v[meio];
        v[meio] = aux;
    }

    if(v[meio] > v[fim]){
        aux = v[meio];
        v[meio] = v[fim];
        v[fim] = aux;

        if(v[ini] > v[meio]){
            aux = v[ini];
            v[ini] = v[meio];
            v[meio] = aux;
        }
    }

    return meio;
}

void Particao(int v[], int ini, int fim, int *pos_pivo){
    int i = ini +1, j = fim, pivo, aux;
    *pos_pivo = escolhePivo(v,ini,fim);
    pivo = v[*pos_pivo];

    /*coloca o pivo no inicio*/
    aux = v[ini];
    v[ini] = v[*pos_pivo];
    v[*pos_pivo] = aux;

    while(i<j){
        while(i<fim && v[i] <= pivo)
            i++;
        while(j>ini && v[j]> pivo)
            j--;
        if(i<j){
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
        }
    }
    v[ini] = v[j];
    v[j] = pivo;
    *pos_pivo = j;
}

void QuickSort(int v[], int ini, int fim){
    int pos_pivo;
    if(ini<fim){
        Particao(v,ini,fim,&pos_pivo);
        QuickSort(v,ini,pos_pivo - 1);
        QuickSort(v, pos_pivo+1, fim);
    }
}