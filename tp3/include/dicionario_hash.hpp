#ifndef HASH_HPP
#define HASH_HPP

#include <string>
#include <iostream>
#include <cstring>
//struct verbete e significado de verbete
#include "verbete.hpp"
//copias de registro e tempo
#include "memlog.h"

using namespace std;

//genralização de array
//usa hash function que serve de index
//lidar com colisões de index: endereçamento aberto
struct no{
    int vazio = 1;
    int retirado = 0;
    Verbete* palavra;
};

//ordenar
void quickRecursivo(no *Vet, int N);

class DicHash{
    private:
        //listas pra diferentes letras
        int _tamMax;
        int _tamVerbetes;
        no* tabela;

        // hash function to map values to key
        int hashFunction(string x) {
            int hash = 0;
            for(int i = 0; i < x.size(); i++){
                hash += x[i]*(i+1);
            }
            hash = hash%_tamMax;
            return hash;
        }

    public:
        //inicializa os buckets
        DicHash(int tam);
        ~DicHash();

        //adiciona novos verbetes aos buckets
        void insereHash(Verbete* it);
        //encontra o bucket correspondente ao key e adiciona verbetes
        //1 se tiver, 0 se não
        int pesquisaHash(Verbete* it);
        //remove os verbetes que tem significado
        void removeHashComSignificados();
        //imprimir verbetes
        void imprimeHash(ostream &f_out);

};



#endif