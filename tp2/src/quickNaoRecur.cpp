#include "quick.hpp"

//fazer a pilha no proprio codigo
//ORDENAR
void quickNaoRecursivo(registro *Vet, int N, int *comp, int *copias){
    //inicializar vazia
    MinhaPilha pilha;
    Intervalo interv;
    int esq=0, dir=N-1, i, j;

    //empilhar os intervalos que precisam ser ordenados
    interv.esq = esq;
    interv.dir = dir;
    pilha.empilha(interv);
    //pode ser trocado por empilhar inicio e em seguida empilhar final

    do{
        //intervalo ainda tem elementos
        if(dir > esq){
            Particao(esq, dir, &i, &j, Vet, comp, copias);
            //empilhar OS DOIS LADOS
            interv.dir = j;
            interv.esq = esq;
            pilha.empilha(interv);
            
            interv.esq = i;
            interv.dir = dir;
            pilha.empilha(interv);

            esq = i;
            dir = j;
        }
        //apos ordenado, passar pro prox intervalo 
        else{
            //pegar o intervalo mais recente
            interv = pilha.intervTopo();
            pilha.desempilha();
            dir = interv.dir;
            esq = interv.esq;
        }

    }while(!pilha.vazia());
}