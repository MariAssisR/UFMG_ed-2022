#ifndef SIGNIFICADOS_HPP
#define SIGNIFICADOS_HPP

#include <string>
#include <iostream>

using namespace std;

struct significados{
    string texto;
    significados* prox=nullptr;
};
class ListSignificados{
    private:    
    public:
        significados* primeiro;
        int tam;
        ListSignificados();
        ~ListSignificados();

        void insereSignificado(string aux);
        void imprimirSignificadosParaDic(ostream &f_out);
};

#endif