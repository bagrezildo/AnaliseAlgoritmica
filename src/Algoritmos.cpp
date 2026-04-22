#include "Algoritmos.hpp"
#include <cmath>

int BuscaSequencial(const vector<int>& v, int chave){
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i] == chave)
            return i;
    }
    return -1;
}

int BuscaBinaria(const vector<int>& v, int chave){
    int inicio = 0;
    int fim = v.size() - 1;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;

        if (v[meio] == chave)
            return meio;
        else if (v[meio] < chave)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    return -1;
}

//Algoritmos de Ordenação

void InsertionSort(vector<int>& v){
    int n = v.size();
    int chave, j;
    
    for (int i = 1; i < n; i++){
        chave = v[i];
        j = i;

        while ( j > 0 && v[j-1] > chave) {
            v[j] = v[j-1];
            j--; 
        }
        v[j] = chave;
    }
}

void BubbleSort(vector<int>& v){
    int n = v.size();
    if(n <= 1) return;

    bool trocou;
    for (int i = 0; i < n - 1; i++){
        trocou = false;
        for (int j = 0; j < n - i - 1; j++){
            if (v[j] > v[j+1]){
                swap(v[j], v[j+1]);
                trocou = true;
            }
        }

        if (!trocou) break;
    }
}

// --- Funções auxiliares do Merge Sort ---
void Merge(vector<int>& v, int esq, int meio, int dir) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = v[esq + i];
    for (int j = 0; j < n2; j++) R[j] = v[meio + 1 + j];

    int i = 0, j = 0, k = esq;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) { v[k] = L[i]; i++; } 
        else { v[k] = R[j]; j++; }
        k++;
    }
    while (i < n1) { v[k] = L[i]; i++; k++; }
    while (j < n2) { v[k] = R[j]; j++; k++; }
}

void MergeSortHelper(vector<int>& v, int esq, int dir) {
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2;
        MergeSortHelper(v, esq, meio);
        MergeSortHelper(v, meio + 1, dir);
        Merge(v, esq, meio, dir);
    }
}

void MergeSort(vector<int>& v) {
    if (!v.empty()) {
        MergeSortHelper(v, 0, v.size() - 1);
    }
}

// ---

int Particao(vector<int>& v, int baixo, int alto) {
    // Escolhe o pivô no meio para evitar o pior caso O(n^2) em arrays invertidos
    int meio = baixo + (alto - baixo) / 2;
    swap(v[meio], v[alto]); 
    
    int pivo = v[alto];
    int i = (baixo - 1);
    
    for (int j = baixo; j <= alto - 1; j++) {
        if (v[j] < pivo) {
            i++;
            swap(v[i], v[j]);
        }
    }
    swap(v[i + 1], v[alto]);
    return (i + 1);
}

void QuickSortHelper(vector<int>& v, int baixo, int alto) {
    if (baixo < alto) {
        int pi = Particao(v, baixo, alto);
        QuickSortHelper(v, baixo, pi - 1);
        QuickSortHelper(v, pi + 1, alto);
    }
}

void QuickSort(vector<int>& v) {
    if (!v.empty()) QuickSortHelper(v, 0, v.size() - 1);
}