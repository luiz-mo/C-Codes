# Enunciado
## Objetivos
Este trabalho tem como objetivo modificar o Tipo Abstrato de Dados (TAD) para números racionais feito no trabalho anterior para que algumas funções recebam parâmetros
por endereços. O motivo da alteração é para que os protótipos das funções fiquem mais
elegantes, pois tendo a opção de modificar o valor de uma variável recebida como parâmetro por endereço, podemos utilizar o retorno da função para retornar um código de
erro.
## O trabalho
Você deve adaptar a sua implementação do arquivo racional.c conforme o novo arquivo
racional.h fornecido

• racional.h: arquivo (read only) de header com todos os protótipos das funções
para manipular números racionais;

• racional.c: esqueleto de arquivo, a completar;

• tp2.c: esqueleto de arquivo, a completar.

## O programa
No arquivo racional.h foi definida uma interface para o tipo abstrato de dados racional
que usa a mesma estrutura para os números racionais usada no trabalho anterior. Você
deve implementar o arquivo racional.c conforme especificado no arquivo racional.h
fornecido. Seu programa principal deve incluir o header racional.h e deve ter uma
função main que implemente corretamente em C o seguinte pseudo-código:

```text
defina um vetor para até 100 números racionais

leia um valor n tal que 0 < n < 100

preencha o vetor com n números racionais lidos da entrada (leia o numerador e o denominador de cada racional)
imprima "VETOR = " e o conteúdo do vetor lido

elimine deste vetor os elementos inválidos
imprima "VETOR = " e o conteúdo do vetor resultante

ordene este vetor
imprima "VETOR = " e o conteúdo do vetor resultante

calcule a soma de todos os elementos do vetor
imprima "SOMA = " e a soma calculada acima

nova linha
retorne 0
