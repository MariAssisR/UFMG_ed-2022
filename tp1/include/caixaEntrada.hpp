#ifndef CAIXA_HPP
#define CAIXA_HPP

#include <iostream>
#include <string>

#include "email.hpp"
#include "memlog.h"
#include "msgassert.h"

using namespace std;

class CaixaEntrada{
    private:
        int _id_caixa;
        CaixaEntrada *_prox_caixa;

        Email* _primeiro;
        Email* _ultimo;

    friend class Servidor;

    public:
        CaixaEntrada(){};
        CaixaEntrada(int id);
        ~CaixaEntrada(){};

        //adiciona na lista de forma ordenada(descrescente)
        void adicionarEmail(int prioridade, string mensagem);
        //le o primeiro item da lista(maior) em seguida apaga
        string consultarEmail();

};

#endif