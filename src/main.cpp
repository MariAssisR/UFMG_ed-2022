#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <getopt.h>
//gerador de vetor aleatorio a partir de semente
#include <stdlib.h>
//registro tempo
#include <stdio.h>
#include <sys/resource.h>

//algoritmos de quick separados
#include "quick.hpp"
#include "merge_heap.hpp"
//struct registro
#include "registro.hpp"
//asserts
#include "msgassert.h"
//registro de memoria
#include "memlog.h"

using namespace std;


typedef struct {
  char lognome[100];
  int regmem;
  char arq_in[100]; //-i
  char arq_out[100]; //-o
  int versao_quick; //-v
  int semente; //-s
  int aux_m; //-m
  int aux_k; //-k
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
    opt->versao_quick = 0;
    opt->semente = 0;
    opt->aux_m = 0;
    opt->aux_k = 0;

    // getopt - letra indica a opcao, : junto a letra indica parametro
    // no caso de escolher mais de uma operacao, vale a ultima
    while ((c = getopt(argc, argv, "i:o:v:s:m:k:p:l")) != EOF)
        switch(c) {
        case 'i':
	        strcpy(opt->arq_in,optarg);
            break;
        case 'o':
	        strcpy(opt->arq_out,optarg);
            break;
        case 'v': 
	        opt->versao_quick = atoi(optarg);
		    break; 
        case 's': 
	        opt->semente = atoi(optarg);
		    break; 
        case 'm': 
	        opt->aux_m = atoi(optarg);
		    break; 
        case 'k': 
	        opt->aux_k = atoi(optarg);
		    break;        
        case 'p': 
	        strcpy(opt->lognome,optarg);
		    break;
        case 'l': 
	        opt->regmem = 1;
		    break;

       }
}

int main(int argc, char* argv[]){
    //ler linha de comando
    opt_tipo opt;
    parse_args(argc,argv,&opt);

    /*
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

    //abrir arquivo
    ifstream file;
    ofstream f_out;
    file.open(opt.arq_in, ios::in);
    f_out.open(opt.arq_out);
    //arq de saida infos
    f_out << "N \tcomparações\tcópias\ttempo" << endl;

    //verificar arquivo
    if(file.is_open()){
        //pegar os diferentes valores de entrada(N)
        string linha;
        getline(file, linha);
        int N = stoi(linha);//primeira linha arquivo
        if(N < 0)
            erroAssert(0,"Número de elementos para ordenação inválido");

        while(getline(file, linha)){
            N = stoi(linha);

            //gerar N registros 
            registro *vetor_alet = new registro[N];    
            srand(opt.semente);

            //chave && reais
            for(int i = 0; i < N; i++){
                //gerar chaves aleatorias com semente -s para os N registros 
                vetor_alet[i].chave = rand();
                escreveMemLog((long int)(&(vetor_alet[i])),sizeof(registro),0);
            }

            //numero de comparações de chaves
            int comparacao = 0;
            //numero de copias
            int copias = 0;

            //iniciar registro tempo
            struct rusage resources;
            int rc;
            double utime, stime, total_time;

            //qual versao de quick rodar
            //Quicksort Recursivo
            if(opt.versao_quick == 1) 
                quickRecursivo(vetor_alet, N, &comparacao, &copias);
            //Quicksort Mediana (k)
            else if(opt.versao_quick == 2) 
                quickMediana(vetor_alet, N, opt.aux_k, &comparacao, &copias);
            //Quicksort Seleção (m)
            else if(opt.versao_quick == 3) 
                quickSelecao(vetor_alet, N, opt.aux_m, &comparacao, &copias);
            //Quicksort não Recursivo
            else if(opt.versao_quick == 4) 
                quickNaoRecursivo(vetor_alet, N, &comparacao, &copias);
            //Quicksort Empilha Inteligente
            else if(opt.versao_quick == 5) 
                quickEmpilha(vetor_alet, N, &comparacao, &copias);
            
            //Merge
            else if(opt.versao_quick == 6) 
                mergeSort(vetor_alet, 0, N-1, &comparacao, &copias);
            //Heap
            else if(opt.versao_quick == 7) 
                heapSort(vetor_alet, N, &comparacao, &copias);


            if((rc = getrusage(RUSAGE_SELF, &resources)) != 0)
                perror("getrusage failed");
            utime = (double) resources.ru_utime.tv_sec + 1.e-6 * (double) resources.ru_utime.tv_usec;
            stime = (double) resources.ru_stime.tv_sec + 1.e-6 * (double) resources.ru_stime.tv_usec;
            total_time = utime+stime;
            //printf("User time %.3f, System time %.3f, Total Time %.3f\n", utime, stime, total_time);

            f_out << N << '\t' << comparacao << "  " << copias << "  " << total_time << endl;
            delete[] vetor_alet;
            
        }
        
        file.close();
        f_out.close();

    }
    else{
        erroAssert(0,"Arquivo não existe ou não pode ser aberto");
    }

    //finalizaMemLog();
    return 0;
}