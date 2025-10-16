# Enunciado
Este trabalho tem como objetivo a implementação de um Tipo Abstrato de Dados (TAD)
para números racionais, além de praticar o desenvolvimento de programas na linguagem
C. A partir deste trabalho passaremos a entender como escrever programas que usam
mais de um arquivo fonte.

Você deve implementar um programa que manipule números racionais, que são números
da forma a/b, onde a e b são números inteiros.

racional.c: um esqueleto de arquivo racionais.c;

makefile: sugestão de um makefile que você pode usar.

tp1.c: um esqueleto de arquivo tp1.c.

No arquivo racional.h foi definida uma interface para o tipo abstrato de dados racional que usa uma struct para os números racionais. Você deve implementar o arquivo
racional.c conforme especificado no racional.h fornecido. A sua função main deve incluir o header racional.h e deve ter um laço principal que implemente corretamente
em C o seguinte pseudo-código:
```text
inicialize a semente randomica, uma unica vez em todo o codigo

sugestao: use "srand(0)" para facilitar os testes
leia um n tal que 0 < n < 100
leia um max tal que 0 < max < 30
para todo i de 1 ate n faca
   /* use um unico espaco em branco separando numeros na mesma linha */
   imprima o valor de i seguido de um ": " e um espaco em branco
   sorteie dois racionais r1 e r2

    os numeradores e denominadores devem estar entre -max e max
    imprima r1 e r2, na mesma linha e nao mude de linha
    se r1 ou r2 forem um dos dois invalidos, entao:
       imprima "NUMERO INVALIDO" e retorne 1

    calcule r1 + r2
    calcule r1 - r2
    calcule r1 * r2
    calcule r1 / r2

    se a divisao for invalida, entao:
       imprima "DIVISAO INVALIDA" e retorne 1

    imprima na mesma linha r1 + r2
    imprima na mesma linha r1 - r2
    imprima na mesma linha r1 * r2
    imprima na mesma linha r1 / r2
    mude de linha
fim_para

retorne 0
