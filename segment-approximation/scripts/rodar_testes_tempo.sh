#!/bin/bash

EXEC="../programa"
PASTA_TESTES="../TimeTests"

# Garante que o executável existe na raiz
if [ ! -f "$EXEC" ]; then
    echo "Erro: Executável '$EXEC' não encontrado na raiz. Compile o programa primeiro."
    exit 1
fi

# Se os arquivos grandes não existirem localmente, chama o gerador
if [ ! -d "$PASTA_TESTES" ] || [ ! -f "$PASTA_TESTES/grande_1M.txt" ]; then
    echo "Arquivos gigantes não encontrados. Chamando o gerador..."
    if [ -f "./gerar_grandes_entradas.sh" ]; then
        chmod +x gerar_grandes_entradas.sh
        ./gerar_grandes_entradas.sh
    else
        echo "Erro: 'gerar_grandes_entradas.sh' não encontrado na pasta de scripts."
        exit 1
    fi
fi

echo ""
echo "====================================================="
echo "   INICIANDO TESTE DE ESCALA TEMPORAL O(n log n)"
echo "====================================================="

testar() {
    local nos=$1
    local arquivo=$2
    echo ""
    echo "-----------------------------------------------------"
    echo "[TESTE] Rodando com $nos pontos..."
    echo "-----------------------------------------------------"
    time "$EXEC" -a 250.0 < "$PASTA_TESTES/$arquivo" > /dev/null
}

testar "10.000" "grande_10k.txt"
testar "100.000 (10x maior)" "grande_100k.txt"
testar "1.000.000 (100x maior)" "grande_1M.txt"

echo ""
echo "====================================================="
echo "            Testes de tempo concluídos!"
echo "====================================================="
