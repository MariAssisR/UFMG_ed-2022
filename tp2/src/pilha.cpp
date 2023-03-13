#include "pilha.hpp"

MinhaPilha::~MinhaPilha(){
    while(!this->vazia())
        this->desempilha();
}
void MinhaPilha::empilha(Intervalo a){
    ItemPilha *novo;

    novo = new ItemPilha;
    novo->atual = a;
    novo->prox = topo;
    topo = novo;
    tam++;
}
void MinhaPilha::desempilha(){
    ItemPilha *aux;
    if(tam > 0){
        aux = topo;
        topo = topo->prox;
        delete aux;
        tam--;
    }
}
Intervalo MinhaPilha::intervTopo(){
    return topo->atual;
}
int MinhaPilha::vazia(){
    return tam==0;
} 
