#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "email.hpp"
#include "caixaEntrada.hpp"
#include "servidor.hpp"
#include "msgassert.h"
#include "memlog.h"
#include <cstring>
#include <getopt.h>

using namespace std;

int main(int argc, char* argv[]){
    //implementação segue o padrão de LISTA ENCADEADA

    //abrir arquivo
    ifstream file;
    file.open(argv[1], ios::in);

    //criar servidor
    Servidor servidor;

    //verificar arquivo
    if(file.is_open()){
        string linha;
        string comando;
        int id;

        //passar por todas as linhas/funções
        while (getline(file, linha)) {
            stringstream linha_ss(linha);
            linha_ss >> comando >> id;

            if(comando == "CADASTRA"){
                servidor.cadastraId(id);
            }
            else if(comando == "REMOVE"){
                servidor.removeId(id);
            }
            else if(comando == "CONSULTA"){
                servidor.consultaId(id);
            }
            else if(comando == "ENTREGA"){
                int prior;
                string msg;
                string msg_total;
                linha_ss >> prior;
                while(1){
                    linha_ss >> msg;
                    if(msg == "FIM"){
                        break;
                    }
                    msg_total = msg_total + msg + " ";
                }
                servidor.entrega(id,prior,msg_total);
            }
            else{
                erroAssert(1,"Comando não existente");
            }
        }

        file.close();
    }
    else{
        erroAssert(0,"Arquivo não existe ou não pode ser aberto");
        return 0;
    }
    return 0;
}