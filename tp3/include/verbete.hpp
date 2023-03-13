#ifndef VERBETE_HPP
#define VERBETE_HPP

#include <string>
#include <iostream>
//copias de registro e tempo
#include "memlog.h"
//significados
#include "significados.hpp"

using namespace std;

class Verbete{
    private: 
    public:
        Verbete(){};
        ~Verbete(){};
        char tipo; //adj, verbo, subs
        //nome é a chave
        string nome; //verbete em si
        ListSignificados significado; //lista de significados
};

#endif