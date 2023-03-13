#include "dicionario_hash.hpp"

DicHash::DicHash(int tam){
    _tamMax = tam;
    _tamVerbetes = 0;
    tabela = new no[tam];
}
DicHash::~DicHash(){
    delete[] tabela;
}

void DicHash::insereHash(Verbete* it){
    int idx_hash = hashFunction(it->nome);
    int i = 0, j = 0;

    //percorrer tabela atrás de posição vazia ou retirada
    while(j < _tamMax){
        //leMemLog((long int)(&(tabela[idx_hash+i].palavra)),sizeof(Verbete),0);
        if(tabela[idx_hash+i].vazio == 1){
            //escreveMemLog((long int)(&(tabela[idx_hash+i].palavra)),sizeof(Verbete),0);
            tabela[idx_hash+i].palavra = it;
            tabela[idx_hash+i].vazio = 0;
            tabela[idx_hash+i].retirado = 0;
            _tamVerbetes++;
            return;
        }
        else if(tabela[idx_hash+i].retirado == 1){
            //escreveMemLog((long int)(&(tabela[idx_hash+i].palavra)),sizeof(Verbete),0);
            tabela[idx_hash+i].palavra = it;
            tabela[idx_hash+i].vazio = 0;
            tabela[idx_hash+i].retirado = 0;
            _tamVerbetes++;
            return;
        }
        //add palavra existente
        else if(tabela[idx_hash+i].palavra->nome == it->nome){
            //leMemLog((long int)(&(tabela[idx_hash+i].palavra)),sizeof(Verbete),0);
            //palavra existente && tipo existente
            if(tabela[idx_hash+i].palavra->tipo == it->tipo){
                //atualizar somente número de significados
                if(it->significado.tam > 0){
                    string significado_novo = it->significado.primeiro->texto;
                    tabela[idx_hash+i].palavra->significado.insereSignificado(significado_novo);
                } 
                return;
            }
            
        }
        i++;
        j++;
        if(idx_hash+i >= _tamMax){
            i = 0;
            idx_hash = 0;
        }
    }
}

int DicHash::pesquisaHash(Verbete* it){
    int idx_hash = hashFunction(it->nome);
    int i = 0;

    //percorrer tabela atrás de chave
    //caso esteja vazio não tem
    while(i < _tamMax && tabela[idx_hash+i].vazio != 0 && (tabela[idx_hash+i].palavra->nome != it->nome))
        i++;
    
    //achou chave
    if((tabela[idx_hash+i].palavra->nome != it->nome) && tabela[idx_hash+i].retirado != 0)
        return 1;
    return 0;
}
        
void DicHash::removeHashComSignificados(){
    int i = 0;

    //percorrer tabela retirando todos que tenham significado
    while(i < _tamMax){
        if(tabela[i].vazio == 0 && tabela[i].retirado == 0){
            //leMemLog((long int)(&(tabela[i].palavra)),sizeof(Verbete),0);
            //retirar sign
            if(tabela[i].palavra->significado.tam > 0){
                tabela[i].retirado = 1;
                _tamVerbetes--;
            }
        }
        i++;
    }
}

void DicHash::imprimeHash(ostream &f_out){
    int i = 0;

    quickRecursivo(tabela, _tamMax);
    //percorrer tabela imprimindo todos
    while(i < _tamMax){
        if(tabela[i].vazio == 0 && tabela[i].retirado == 0){
            //leMemLog((long int)(&(tabela[i].palavra)),sizeof(Verbete),0);
            //print
            //imprimir verbete
            f_out << tabela[i].palavra->nome.substr(0, tabela[i].palavra->nome.size()-3);
            //tipo
            f_out << " (" << tabela[i].palavra->tipo << ")" << endl;
            //significados
            tabela[i].palavra->significado.imprimirSignificadosParaDic(f_out);
        }
        i++;
    }
}
