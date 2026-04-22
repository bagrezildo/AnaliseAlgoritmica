/**
 * \file Printer.hpp
 * \brief Classe para impressão de resultados e exportação de dados.
 * \author Matheus Miguel
 * \date 2026
 */

#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <string>
#include <vector>

using namespace std;

/**
 * \class Printer
 * \brief Classe responsável por imprimir mensagens e exportar resultados para CSV.
 */
class Printer {
    public:
        /**
         * \struct Resultado
         * \brief Estrutura para armazenar os resultados de um algoritmo.
         */
        struct Resultado {
            string algoritmo; /**< Nome do algoritmo testado. */
            string tipo; /**< Tipo do algoritmo (Busca ou Ordenacao). */
            int tamanho_n; /**< Tamanho do vetor de entrada. */
            long long tempo_medio_ns; /**< Tempo médio em nanosegundos. */
            double desvio_padrao; /**< Desvio padrão do tempo (não usado atualmente). */
        };

        /**
         * \brief Imprime a mensagem de ajuda para o uso do programa.
         */
        static void helper();

        /**
         * \brief Imprime o cabeçalho do programa.
         */
        static void header();

        /**
         * \brief Exporta os resultados para um arquivo CSV.
         * \param resultados Vetor de resultados a serem exportados.
         * \param nomeArquivo Nome do arquivo CSV de saída.
         */
        static void ExportarParaCSV(const std::vector<Resultado>& resultados, const std::string& nomeArquivo);
};

#endif // PRINTER_H