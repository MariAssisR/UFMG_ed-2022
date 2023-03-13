#include "quick.hpp"

int acharMediana(registro *arr, int esq, int dir, int k, int *comp, int *copias){
    //pegar k elementos aleatorios de arr
    //não precisa de ser um registro já que está somente retornando a mediana
    //ta como registro para reutilizar a função
    registro *vetor = new registro[k];
    for(int i = 0; i < k; i++){
        //leMemLog((long int)(&(vetor[i])),sizeof(registro),0);
        vetor[i].chave = arr[esq+rand()%(dir-esq+1)].chave;
    }

    //ordenar os k elementos
    quickRecursivo(vetor, k, comp, copias);

    int retorno = vetor[k/2].chave;
    
    delete [] vetor;
    //retornar mediana
    return retorno;

}

void ParticaoMediana(int esq, int dir, int *i, int *j, registro *arr, int k, int *comp, int *copias){ 
    registro w;
    *i = esq; *j = dir;
    
    //pega MEDIANA
    int pivo = acharMediana(arr, esq, dir, k, comp, copias);
    
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

void OrdenaMediana(int esq, int dir, registro *arr, int k, int *comp, int *copias){
    int i, j;
    //dividir em esq e dir
    //ordenar separado
    ParticaoMediana(esq, dir, &i, &j, arr, k, comp, copias);
    if (esq < j) OrdenaMediana(esq, j, arr, k, comp, copias);
    if (i < dir) OrdenaMediana(i, dir, arr, k, comp, copias);
}

void quickMediana(registro *Vet, int N, int k, int *comp, int *copias){
    OrdenaMediana(0, N-1, Vet, k, comp, copias); 
}