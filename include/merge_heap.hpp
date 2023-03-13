#ifndef MERGE_HEAP
#define MERGE_HEAP

#include <string>
#include <iostream>
//struct registro
#include "registro.hpp"
//copias de registro e tempo
#include "memlog.h"

using namespace std;

//MERGE
//divide, ordena, junta
void mergeSort(registro *Vet, int esq, int dir, int *comp, int *copias);
void merge(registro *Vet, int esq, int meio, int dir, int *comp, int *copias);

//HEAP
//principio da ordenação de selecao
//fila de prioridade -> Heap(arvore binaria)
void heapSort(registro *Vet, int N, int *comp, int *copias);
void checarFilhosHeap(int i, int N, registro *Vet, int *comp, int *copias);

#endif