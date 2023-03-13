#ifndef PILHA_HPP
#define PILHA_HPP

#include <string>
#include <iostream>
using namespace std;

//PILHA das não recursivas
//intervalos a serem ordenados na pilha
struct Intervalo{
    int esq;
    int dir;
};
//pilha de ItemPilha
struct ItemPilha{
    Intervalo atual;
    ItemPilha *prox;
};
class MinhaPilha{
    private:
        int tam=0;
        ItemPilha *topo;
    public:
        MinhaPilha(){topo = nullptr;};
        ~MinhaPilha();
        void empilha(Intervalo a);
        void desempilha();
        Intervalo intervTopo();
        int vazia();
};

#endif