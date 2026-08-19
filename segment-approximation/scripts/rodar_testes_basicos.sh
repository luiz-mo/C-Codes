#!/bin/bash

echo -e "\n============================================="
echo "   INICIANDO BATERIA DE TESTES COM VALGRIND"
echo -e "=============================================\n"

# Função auxiliar para rodar o teste
rodar_teste() {
    local arquivo=$1
    local param=$2
    local valor=$3
    
    echo "----------------------------------------"
    echo "Testando: $(basename "$arquivo") ($param $valor)"
    echo "----------------------------------------"
    
    # EXECUTAR VALGRIND SILENCIANDO A SAÍDA DO PROGRAMA (> /dev/null)
    valgrind --leak-check=full --errors-for-leak-kinds=all --show-leak-kinds=all --track-origins=yes --log-file=valgrind_temp.log ../programa $param $valor < "$arquivo" > /dev/null 2>&1
    
    # ANALISAR O LOG DO VALGRIND
    local leaks=$(grep "definitely lost:" valgrind_temp.log | awk '{print $3}')
    local erros=$(grep "ERROR SUMMARY:" valgrind_temp.log | awk '{print $4}')
    
    if [ "$erros" != "0" ] && [ "$erros" != "" ] || [ "$leaks" != "0" ] && [ "$leaks" != "" ]; then
        echo -e "\033[0;31m[FALHOU] Erros detectados pelo Valgrind!\033[0m"
        grep "ERROR SUMMARY:" valgrind_temp.log
        grep "definitely lost:" valgrind_temp.log
    else
        echo -e "\033[0;32m[PASSOU] Memória limpa e sem erros.\033[0m"
    fi
    
    # APAGA O LOG TEMPORÁRIO PARA DEIXAR A PASTA LIMPA
    rm -f valgrind_temp.log
    echo ""
}

# --- MAPEAMENTO DOS CASOS DE TESTE (Buscando em ../MinimumTests) ---

# Os 4 Testes Iniciais
rodar_teste "../MinimumTests/teste1-linha.txt" "-a" "1.0"
rodar_teste "../MinimumTests/teste2-triangulo.txt" "-h" "1.0"
rodar_teste "../MinimumTests/teste3-quatro-pontos.txt" "-a" "10.0"
rodar_teste "../MinimumTests/teste4-subida.txt" "-h" "10.0"

# Casos normais e limites de tolerância (Área)
rodar_teste "../MinimumTests/teste5-serie-crescente.txt" "-a" "1.0"
rodar_teste "../MinimumTests/teste8-pico-isolado.txt" "-a" "10.0"
rodar_teste "../MinimumTests/teste9-serie-decrescente.txt" "-a" "1.0"
rodar_teste "../MinimumTests/teste10-serie-constante.txt" "-a" "1.0"
rodar_teste "../MinimumTests/teste11-valores-negativos.txt" "-a" "1.0"
rodar_teste "../MinimumTests/teste12-notacao-cientifica.txt" "-a" "1.0"
rodar_teste "../MinimumTests/teste13-muitos-pontos.txt" "-a" "50.0"

# Casos de picos
rodar_teste "../MinimumTests/teste14-pico-inicial.txt" "-a" "10.0"
rodar_teste "../MinimumTests/teste15-pico-final.txt" "-a" "10.0"
rodar_teste "../MinimumTests/teste16-dois-picos.txt" "-a" "10.0"
rodar_teste "../MinimumTests/teste17-valores-proximos.txt" "-a" "0.01"

# Caso tolerância zero (nada deve sumir)
rodar_teste "../MinimumTests/teste18-tolerancia-zero.txt" "-a" "0.0"

# CASOS EXTREMOS (1 e 2 pontos)
rodar_teste "../MinimumTests/teste6-2pontos.txt" "-a" "5.0"
rodar_teste "../MinimumTests/teste7-1ponto.txt" "-a" "5.0"

echo "============================================="
echo "            TESTES CONCLUÍDOS!"
echo "============================================="