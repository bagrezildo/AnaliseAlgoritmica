#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <string>
#include <vector>

using namespace std;



class Printer {
    public:
        struct Resultado {
            string algoritmo;
            string tipo;
            int tamanho_n;
            long long tempo_medio_ns;
            double desvio_padrao;
        };

        static void helper();
        static void header();
        static void ExportarParaCSV(const std::vector<Resultado>& resultados, const std::string& nomeArquivo);
};

#endif // PRINTER_H