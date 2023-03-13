#include "dicionario_hash.hpp"
//CODIGO PARA ORDENAR INT

void Particao(int esq, int dir, int *i, int *j, no *arr){ 
    string pivo;
    no w;
    *i = esq; *j = dir;
 
    if(arr[(*i + *j)/2].palavra == nullptr){
        Verbete *aux = new Verbete();
        aux->nome = "zzzz";
        arr[(*i + *j)/2].palavra = aux;
    }
    pivo = arr[(*i + *j)/2].palavra->nome;
    
    do{ 
        if(arr[*i].palavra == nullptr){
            Verbete *aux = new Verbete();
            aux->nome = "zzzz";
            arr[*i].palavra = aux;
        }
        while(strcmp(pivo.c_str(),arr[*i].palavra->nome.c_str())>0){
            (*i)++;
            if(arr[*i].palavra == nullptr){
                Verbete *aux = new Verbete();
                aux->nome = "zzzz";
                arr[*i].palavra = aux;
            }
        } 
        
        if(arr[*j].palavra == nullptr){
            Verbete *aux = new Verbete();
            aux->nome = "zzzz";
            arr[*j].palavra = aux;
        }
        while(strcmp(pivo.c_str(),arr[*j].palavra->nome.c_str())<0){
            (*j)--;
            if(arr[*j].palavra == nullptr){
                Verbete *aux = new Verbete();
                aux->nome = "zzzz";
                arr[*j].palavra = aux;
            }
        }

        if (*i <= *j){ 
            w = arr[*i]; arr[*i] = arr[*j]; arr[*j] = w;
            (*i)++; (*j)--;
        }
    }while (*i <= *j); //enquanto i não cruzar j
}

void Ordena(int esq, int dir, no *arr){
    int i, j;
    Particao(esq, dir, &i, &j, arr);
    if (esq < j) Ordena(esq, j, arr);
    if (i < dir) Ordena(i, dir, arr);
}

void quickRecursivo(no *Vet, int N){
    Ordena(0, N-1, Vet); 
}