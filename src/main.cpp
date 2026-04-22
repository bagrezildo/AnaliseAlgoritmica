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

// Declarações das funções auxiliares para gerar vetores de teste
vector<int> VetorOrdenado(int tamanho);
vector<int> VetorInvertido(int tamanho);

/**
 * \brief Função principal que executa a análise empírica dos algoritmos.
 *
 * Esta função coordena a execução de testes de desempenho para algoritmos de busca
 * e ordenação, coletando tempos de execução e exportando os resultados para um arquivo CSV.
 *
 * \param argc Número de argumentos da linha de comando
 * \param argv Array de strings contendo os argumentos (tamanhos de teste N)
 * \return 0 em caso de sucesso, 1 se argumentos insuficientes
 */
int main(int argc, char* argv[]){
    // Exibe o cabeçalho do programa
    Printer::header();
    
    // Verifica se foram fornecidos argumentos suficientes (pelo menos um tamanho N)
    if (argc < 2) {
        Printer::helper();
        return 1;
    }

    // Vetor para armazenar todos os resultados dos testes
    vector<Printer::Resultado> todosResultados;

    // Converte os argumentos da linha de comando para tamanhos de teste
    vector<int> tamanhosN;
    for (int i = 1; i < argc; ++i) {
        tamanhosN.push_back(atoi(argv[i]));
    }

    // Mapeia os nomes dos algoritmos de busca para suas funções correspondentes
    map<string, AlgoritmoBusca> buscas{
        {"BuscaSequencial", BuscaSequencial},
        {"BuscaBinaria", BuscaBinaria},
    };

    // Mapeia os nomes dos algoritmos de ordenação para suas funções correspondentes
    map<string, AlgoritmoOrdenacao> ordenacoes{
        {"MergeSort", MergeSort},
        {"QuickSort", QuickSort}
    };
    
    cout << "Iniciando a bateria de testes empiricos...\n";
    
    // Número de repetições para algoritmos de busca (para obter média confiável)
    int numRepeticoesBusca = 1000;
    
    // Loop através de cada algoritmo de busca
    for (const auto& par :  buscas){
        string nomeAlgoritmo = par.first;
        AlgoritmoBusca funcao = par.second;

        // Loop através de cada tamanho de teste N
        for (int n : tamanhosN){
            cout << "Testando " << nomeAlgoritmo << " com N = " << n << "...\n";
            
            // Gera um vetor ordenado para testes de busca
            vector<int> dados = VetorOrdenado(n);
            
            // Define o alvo como -1 para testar o pior caso (elemento não encontrado)
            int alvo = -1; // Verificando o pior caso

            // Chamada inicial para aquecer o cache (não conta para medição)
            funcao(dados, alvo);

            long long tempoTotal = 0;

            // Executa múltiplas repetições para calcular o tempo médio
            for (int r=0; r < numRepeticoesBusca; ++r){
                auto inicio = high_resolution_clock::now();

                funcao(dados, alvo);

                auto fim  = high_resolution_clock::now();
                tempoTotal += duration_cast<nanoseconds>(fim - inicio).count();
            }
            
            // Calcula o tempo médio em nanossegundos
            long long tempoMedio = tempoTotal / numRepeticoesBusca;
            
            // Armazena o resultado para exportação posterior
            todosResultados.push_back({nomeAlgoritmo, "Busca", n, tempoMedio});
        }
    }

    // Número de repetições para algoritmos de ordenação (menor devido ao custo maior)
    int numRepeticoesOrdenacao = 10;
    
    // Loop através de cada algoritmo de ordenação
    for (const auto& par: ordenacoes){
        string nomeAlgoritmo = par.first;
        AlgoritmoOrdenacao funcao = par.second;

        // Loop através de cada tamanho de teste N
        for (int n : tamanhosN){
            
            cout << "Testando " << nomeAlgoritmo << " com N = " << n << "...\n";

            // Gera um vetor invertido para testar o pior caso de ordenação
            vector<int> dadosInvertidos = VetorInvertido(n);

            // Chamada inicial para aquecer o cache
            funcao(dadosInvertidos);

            long long tempoTotal = 0;

            // Executa múltiplas repetições para calcular o tempo médio
            for (int r = 0; r < numRepeticoesOrdenacao; ++r){
                // Cria uma cópia dos dados para não modificar o original
                vector<int> dadosParaOrdenar = dadosInvertidos;

                auto inicio = high_resolution_clock::now();

                funcao(dadosParaOrdenar);

                auto fim = high_resolution_clock::now();
                
                tempoTotal += duration_cast<nanoseconds>(fim - inicio).count();
            }
            
            // Calcula o tempo médio em nanossegundos
            long long tempoMedio = tempoTotal / numRepeticoesOrdenacao;
            
            // Armazena o resultado para exportação posterior
            todosResultados.push_back({nomeAlgoritmo, "Ordenacao", n, tempoMedio});
        }

    }

    // Exporta todos os resultados coletados para um arquivo CSV
    std::cout << "Exportando resultados para o disco...\n";
    Printer::ExportarParaCSV(todosResultados, "resultados.csv");
    cout << "Coleta empirica de dados concluida. Resultados salvos em 'resultados.csv'.\n";
    cout << "Para ver os graficos, execute o script: ./run_plot.sh (Linux) ou run_plot.bat (Windows)\n";
    
    return 0;
}

/**
 * \brief Gera um vetor de inteiros ordenado de 0 a tamanho-1.
 *
 * Esta função é usada para criar vetores ordenados necessários para os testes
 * de algoritmos de busca, especialmente a busca binária que requer dados ordenados.
 *
 * \param tamanho O tamanho do vetor a ser gerado
 * \return Vetor de inteiros ordenado
 */
vector<int> VetorOrdenado(int tamanho) {
    vector<int> vec(tamanho);
    for (int i = 0; i < tamanho; i++){
        vec[i] = i;
    }

    return vec;
}

/**
 * \brief Gera um vetor de inteiros em ordem inversa (decrescente).
 *
 * Esta função cria vetores invertidos que representam o pior caso para algoritmos
 * de ordenação, onde os elementos estão na ordem oposta à desejada.
 *
 * \param tamanho O tamanho do vetor a ser gerado
 * \return Vetor de inteiros em ordem inversa
 */
vector<int> VetorInvertido(int tamanho) {
    vector<int> vec(tamanho);
    for (int i = 0; i < tamanho; i++) {
        vec[i] = tamanho - i;
    }
    return vec;
}