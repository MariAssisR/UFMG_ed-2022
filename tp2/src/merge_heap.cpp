#include "merge_heap.hpp"

//MERGE
//divide
void mergeSort(registro *Vet, int esq, int dir, int *comp, int *copias){
    if (esq < dir){
        int meio = esq+(dir-esq)/2;
        mergeSort(Vet, esq, meio, comp, copias); //lado esquerda
        mergeSort(Vet, meio+1, dir, comp, copias); //lado direito
        merge(Vet, esq, meio, dir, comp, copias);
    }
}

//combinando subvetores
void merge(registro *Vet, int esq, int meio, int dir, int *comp, int *copias){
    //quantidade de elementos em cada lado
    int N_esq = meio-esq+1;
    int N_dir = dir-meio;
    //criar vetor temporario com esquerda e direita
    registro *vet_esq = new registro[N_esq];
    registro *vet_dir = new registro[N_dir];
    //indice novos vetores, e resultante
    int indx_e=0, indx_d=0, indx_r=esq;

    //passar valores do original para temporarios
    for (int i = 0; i < N_esq; i++){
        (*copias)++;
        vet_esq[i] = Vet[esq + i];
        leMemLog((long int)(&(Vet[esq+i])),sizeof(registro),0);
        escreveMemLog((long int)(&(vet_esq[i])),sizeof(registro),0);
    }
    for (int i = 0; i < N_dir; i++){
        (*copias)++;
        vet_dir[i] = Vet[meio+1 + i];
        leMemLog((long int)(&(Vet[meio+1+i])),sizeof(registro),0);
        escreveMemLog((long int)(&(vet_dir[i])),sizeof(registro),0);
    }

    //juntando
    //os dois lados tem elementos
    while(indx_e < N_esq && indx_d < N_dir){
        //comparar os primeiros elementos dos dois lados
        //oque for menor, adicionar no vetor
        (*comp)++;
        if(vet_esq[indx_e].chave <= vet_dir[indx_d].chave){
            leMemLog((long int)(&(vet_esq[indx_e])),sizeof(registro),0);
            leMemLog((long int)(&(Vet[indx_r])),sizeof(registro),0);
            Vet[indx_r] = vet_esq[indx_e];
            indx_e++;
        }
        else{
            leMemLog((long int)(&(vet_dir[indx_d])),sizeof(registro),0);
            leMemLog((long int)(&(Vet[indx_r])),sizeof(registro),0);
            Vet[indx_r] = vet_dir[indx_d];
            indx_d++;
        }
        indx_r++;
        (*copias)++;
    }

    //se somente um dos lados existir elementos
    //copiar elementos restantes
    while(indx_e < N_esq){
        leMemLog((long int)(&(vet_esq[indx_e])),sizeof(registro),0);
        leMemLog((long int)(&(Vet[indx_r])),sizeof(registro),0);
        Vet[indx_r] = vet_esq[indx_e];
        indx_e++;
        indx_r++;
        (*copias)++;
    }
    while(indx_d < N_dir){
        leMemLog((long int)(&(vet_dir[indx_d])),sizeof(registro),0);
        leMemLog((long int)(&(Vet[indx_r])),sizeof(registro),0);
        Vet[indx_r] = vet_dir[indx_d];
        indx_d++;
        indx_r++;
        (*copias)++;
    }

    //apagar temporarios
    delete[] vet_esq;
    delete[] vet_dir;
}


//HEAP
void heapSort(registro *Vet, int N, int *comp, int *copias){
    //heap é uma arvore binaria vetorial
    //pai tem q ser maior q filhos 
    //ordem: constroi heap, maior pro final, constroi heap...

    //construir heap
    for(int i = N/2 -1; i >= 0; i--)
        checarFilhosHeap( i, N, Vet, comp, copias);
    //achar maior elemento do heap, um a um
    for(int i = N-1; i >= 0; i--){
        //trocar primeiro(maior) e ultimo
        (*copias)++;
        registro aux = Vet[0];
        Vet[0] = Vet[i];
        Vet[i] = aux;
        leMemLog((long int)(&(Vet[0])),sizeof(registro),0);
        leMemLog((long int)(&(Vet[i])),sizeof(registro),0);

        //achar maior elemento do reduzido
        checarFilhosHeap(0, i, Vet, comp, copias);

    }
    
}
void checarFilhosHeap(int i, int N, registro *Vet, int *comp, int *copias){
    int esq = 2*i +1;
    int dir = 2*i +2;
    int raiz_pos = i;
    registro w;

    //check filho esq for maior que pai
    (*comp)++;
    if(esq < N && Vet[esq].chave > Vet[raiz_pos].chave){
        leMemLog((long int)(&(Vet[esq])),sizeof(registro),0);
        leMemLog((long int)(&(Vet[raiz_pos])),sizeof(registro),0);
        raiz_pos = esq;
    }

    //check filho dir for maior que pai
    (*comp)++;
    if(dir < N && Vet[dir].chave > Vet[raiz_pos].chave){
        leMemLog((long int)(&(Vet[dir])),sizeof(registro),0);
        leMemLog((long int)(&(Vet[raiz_pos])),sizeof(registro),0);
        raiz_pos = dir;
    }

    //se o maior não for raiz 
    if(raiz_pos != i){
        //trocar
        (*copias)++;
        w = Vet[i];
        Vet[i] = Vet[raiz_pos];
        Vet[raiz_pos] = w;
        leMemLog((long int)(&(Vet[i])),sizeof(registro),0);
        leMemLog((long int)(&(Vet[raiz_pos])),sizeof(registro),0);

        //ir recursivamente checando filhos
        checarFilhosHeap(raiz_pos, N, Vet, comp, copias);
    }
}