#include "caixaEntrada.hpp"


CaixaEntrada::CaixaEntrada(int id){
    _id_caixa = id;
    _primeiro = _ultimo = nullptr;
}

void CaixaEntrada::adicionarEmail(int prioridade, string mensagem){

    Email *novo = new Email(prioridade,mensagem);
    escreveMemLog((long int)(&(*novo)),sizeof(Email),2);
        
    if(_primeiro == nullptr){
        _primeiro = novo;
        _primeiro->_prox_email = nullptr;
        _ultimo = _primeiro;
    }
    else if(prioridade > _primeiro->getPrior()){
        novo->_prox_email = _primeiro;
        _primeiro = novo;
    }
    else{
        Email *p = _primeiro->_prox_email;//começa no 2
        Email *aux = _primeiro;

        while(p != nullptr){
            leMemLog((long int)(&(*p)),sizeof(Email),2);
            if(prioridade > p->getPrior()){
                novo->_prox_email = p;
                aux->_prox_email = novo;
                return;
            }
            p = p->_prox_email;
            aux = aux->_prox_email;
        }
        _ultimo->_prox_email = novo;
        novo->_prox_email = nullptr;
        _ultimo = novo;
    }
}

string CaixaEntrada::consultarEmail(){
    string aux = _primeiro->getEmail();

    //apagar email da frente
    Email *apagar = _primeiro;
    leMemLog((long int)(&(*apagar)),sizeof(Email),3);
    _primeiro = _primeiro->_prox_email;
    delete apagar;

    return aux;
}