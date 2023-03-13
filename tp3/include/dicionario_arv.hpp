#ifndef ARV_HPP
#define ARV_HPP

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#include <string>
#include <iostream>
//comp strings
#include <string.h>
//struct verbete e significado de verbete
#include "verbete.hpp"
//copias de registro e tempo
#include "memlog.h"

using namespace std;

struct item{
    Verbete* _verbete;
    item* esq = nullptr;
    item* dir = nullptr;
    int altura = 1;
};

// arvore AVL, balanceamento -1<=0<=1
class DicArvore{
    private:
        item *_raiz;
        int _num; //num de verbetes
        //conta quantos precisam ser removidos, usado na hr de debbugar
        int _numVerbetesComSig;

        //pegar a altura
        int getAltura(item* no);
        //valor do balanceamento
        int balanceamento(item* no);
        //balancear
        item* balancear(item* no);
        item* rotacaoEsq(item* pai);
        item* rotacaoDir(item* pai);

        //sequencia de metodos chamada a partir dos metodos publicos
        //está privado porque são chamados com a raiz
        //insere balanceado
        item* insereDicRec(item* no,Verbete* it);
        //pesquisa *NAO USADA
        item* pesquisaDicRec(item* no,Verbete* it);
        //imprime
        void imprimeDicRec(item* no, ostream &f_out);
        //remoção sem balancear 
        void removeDicRec(item* &no);
        void antecessor(item *no, item* &no_prox);
        
        
        //apagar dicionario completo
        //usado no destrutor
        void destroiDic(item* &no);

    public:
        DicArvore();
        ~DicArvore();

        //inserir um novo verbete 
        void insereDic(Verbete* it);
        //buscar verbete especifico  *NAO USADA
        int pesquisaDic(Verbete* it);
        //imprimir verbetes
        void imprimeDic(ostream &f_out);
        //remove verbetes com significado
        void removeDic();
};

#endif