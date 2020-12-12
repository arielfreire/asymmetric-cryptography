![C/C++ CI](https://github.com/arielfreire/asymmetric-cryptography/workflows/C/C++%20CI/badge.svg)
# Estudo de Criptografia Assimetrica

Trabalho da cadeira de Laboratório de Programação UERJ 2020.1

## O que é

O objetivo desse trabalho é fornecer um programa que gere chaves públicas e privadas a partir de dois numeros primos quaisquer, e de posse destas chaves seja capaz de criptografar uma mensagem fornecida como entrada e porsteriormente descriptografa-la.

## How to

Compilar os arquivos `cripto.c` e `geranum.c` utilizando o comando abaixo:

`gcc cripto.c -o cripto -lm -std=c99 -Wall -Werror -pedantic && gcc geranum.c -o geranum -lm -std=c99 -Wall -Werror -pedantic`

### geranum
O programa **geranum** recebe dois numeros primos como parametros de entrada.
Ex: 
`./geranum 13 17`

Como resposta serão gerados dois arquivos contendo a chave pública (numcripto.txt) e chave privada (numdescripto.txt).

### cripto

O programa **cripto** recebe duas oções:
- '-d' Descriptografa a mensagem fornecida como entrada.
- '-c' Criptografa a mensagem fornecida como entrada.
**Obs.:** Para que o programa possa ser executado, é necessário ter gerado antes as chaves de criptografia através de **geranum**
Ex:
`./cripto -c "67 101 108 97 99 97 110 116 111"`
