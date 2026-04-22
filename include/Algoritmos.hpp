/**
 * \file Algoritmos.hpp
 * \brief Declarações dos algoritmos de busca e ordenação implementados no projeto.
 * \author Matheus Miguel
 * \date 2026
 */

#ifndef ALGORITMOS_HPP
#define ALGORITMOS_HPP

#include <functional>

using namespace std;

/**
 * \brief Alias para funções de busca que recebem um vetor e uma chave e retornam o índice.
 */
using AlgoritmoBusca = function<int(const vector<int>&, int)>;

/**
 * \brief Alias para funções de ordenação que recebem um vetor por referência e o ordenam.
 */
using AlgoritmoOrdenacao = function<void(vector<int>&)>;

//Algoritmos de Busca

/**
 * \brief Realiza busca sequencial em um vetor.
 * \param v O vetor onde a busca será realizada.
 * \param chave O valor a ser procurado.
 * \return O índice da chave se encontrada, -1 caso contrário.
 */
int BuscaSequencial(const vector<int>& v, int chave);

/**
 * \brief Realiza busca binária em um vetor ordenado.
 * \param v O vetor ordenado onde a busca será realizada.
 * \param chave O valor a ser procurado.
 * \return O índice da chave se encontrada, -1 caso contrário.
 */
int BuscaBinaria(const vector<int>& v, int chave);

//Algoritmos Ordenação

/**
 * \brief Ordena um vetor usando o algoritmo Insertion Sort.
 * \param v O vetor a ser ordenado (modificado in-place).
 */
void InsertionSort(vector<int>& v);

/**
 * \brief Ordena um vetor usando o algoritmo Bubble Sort.
 * \param v O vetor a ser ordenado (modificado in-place).
 */
void BubbleSort(vector<int>& v);

/**
 * \brief Ordena um vetor usando o algoritmo Merge Sort.
 * \param v O vetor a ser ordenado (modificado in-place).
 */
void MergeSort(vector<int>& v);

/**
 * \brief Ordena um vetor usando o algoritmo Quick Sort.
 * \param v O vetor a ser ordenado (modificado in-place).
 */
void QuickSort(vector<int>& v);

#endif