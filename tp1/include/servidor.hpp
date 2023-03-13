#ifndef SERVIDOR_HPP
#define SERVIDOR_HPP

#include <iostream>
#include <string>

#include "email.hpp"
#include "caixaEntrada.hpp"
#include "memlog.h"
#include "msgassert.h"

using namespace std;

class Servidor{
    private:
        CaixaEntrada* _primeiro;
        CaixaEntrada* _ultimo;

    public:
        Servidor();
        ~Servidor();

        //cadastra nova caixa caso id nn esteja em uso
        void cadastraId(int id); 
        //remove caixa caso id exista
        void removeId(int id);
        //caso id exista, adiciona nova mensagem na caixa de id informado
        //dentro de caixa as mensagens são ordenados por prioridade
        void entrega(int id, int prioridade, string msg);
        //caso id exista, e se não estiver vazio, informa a primeira mensagem da caixa
        //em seguida apaga a mensagem
        void consultaId(int id);
};

#endif