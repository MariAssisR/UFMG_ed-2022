#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <getopt.h>
//registro tempo
#include <stdio.h>
#include <sys/resource.h>

//TAD verbete+significado
#include "verbete.hpp"
//TAD dicionario
#include "dicionario_arv.hpp"
#include "dicionario_hash.hpp"
//asserts
#include "msgassert.h"
//registro de memoria
#include "memlog.h"

using namespace std;


typedef struct {
  char lognome[100];//-p
  int regmem;//-l
  char arq_in[100]; //-i
  char arq_out[100]; //-o
  char tipo[10]; //-t arv ou hash
}opt_tipo;

// Descricao: le as opcoes da linha de comando e inicializa variaveis
void parse_args(int argc,char ** argv, opt_tipo * opt){
    
    // variavel auxiliar
    extern char * optarg;
    int c;

    // inicializacao variaveis globais para opcoes
    opt->lognome[0] = 0;
    opt->regmem = 0;
    opt->arq_in[0] = 0;
    opt->arq_out[0] = 0;
    opt->tipo[0] = 0;

    // getopt - letra indica a opcao, : junto a letra indica parametro
    // no caso de escolher mais de uma operacao, vale a ultima
    while ((c = getopt(argc, argv, "i:o:t:p:l")) != EOF)
        switch(c) {
        case 'i':
	        strcpy(opt->arq_in,optarg);
            break;
        case 'o':
	        strcpy(opt->arq_out,optarg);
            break;
        case 't':
	        strcpy(opt->tipo,optarg);
            break;     
        case 'p': 
	        strcpy(opt->lognome,optarg);
		    break;
        case 'l': 
	        opt->regmem = 1;
		    break;

       }
}

string removeSpaces(string word) {
    string newWord;
    for (long unsigned int i = 0; i < word.length(); i++) {
        if (word[i] != ' ') {
            newWord += word[i];
        }
    }
    return newWord;
}

int main(int argc, char* argv[]){
    //ler linha de comando
    opt_tipo opt;
    parse_args(argc,argv,&opt);

    /*
    //flag -p necessaria
    // iniciar registro de acesso
    iniciaMemLog(opt.lognome);
    //registro de memoria
    if (opt.regmem){ 
        ativaMemLog();
    }
    else{
        desativaMemLog();
    }
    */

    //abrir arquivos
    ofstream f_out;
    ifstream file;
    ifstream file_contar_linhas;

    //arquivo para contar linhas para tabela hash
    file_contar_linhas.open(opt.arq_in, ios::in);
    int num_linhas = 0;
    //verificar arquivo
    if(file_contar_linhas.is_open()){
        string linha;
        while(getline(file_contar_linhas, linha))
            num_linhas++;
    }
    file_contar_linhas.close();

    //arquivo para programa
    file.open(opt.arq_in, ios::in);
    f_out.open(opt.arq_out, ios::out);
    //verificar arquivo
    if(file.is_open()){
        //iniciar registro tempo
        struct rusage resources;
        int rc;
        double utime, stime, total_time;

        //criar dic
        DicArvore arv;
        DicHash hash(num_linhas);

        string linha;
        while(getline(file, linha)){
            //criar verbete
            Verbete *a = new Verbete();

            //passar infos do arq para o verbete
            //tipo
            a->tipo = linha.front();
            //nome
            unsigned first = linha.find("[");
            unsigned last = linha.find("]");
            a->nome = linha.substr(first+1,last-first-1);
            //a->nome = removeSpaces(a->nome);
            //pegar os significados
            first = linha.find("]");
            last = linha.size()-1;
            if(first != last)
                a->significado.insereSignificado(linha.substr(first+2, last-first));

            //add verbete no dic/hash
            if(!strcmp(opt.tipo,"arv"))
                arv.insereDic(a);
            else{
                a->nome += "  ";
                a->nome += a->tipo;
                hash.insereHash(a);
            }
        }
        if(!strcmp(opt.tipo,"arv")){
            arv.imprimeDic(f_out);
            arv.removeDic();
            arv.imprimeDic(f_out);
        }
        else{
            hash.imprimeHash(f_out);
            hash.removeHashComSignificados();
            hash.imprimeHash(f_out);
        }

        if((rc = getrusage(RUSAGE_SELF, &resources)) != 0)
            perror("getrusage failed");
        utime = (double) resources.ru_utime.tv_sec + 1.e-6 * (double) resources.ru_utime.tv_usec;
        stime = (double) resources.ru_stime.tv_sec + 1.e-6 * (double) resources.ru_stime.tv_usec;
        total_time = utime+stime;
        //printf("User time %.3f, System time %.3f, Total Time %.3f\n", utime, stime, total_time);

        //f_out << total_time << endl;

        f_out.close();
        file.close();
    }
    else{
        erroAssert(0,"Arquivo não existe ou não pode ser aberto");
    }

    //finalizaMemLog();
    return 0;
}