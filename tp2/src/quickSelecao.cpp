#include "quick.hpp"

void selectionSort(registro *arr, int esq, int dir, int *comp, int *copias){
    int i, j, menor_index;
    registro aux;
 
    for (i = esq; i < dir; i++){
        leMemLog((long int)(&(arr[i])),sizeof(registro),0);
        // achar o menor
        menor_index = i;
        for (j = i+1; j <= dir; j++){
            leMemLog((long int)(&(arr[j])),sizeof(registro),0);
            (*comp)++;
            if (arr[j].chave < arr[menor_index].chave){
                menor_index = j;
            }
        }
        //trocar
        if(menor_index!=i){
            (*copias)++;
            aux = arr[i]; arr[i] = arr[menor_index]; arr[menor_index] = aux;
            leMemLog((long int)(&(arr[menor_index])),sizeof(registro),0);
            leMemLog((long int)(&(arr[i])),sizeof(registro),0);
        }
    }
}

void ParticaoSelecao(int esq, int dir, int *i, int *j, registro *arr, int m, int *comp, int *copias){ 
    int pivo;
    registro w;
    *i = esq; *j = dir;
 
    //pega MEIO do vetor
    pivo = arr[(*i + *j)/2].chave;
    
    do{ 
        //achar possiveis trocas
        (*comp)++;
        while (pivo > arr[*i].chave){
            leMemLog((long int)(&(arr[(*i)])),sizeof(registro),0);
            (*i)++;
            (*comp)++;
        } 
        (*comp)++;
        while (pivo < arr[*j].chave){
            leMemLog((long int)(&(arr[(*j)])),sizeof(registro),0);
            (*j)--;
            (*comp)++;
        }

        //checar se não cruzou
        if (*i <= *j){ 
            //trocar
            (*copias)++;
            w = arr[*i]; arr[*i] = arr[*j]; arr[*j] = w;
            leMemLog((long int)(&(arr[(*j)])),sizeof(registro),0);
            leMemLog((long int)(&(arr[(*i)])),sizeof(registro),0);
            (*i)++; (*j)--;
        }
    }while (*i <= *j); //enquanto i não cruzar j
}

void OrdenaSelecao(int esq, int dir, registro *arr, int m, int *comp, int *copias){
    int i, j;
    //dividir em esq e dir
    //ordenar separado
    if((dir-esq+1) <= m){
        selectionSort(arr, esq, dir, comp, copias);
    }
    else{
        ParticaoSelecao(esq, dir, &i, &j, arr, m, comp, copias);
        if (esq < j) OrdenaSelecao(esq, j, arr, m, comp, copias);
        if (i < dir) OrdenaSelecao(i, dir, arr, m, comp, copias);
    }
    
}

void quickSelecao(registro *Vet, int N, int m, int *comp, int *copias){
    OrdenaSelecao(0, N-1, Vet, m, comp, copias);
}