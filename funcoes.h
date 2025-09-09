#ifndef FUNCOESTP_H
#define FUNCOESTP_H

#include <stdlib.h> // Incluído para a definição de NULL, se necessário
#include <time.h>   // Incluído para a definição de time

void limparBuffer(char delimitador);
void liberarMatriz(int **matriz, int tamTabu);
void alocamatriz(int ***matriz, int tamTabu);
void matrizJogoPadrao(int tamTabu, int **matrizJogo);
void imprimirTabuleiro(int **matriz, int **matrizJogo, int tamTabu, int* vetLinha, int* vetColuna);
void criarMatAleatF(int **matriz, int **matrizResultado, int tamTabu, int* vetLinha, int* vetColuna);
int verificaSeGanhou(int** matrizJogo, int** matrizResultado, int tamTabu);
void jogabilidadeFacil(int **matriz, int **matrizResultado, int **matrizJogo, int tamTabu, int* vetLinha, int* vetColuna);
void continuarJogoSalvo(int tamTabu, int **matrizJogo, int **matriz, int **matrizResultado, int* vetLinha, int* vetColuna);

#endif