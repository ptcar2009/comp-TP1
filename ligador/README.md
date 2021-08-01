# Compiladores - TP1

Pedro Tavares de Carvalho
Francisco Bonome Andrade

## Introdução

Para este trabalho foi proposta a contrução de um montador para uma máquina virtual, o qual deve receber como entrada instruções de um programa em Assembly, "traduzí-lo" e gerar como saída instruções na linguagem da máquina virtual.  

As intruções Assembly (operadores e operações) foram definidas na descrição do trabalho, assim como a quantidade de registradores de propósito geral (quatro) e os registradores de propósito específico (PC, AP e PEP), e também que o caractere ";" define o início de um comentário, o qual deve ser ignorado pelo montador.

## Desenvolvimento

O montador recebe como entrada um arquivo de texto no qual está descrito o programa em Assembly. Uma vez que o arquivo de entrada seja válido, itera-se uma primeira vez por cada linha do arquivo de forma a registrar cada um dos operadores em um vetor de strings, definir o espaço de memória para cada label (caso existam) e ignorar os comentários (também caso existam). Essa primeira passagem pelo código é finalizada quando o operador "END" é encontrado ou quando o final do arquivo é atingido.

Em seguida, é feita uma segunda passagem, dessa vez pelo vetor de strings gerado no passo anterior. Nessa etapa, os operadores e operandos são validados e, caso sejam válidos, são traduzidos para a linguagem da máquina virtual. Caso contrário, o programa é interrompido e um erro é logado ao usuário. Por fim, imprime-se na saída padrão o resultado obtido pelo montador, no formato especificado na descrição da máquina virtual.

A fim de realizar a "tradução" dos operadores e operandos para a linguagem de máquina durante a segunda passagem, foram utilizadas estruturas de mapa, as quais relacionam os operadores/operandos em seu formato de string com seu valor numérico que é entendido pela máquina virtual. Por exemplo:

- Registradores:

```cpp
{"R0", 0},
{"R1", 1},
{"R2", 2},
{"R3", 3},
```

- Operações:

```cpp
{"ADD", {8, {"R", "R"}}},
{"SUB", {9, {"R", "R"}}},
{"MUL", {10, {"R", "R"}}},
```

Além da implementação do montador, também foi criada uma estrutura que loga (registra) o passo-a-passo da execução do programa, relatando o que está sendo feito a cada etapa e explicitando algum eventual erro que venha a ocorrer.

## Conclusão

Após o término da implementação foram criados alguns programas em Assembly a fim de testar os programas gerados pelo montador. Foi fornecido um emulador o qual recebe as instruções geradas pelo montador e simula a execução da máquina virtual com base nas instruções.

Pequenos programas em Assembly foram criados para testar cada uma das instruções individualmente, e todos foram bem sucedidos. Além disso, foi implementado um dos testes sugeridos, o qual consiste em um programa que recebe cinco números inteiros positivos de entrada e retorna a mediana do conjunto. Esse programa, que contém diversos comentários e linhas em branco, também teve sua execução bem sucedida, e pode ser verificado [aqui](tst/median.txt).
