# Calculadora Orientada a Objetos em C++

Este projeto é uma **calculadora orientada a objetos**, desenvolvida como parte da disciplina **Análise e Projeto de Software (APS)** da **UTFPR-CM**. O objetivo principal foi implementar uma calculadora com as operações básicas de aritmética, utilizando conceitos de orientação a objetos em **C++**.

## Funcionalidades

A calculadora oferece as seguintes funcionalidades:

- **Soma**: Adição de dois números.
- **Subtração**: Subtração de dois números.
- **Multiplicação**: Multiplicação de dois números.
- **Divisão**: Divisão de dois números.
- **Potenciação**: Eleva um número à potência de outro.
- **Raiz Quadrada**: Calcula a raiz quadrada de um número.

### Descrição das Classes

  #### **`Display`**
- Responsável por exibir as informações na tela da calculadora.

#### **`Cpu`**
- Gerencia as operações matemáticas e a lógica de cálculo.

#### **`Keyboard`**
- Gerencia as teclas da calculadora e processa as entradas do usuário.

#### **`Key`**
- Representa uma tecla da calculadora, que pode ser um número, operação ou comando de memória.

#### **`Interfaces`**
- Arquivo que pode conter interfaces para classes como `Keyboard` e `Display`, permitindo maior flexibilidade.

## Como Usar

### Compilar o Projeto com Makefile

Este projeto utiliza um **Makefile** para facilitar o processo de compilação. Para compilar e executar o projeto, siga os passos abaixo.

1. **Certifique-se de que você tem o `make` instalado**. 

2. **Compilar o Projeto**

   Na raiz do diretório do projeto, execute o seguinte comando para compilar o código:

   ```bash
   make

  Após a compilação bem-sucedida, o programa será executado automaticamente
