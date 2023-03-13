#include "significados.hpp"

ListSignificados::ListSignificados(){
    primeiro = nullptr;
    tam = 0;
}

ListSignificados::~ListSignificados(){
    significados *aux;
    while(primeiro != nullptr){
        aux = primeiro;
        primeiro = primeiro->prox;
        delete[] aux;
    }
}

void ListSignificados::insereSignificado(string str){
    if(str.empty())
        return;
    significados *novo = new significados[1];
    novo->texto = str;
    if(tam == 0){
        primeiro = novo;
        tam++;
        return;
    }
    significados *aux = primeiro;
    while(aux->prox != nullptr){
        aux = aux->prox;
    }
    aux->prox = novo;
    tam++;
}

void ListSignificados::imprimirSignificadosParaDic(ostream &f_out){
    significados *aux = primeiro;
    for(int i=1; i <= tam; i++){
        f_out << i << ". " << aux->texto << endl;
        aux = aux->prox;
    }
}