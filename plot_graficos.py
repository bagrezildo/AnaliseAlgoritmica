import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit
import sys
import warnings

# Ignorar avisos de matemática do SciPy
warnings.filterwarnings('ignore')

# 1. Carregar os dados
try:
    df = pd.read_csv("resultados.csv")
except FileNotFoundError:
    print("Erro: Ficheiro 'resultados.csv' não encontrado.")
    sys.exit(1)

# 2. Converter os tempos (Buscas em µs, Ordenações em ms)
df['TempoMedio_us'] = df['TempoMedio_ns'] / 1000.0       
df['TempoMedio_ms'] = df['TempoMedio_ns'] / 1000000.0    

# 3. Dicionário Teórico
complexidades = {
    "BuscaSequencial": ("O(n)", lambda n: n),
    "BuscaBinaria": ("O(log_2 n)", lambda n: np.log2(n)),
    "MergeSort": ("O(n log n)", lambda n: n * np.log2(n)),
    "QuickSort": ("O(n log n)", lambda n: n * np.log2(n))
}

# 4. Função de Plotagem
def plotar_grupo(nome_grupo, df_grupo, coluna_tempo, label_y, usar_log_y=False):
    if df_grupo.empty: 
        return
    
    plt.figure(figsize=(12, 7))
    algoritmos = df_grupo['Algoritmo'].unique()
    
    # Paleta de cores moderna (Set1 do Matplotlib)
    cores = plt.colormaps.get_cmap('Set1').resampled(len(algoritmos) + 2)
    
    for idx, alg in enumerate(algoritmos):
        dados = df_grupo[df_grupo['Algoritmo'] == alg].sort_values(by='N')
        n_vals = dados['N'].values
        t_vals = dados[coluna_tempo].values
        
        if len(n_vals) == 0:
            continue
            
        cor_atual = cores(idx)
        
        # Linha Real
        plt.plot(n_vals, t_vals, marker='o', linestyle='-', label=f'{alg} (Real)', color=cor_atual, linewidth=2, markersize=6)

        # Curva Teórica Ajustada
        if alg in complexidades:
            nome_teorico, func_teorica = complexidades[alg]
            n_min = max(1, min(n_vals))
            n_max = max(n_vals)
            n_teorico = np.linspace(n_min, n_max, 200)
            
            def modelo_teorico(x, c):
                return c * np.array(func_teorica(x), dtype=float)
                
            try:
                popt, _ = curve_fit(modelo_teorico, n_vals, t_vals)
                y_ajustado = modelo_teorico(n_teorico, popt[0])
                plt.plot(n_teorico, y_ajustado, '--', color=cor_atual, alpha=0.7, label=f'Ajuste: {nome_teorico}', linewidth=2)
            except Exception as e:
                print(f"Não ajustou a curva {alg}. Erro: {e}")

    # 5. Visuais e Eixos
    plt.title(f'Análise de Complexidade Empírica: {nome_grupo}', fontsize=16, weight='bold', pad=15)
    plt.xlabel('Tamanho da Entrada (N)', fontsize=13, weight='bold')
    
    if usar_log_y:
        plt.yscale('log')
        plt.ylabel(f'{label_y} (Escala Log)', fontsize=13, weight='bold')
    else:
        plt.ylabel(label_y, fontsize=13, weight='bold')
    
    plt.ticklabel_format(style='plain', axis='x') # Remover notação científica no eixo X
    plt.legend(fontsize=11, bbox_to_anchor=(1.02, 1), loc='upper left', borderaxespad=0., frameon=True, shadow=True)
    plt.grid(True, which="both", linestyle='--', alpha=0.5)
    plt.tight_layout()
    
    nome_arquivo = f'grafico_{nome_grupo.lower()}.png'
    plt.savefig(nome_arquivo, dpi=300, bbox_inches='tight')
    print(f"Gerado: {nome_arquivo}")

# 6. Separar e Plotar
df_buscas = df[df['Tipo'] == 'Busca']
df_ordenacoes = df[df['Tipo'] == 'Ordenacao']

plotar_grupo("Buscas", df_buscas, 'TempoMedio_us', 'Tempo de Execução (µs)', usar_log_y=True)
plotar_grupo("Ordenacoes", df_ordenacoes, 'TempoMedio_ms', 'Tempo de Execução (ms)', usar_log_y=False)