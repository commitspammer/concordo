# LP1 Trabalho 2 - Concordo

Repositório do Concordo implementado em c++ para a disciplina de Linguagem de Programação 1.

Comentários das funções podem ser encontrados nos seus respectivos [headers](./include).

Informações dos autores podem ser encontrados em [autor.md](./autor.md).

## Compilando a aplicação

Clone este repositório em sua máquina, tenha `make` instalado no sistema e faça:
```
$ make clean install
```

## Executando a aplicação

Faça:
```
$ make run
```
Ou:
```
$ ./bin/concordo
```

## Executando testes

Faça:
```
$ make run F=[FILE_PATH]
```
Ou:
```
$ ./bin/concordo < [FILE_PATH]
```
Onde [FILE_PATH] é o caminho do arquivo de testes (sem colchetes).

Arquivos exemplos de teste podem ser encontrados no diretório [data](./data).

## Limitações e funcionalidades não implementadas

Tanto o [executor.cpp](./src/executor.cpp) quanto o [sistema.h](./include/sistema.h) foram modificados e diferem dos originais do trabalho. Sem essas versões modificadas, seria possível passar strings vazias para as funções do sistema, e [Sistema::list_users()](./src/sistema.cpp) causaria erro na compilação.

O atributo [Mensagem::data_hora](./src/mensagem.cpp) so irá gerar o ano correto neste século (XXI).
