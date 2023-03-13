#ifndef QUICK_HPP
#define QUICK_HPP

#include <string>
#include <iostream>
#include "pilha.hpp"
//struct registro
#include "registro.hpp"
//copias de registro e tempo
#include "memlog.h"

using namespace std;

//QUICKSORTS
void quickRecursivo(registro *Vet, int N, int *comp, int *copias);//1
void quickMediana(registro *Vet, int N, int k, int *comp, int *copias);//2
void quickSelecao(registro *Vet, int N, int m, int *comp, int *copias);//3
void quickNaoRecursivo(registro *Vet, int N, int *comp, int *copias);//4
void quickEmpilha(registro *Vet, int N, int *comp, int *copias);//5

//selecao
void selectionSort(registro *arr, int esq, int dir, int *comp, int *copias);

//esta no quickRec.cpp
void Particao(int esq, int dir, int *i, int *j, registro *arr, int *comp, int *copias);
void Ordena(int esq, int dir, registro *arr, int *comp, int *copias);

#endif