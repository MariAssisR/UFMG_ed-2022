#include "servidor.hpp"
//memlog
//id 0 : cadastra
//id 1 : remove
//id 2 : entrega
//id 3 : consulta

Servidor::Servidor(){
    //inicializa vazio
    _ultimo = _primeiro = nullptr;
}

Servidor::~Servidor(){
    CaixaEntrada *p;
    
    while(_primeiro != nullptr){
        p = _primeiro;
        _primeiro = _primeiro->_prox_caixa;
        delete p;
    }
}

void Servidor::cadastraId(int id){
    erroAssert(id >= 0,"Id invalido");
    CaixaEntrada *p = _primeiro;
    //buscar id
    while(p != nullptr){
        leMemLog((long int)(&(*p)),sizeof(CaixaEntrada),0);
        if(id == p->_id_caixa){
            cout << "ERRO: CONTA "<< id <<" JA EXISTENTE" << endl;
            return;
        }
        p = p->_prox_caixa;
    }

    //caso conta não exista->criar
    //caso nenhuma conta
    if(_primeiro == nullptr){
        _primeiro = new CaixaEntrada(id);
        escreveMemLog((long int)(&(*_primeiro)),sizeof(CaixaEntrada),0);
        _primeiro->_prox_caixa = nullptr;
        _ultimo = _primeiro;
    }
    //caso pelo menos uma conta no servidor
    else{
        CaixaEntrada *aux = new CaixaEntrada(id);
        escreveMemLog((long int)(&(*aux)),sizeof(CaixaEntrada),0);
        aux->_prox_caixa = _primeiro;
        _primeiro = aux;
    }
    cout << "OK: CONTA "<< id <<" CADASTRADA" << endl;
}

void Servidor::removeId(int id){
    erroAssert(id >= 0,"Id invalido");
    CaixaEntrada *p = _primeiro;
    //caso caixa vazia e tentar remover
    if(_primeiro == nullptr){
        cout << "ERRO: CONTA "<< id <<" NAO EXISTE" << endl;
        return;
    }

    //caso a conta de id passado seja a primeira
    if(id == _primeiro->_id_caixa){
        _primeiro = _primeiro->_prox_caixa;
        leMemLog((long int)(&(*p)),sizeof(CaixaEntrada),1);
        delete p;
        cout << "OK: CONTA "<< id << " REMOVIDA"<< endl;return;
        return;
    }

    //caixa com mais de uma conta
    p = p->_prox_caixa;//começa no 2
    CaixaEntrada *aux = _primeiro;

    //buscar a conta com id passado
    while(p != nullptr){

        leMemLog((long int)(&(*p)),sizeof(CaixaEntrada),1);
        if(id == p->_id_caixa){
            aux->_prox_caixa = p->_prox_caixa;
            delete p;

            cout << "OK: CONTA "<< id << " REMOVIDA"<< endl;return;
            return;
        }
        p = p->_prox_caixa;
        aux = aux->_prox_caixa;
    }
    
    cout << "ERRO: CONTA "<< id <<" NAO EXISTE" << endl;
}

void Servidor::entrega(int id, int prioridade, string msg){
    erroAssert(id >= 0,"Id invalido");
    erroAssert(prioridade >= 0 && prioridade < 10,"Prioridade invalida");
    CaixaEntrada *p;
    p = _primeiro;
    
    //buscar pela lista de caixas até o final
    while(p != nullptr){

        leMemLog((long int)(&(*p)),sizeof(CaixaEntrada),2);
        if(id == p->_id_caixa){
            //função responsavel por ordenar os email da caixa de id 
            p->adicionarEmail(prioridade, msg);
            cout << "OK: MENSAGEM PARA "<< id << " ENTREGUE"<< endl;
            return;
        }
        p = p->_prox_caixa;
    }
    
    cout << "ERRO: CONTA "<< id <<" NAO EXISTE" << endl;
}

void Servidor::consultaId(int id){
    erroAssert(id >= 0,"Id invalido");
    CaixaEntrada *p;
    p = _primeiro;
    
    //buscar pela lista de caixas até o final
    while(p != nullptr){
        leMemLog((long int)(&(*p)),sizeof(CaixaEntrada),3);
        if(id == p->_id_caixa){
            if(p->_primeiro == nullptr)
                cout << "CONSULTA "<< id << ": CAIXA DE ENTRADA VAZIA"<< endl;
            else
                cout << "CONSULTA "<< id << ": "<< p->consultarEmail() << endl;
            //função consulta retorna email de  maior prioridade
            return;
        }
        p = p->_prox_caixa;
    }
    cout << "ERRO: CONTA "<< id <<" NAO EXISTE" << endl;
}
