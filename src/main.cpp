/**
 * \file main.cpp
 * \brief Função principal do programa de análise de algoritmos.
 * \author Matheus Miguel
 * \date 2026
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <map>
#include <string>
#include <fstream>
#include <cstdlib>
#include <filesystem>

#include "Algoritmos.hpp"
#include "Printer.hpp"

using namespace std;
using namespace std::chrono;

vector<int> VetorOrdenado(int tamanho);
vector<int> VetorInvertido(int tamanho);

int main(int argc, char* argv[]){
    Printer::header();
    
    if (argc < 2) {
        Printer::helper();
        return 1;
    }

    vector<Printer::Resultado> todosResultados;

    vector<int> tamanhosN;
    for (int i = 1; i < argc; ++i) {
        tamanhosN.push_back(atoi(argv[i]));
    }

    map<string, AlgoritmoBusca> buscas{
        {"BuscaSequencial", BuscaSequencial},
        {"BuscaBinaria", BuscaBinaria},
    };

    map<string, AlgoritmoOrdenacao> ordenacoes{
        {"MergeSort", MergeSort},
        {"QuickSort", QuickSort}
    };
    
    cout << "Iniciando a bateria de testes empiricos...\n";
    
    int numRepeticoesBusca = 1000;
    for (const auto& par :  buscas){
        string nomeAlgoritmo = par.first;
        AlgoritmoBusca funcao = par.second;

        
        for (int n : tamanhosN){
            cout << "Testando " << nomeAlgoritmo << " com N = " << n << "...\n";
            vector<int> dados = VetorOrdenado(n);
            int alvo = -1; // Verificando o pior caso

            funcao(dados, alvo);

            long long tempoTotal = 0;

            for (int r=0; r < numRepeticoesBusca; ++r){
                auto inicio = high_resolution_clock::now();

                funcao(dados, alvo);

                auto fim  = high_resolution_clock::now();
                tempoTotal += duration_cast<nanoseconds>(fim - inicio).count();
            }
            
            long long tempoMedio = tempoTotal / numRepeticoesBusca;
            todosResultados.push_back({nomeAlgoritmo, "Busca", n, tempoMedio});
        }
    }


    int numRepeticoesOrdenacao = 10;
    
    for (const auto& par: ordenacoes){
        string nomeAlgoritmo = par.first;
        AlgoritmoOrdenacao funcao = par.second;

        for (int n : tamanhosN){
            
            cout << "Testando " << nomeAlgoritmo << " com N = " << n << "...\n";

            vector<int> dadosInvertidos = VetorInvertido(n);

            funcao(dadosInvertidos);

            long long tempoTotal = 0;

            for (int r = 0; r < numRepeticoesOrdenacao; ++r){
                vector<int> dadosParaOrdenar = dadosInvertidos;

                auto inicio = high_resolution_clock::now();

                funcao(dadosParaOrdenar);

                auto fim = high_resolution_clock::now();
                
                tempoTotal += duration_cast<nanoseconds>(fim - inicio).count();
            }
            long long tempoMedio = tempoTotal / numRepeticoesOrdenacao;
            todosResultados.push_back({nomeAlgoritmo, "Ordenacao", n, tempoMedio});
        }

    }

    std::cout << "Exportando resultados para o disco...\n";
    Printer::ExportarParaCSV(todosResultados, "resultados.csv");
    cout << "Coleta empirica de dados concluida. Resultados salvos em 'resultados.csv'.\n";
    cout << "Para ver os graficos, execute o script: ./run_plot.sh (Linux) ou run_plot.bat (Windows)\n";
    
    return 0;
}

vector<int> VetorOrdenado(int tamanho) {
    vector<int> vec(tamanho);
    for (int i = 0; i < tamanho; i++){
        vec[i] = i;
    }

    return vec;
}

vector<int> VetorInvertido(int tamanho) {
    vector<int> vec(tamanho);
    for (int i = 0; i < tamanho; i++) {
        vec[i] = tamanho - i;
    }
    return vec;
}