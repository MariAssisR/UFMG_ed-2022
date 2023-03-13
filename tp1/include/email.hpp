#ifndef EMAIL_HPP
#define EMAIL_HPP

#include <iostream>
#include <string>

#include "memlog.h"

using namespace std;

class Email{
    private:
        int _prioridade;
        string _mensagens;
        Email *_prox_email;

    friend class CaixaEntrada;

    public:
        Email(){};
        Email(int prior, string msg){ _prioridade = prior; _mensagens = msg;};
        ~Email(){};

        string getEmail();
        int getPrior();
};

#endif
