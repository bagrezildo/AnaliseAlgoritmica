# Análise Algorítmica

Este projeto implementa uma análise empírica de algoritmos de busca e ordenação, comparando seus desempenhos em termos de tempo de execução para diferentes tamanhos de entrada. O programa é escrito em C++ e inclui ferramentas para gerar gráficos de análise de complexidade usando Python.

## Funcionalidades

- **Algoritmos de Busca**:

  - Busca Sequencial (O(n))
  - Busca Binária (O(log n))
- **Algoritmos de Ordenação**:

  - Merge Sort (O(n log n))
  - Quick Sort (O(n log n))
- **Análise Empírica**: Medição de tempos de execução com múltiplas repetições para obter médias confiáveis.
- **Geração de Gráficos**: Script Python para visualizar comparações entre tempos empíricos e complexidades teóricas.

## Estrutura do Projeto

```
AnaliseAlgoritmica/
├── src/                    # Código fonte C++
│   ├── main.cpp           # Função principal
│   ├── Algoritmos.cpp     # Implementações dos algoritmos
│   └── Printer.cpp        # Utilitários de impressão
├── include/               # Headers C++
│   ├── Algoritmos.hpp
│   ├── Printer.hpp
│   └── text_color.hpp
├── bin/                   # Executáveis compilados
├── build/                 # Arquivos objeto de compilação
├── docs/                  # Documentação gerada pelo Doxygen
├── plot_graficos.py       # Script para gerar gráficos
├── requirements.txt       # Dependências Python
├── Makefile              # Script de compilação
├── Doxyfile              # Configuração do Doxygen
└── README.md             # Este arquivo
```

## Pré-requisitos

### Para C++

- Compilador g++ com suporte a C++17
- Make (para usar o Makefile)

### Para Python (gráficos)

- Python 3.x
- Bibliotecas listadas em `requirements.txt`:
  - pandas
  - matplotlib
  - numpy
  - scipy

## Instalação

1. **Clone ou baixe o repositório**:

   ```bash
   git clone <url-do-repositorio>
   cd AnaliseAlgoritmica
   ```
2. **Instale as dependências Python**:

   ```bash
   pip install -r requirements.txt
   ```

## Compilação

Para compilar o projeto, use o Makefile:

```bash
make all
```

Isso irá:

- Criar os diretórios `build/` e `bin/` se não existirem
- Compilar todos os arquivos fonte
- Gerar o executável `bin/benchmark` (Linux/Mac) ou `bin/benchmark.exe` (Windows)

## Execução

### Executando Testes

Para executar a bateria de testes com tamanhos de entrada específicos:

```bash
make test
```

Ou manualmente:

```bash
./bin/benchmark 1000 5000 10000 15000 20000
```

O programa aceita múltiplos argumentos representando tamanhos de N (número de elementos).

### Saída

O programa gera:

- Um arquivo `resultados.csv` com os tempos médios de execução
- Saída no terminal mostrando o progresso dos testes

## Geração de Gráficos

Após executar os testes, use o script Python para gerar gráficos:

```bash
python plot_graficos.py
```

Isso criará arquivos de imagem `grafico_busca.png` e `grafico_ordenacao.png` comparando os desempenhos empíricos com as complexidades teóricas.

## Documentação

Para gerar a documentação completa usando Doxygen:

```bash
doxygen Doxyfile
```

A documentação será gerada em `docs/html/index.html`.

## Limpeza

Para limpar arquivos de compilação e resultados:

```bash
make clean
```

Isso remove os diretórios `build/`, `bin/`, `resultados.csv` e arquivos de gráfico.

## Autor

- **Matheus Miguel** - Desenvolvimento inicial

## Notas Técnicas

- Os testes de busca são realizados no pior caso (elemento não encontrado)
- Os testes de ordenação usam vetores invertidos (pior caso)
- Os tempos são medidos em nanossegundos para alta precisão
- O número de repetições é ajustável no código fonte
