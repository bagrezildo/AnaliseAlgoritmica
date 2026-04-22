/**
 * \file Printer.cpp
 * \brief Implementações da classe Printer.
 * \author Matheus Miguel
 * \date 2026
 */

#include "Printer.hpp"
#include "text_color.hpp"

#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <fstream>


using namespace std;

void Printer::helper() {
    cout << "Uso: benchmark <N1> <N2> <N3> ... <Nn>" << endl;
    cout << "\tOnde os argumentos são:"<< endl;
    cout << "\t\t\t<Nn>\t\t A quantidade de elementos dentro do vetor de entrada." << endl;
}

void Printer::header(){
    cout << Color::tcolor("=================================================================================", Color::BOLD) << endl;
    cout << "                         Welcome to the C++ Algorithm Complexity Analyser, v1.0" << endl;
    cout << "                           Copyright (C) 2026, Matheus Miguel" << endl;
    cout << Color::tcolor("=================================================================================", Color::BOLD) << endl;
    cout << Color::tcolor("Esse programa realiza a medicao de desempenho e analise de complexidade\n"
                        "empirica de algoritmos de busca e ordenacao.", Color::BRIGHT_CYAN, Color::BOLD) << endl;
    cout << endl;
}

void Printer::ExportarParaCSV(const std::vector<Resultado>& resultados, const std::string& nomeArquivo) {
    ofstream arquivoCSV(nomeArquivo);
    
    if (!arquivoCSV.is_open()) {
        std::cerr << "Erro ao criar o arquivo CSV." << std::endl;
        return;
    }
    
    // Escreve o cabeçalho
    arquivoCSV << "Algoritmo,Tipo,N,TempoMedio_ns\n"; 
    
    // Escreve os dados
    for (const auto& res : resultados) {
        arquivoCSV << res.algoritmo << ","
                   << res.tipo << ","
                   << res.tamanho_n << ","
                   << res.tempo_medio_ns << "\n";
    }
    
    arquivoCSV.close();
}