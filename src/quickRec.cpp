#include "quick.hpp"
//CODIGO PARA ORDENAR INT

void Particao(int esq, int dir, int *i, int *j, registro *arr, int *comp, int *copias){ 
    int pivo;
    registro w;
    *i = esq; *j = dir;
 
    //pega MEIO do vetor
    pivo = arr[(*i + *j)/2].chave;
    
    do{ 
        //achar possiveis trocas
        (*comp)++;
        while(pivo > arr[*i].chave){
            leMemLog((long int)(&(arr[(*i)])),sizeof(registro),0);
            (*i)++;
            (*comp)++;
        } 
        
        (*comp)++;
        while(pivo < arr[*j].chave){
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

void Ordena(int esq, int dir, registro *arr, int *comp, int *copias){
    int i, j;
    //dividir em esq e dir
    //ordenar separado
    Particao(esq, dir, &i, &j, arr, comp, copias);
    if (esq < j) Ordena(esq, j, arr, comp, copias);
    if (i < dir) Ordena(i, dir, arr, comp, copias);
}

void quickRecursivo(registro *Vet, int N, int *comp, int *copias){
    Ordena(0, N-1, Vet, comp, copias); 
}