#ifndef ALGORITMOS_HPP
#define ALGORITMOS_HPP

#include <functional>

using namespace std;

using AlgoritmoBusca = function<int(const vector<int>&, int)>;
using AlgoritmoOrdenacao = function<void(vector<int>&)>;

//Algoritmos de Busca
int BuscaSequencial(const vector<int>& v, int chave);
int BuscaBinaria(const vector<int>& v, int chave);

//Algoritmos Ordenação
void InsertionSort(vector<int>& v);
void BubbleSort(vector<int>& v);
void MergeSort(vector<int>& v);
void QuickSort(vector<int>& v);

#endif