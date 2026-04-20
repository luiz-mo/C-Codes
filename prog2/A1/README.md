# Anotações para escrever relatorio depois
mudei o gbv_remove e gbv_view para receber o nome da biblioteca
# Relatorio do trabalho

## Autoria
Luiz Guilherme de Souza Mo GRR 20252981

## Lista de Arquivos
Mantive a estrutura padrao de arquivos, adicionando apenas o diretorio src contendo arquivos para teste

### src
#### Arquivos de teste

### main.c
### gbv.c
### gbv.h
### util.c
### util.h
### Makefile

## Dificuldades enfrentadas + bugs conhecidos
No início, posso dizer que minha maior dificuldade foi utilizar as funções de manipulação de arquivos binários, visto que não pude comparecer à aula desse dia. No entanto, é realmente fácil encontrar a documentação dessas funções e com o tempo consegui me acostumar com seu uso. No início também levei um tempo para me lembrar como usar as funções da biblioteca string.h, mas isso não foi um problema posteriormente. 

Depois de entender isso, fui tentar entender o enunciado em si do trabalho e o gbv.h fornecido. Consegui fazer as funções mais simples(gbv_create, gbv_open e gbv_list), porém na hora de ir para o gbv_add, surgiram muitas duvidas de como fazer isso e eu ainda não tinha certeza se havia compreendido a estrutura do gbv. Depois de pedir uma explicação melhor do professor, o desenvolvimento fluiu melhor, principalmente na gbv_add que considero a função mais complicada do trabalho.

Para as funções gbv_remove e gbv_view, não consegui fazer usando a assinatura original do gbv.h fornecido e para ambas, incluí como argumento o nome da biblioteca.

- int gbv_remove(Library *lib, const char *archive, const char *docname);
- int gbv_view(const Library *lib, const char *archive, const char *docname);

Também fiz algumas mudanças no main, incluindo a opcão -c para criar um .gbv, sendo necessário criar a biblioteca antes de tentar utilizá-la e também adicionei mensagens de erro para cada opção.

Na questão do gbv_view, considero que também enfrentei dificuldades, pois pensei demais no tamanho dos blocos não ser fixo, por exemplo, um documento com 2100 bytes com blocos de 1024 bytes teria dois blocos de 1024B e outro de 52B. Porém, vi que o jeito que eu estava tentando fazer não iria funcionar para dois 'p' seguidos, então adotei que os blocos voltam com tamanho fixo e não com o tamanho do bloco atual.

Na questão de bugs conhecidos, não identifiquei nenhum nos testes que fiz. Para testar, testei os casos de erro da cada função do gbv.c, adicionei arquivos, removi todos e adicionei de novo, tentei remover mais de uma vez e, em todos, a saída estava correta.
