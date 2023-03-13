#include "quick.hpp"

//fazer a pilha no proprio codigo
//ORDENAR
void quickEmpilha(registro *Vet, int N, int *comp, int *copias){
    //inicializar vazia
    MinhaPilha pilha;
    Intervalo interv;
    int esq=0, dir=N-1, i, j;

    //empilhar os intervalos que precisam ser ordenados
    interv.esq = esq;
    interv.dir = dir;
    pilha.empilha(interv);

    do{
        //intervalo ainda tem elementos pra ordenar
        if(dir > esq){
            Particao(esq, dir, &i, &j, Vet, comp, copias);
            //empilhar MAIOR LADO
            if((j-esq)>(dir-i)){
                interv.dir = j;
                interv.esq = esq;
                pilha.empilha(interv);
                esq = i;
            }
            else{
                interv.esq = i;
                interv.dir = dir;
                pilha.empilha(interv);
                dir = j;
            }
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
