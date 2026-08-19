#!/bin/bash

# Função para gerar um arquivo com N pontos flutuantes aleatórios
gerar_arquivo() {
    local n=$1
    local nome_arquivo=$2
    
    echo "Gerando $nome_arquivo com $n pontos..."
    
    # Escreve a quantidade de pontos na primeira linha
    echo "$n" > "$nome_arquivo"
    
    awk -v n="$n" 'BEGIN {
        srand();
        for (i = 1; i <= n; i++) {
            printf "%.4f\n", rand() * 500
        }
    }' >> "$nome_arquivo"
}

# Cria a pasta dentro de scripts/ se não existir
mkdir -p ../TimeTests

# Gera os três cenários de teste de escala
gerar_arquivo 10000 "../TimeTests/grande_10k.txt"
gerar_arquivo 100000 "../TimeTests/grande_100k.txt"
gerar_arquivo 1000000 "../TimeTests/grande_1M.txt"

echo "Todos os arquivos foram gerados com sucesso na pasta 'TimeTests'"