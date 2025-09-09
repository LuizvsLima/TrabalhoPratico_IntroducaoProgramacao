#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cores.h"
#define TAM 100



//função libera matriz
void liberarMatriz(int **matriz, int tamTabu){
    for (int i = 0; i < tamTabu; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

//função para limparbuffer do scanf de nome
void limparBuffer(char delimitador) {
    int c;
    while ((c = getchar()) != delimitador && c != EOF);
}

// Alterei o tipo da matriz para int
void alocamatriz(int ***matriz, int tamTabu) {
    *matriz = malloc(tamTabu * sizeof(int*));
    if (*matriz == NULL) {
        // Trata erro de alocação de memória
        printf("Erro ao alocar memória para as linhas da matriz.\n");
        exit(1);
    }
    for (int i = 0; i < tamTabu; i++) {
        (*matriz)[i] = malloc(tamTabu * sizeof(int));
        if ((*matriz)[i] == NULL) {
            // Trata erro de alocação de memória
            printf("Erro ao alocar memória para as colunas da matriz.\n");
            exit(1);
        }
    }
}

// Agora usa a mesma sintaxe de ponteiro do funcoes.h
void criarMatAleatF(int **matriz, int **matrizResultado, int tamTabu, int* vetLinha, int* vetColuna) {
    // CRIA MATRIZ ALEATORIO DE 1 A 9
    for (int i = 0; i < tamTabu; i++) {
        for (int j = 0; j < tamTabu; j++) {
            int numAleatMat = rand() % 9 + 1;
            matriz[i][j] = numAleatMat;
            matrizResultado[i][j] = 1; // Atribui 1 para indicar que o número deve ser mantido
        }
    }

    // REMOVENDO NÚMEROS DA MATRIZ ORIGINAL
    for(int i = 0; i < tamTabu; i++){
        for(int j = 0; j < tamTabu; j++){
            int possibilidades = rand() % 100;
            if(possibilidades < 50){
                matrizResultado[i][j] = 0; // Marca a posição para ser removida
            }
        }
    }

    // SOMA DE LINHAS E COLUNAS DA MATRIZ
    for (int i = 0; i < tamTabu; i++) {
        vetLinha[i] = 0;
        vetColuna[i] = 0;
        for (int j = 0; j < tamTabu; j++) {
            // Apenas soma os números que não foram removidos (matrizResultado[i][j] == 1)
            if (matrizResultado[i][j] == 1) {
                vetLinha[i] += matriz[i][j];
            }
            // Soma as colunas
            if (matrizResultado[j][i] == 1) {
                vetColuna[i] += matriz[j][i];
            }
        }
    }
}

//FUNÇÃO VERIFICA VITORIA
// A lógica foi simplificada para comparar as matrizes de jogo e de resultado
int verificaSeGanhou(int** matrizJogo, int** matrizResultado, int tamTabu){
  for(int i = 0; i < tamTabu; i++){
    for(int j = 0; j < tamTabu; j++){
      if(matrizJogo[i][j] != matrizResultado[i][j]){
        return 0; // Perdeu
      }
    }
  }
  return 1; // Ganhou
}

// Agora usa a mesma sintaxe de ponteiro do funcoes.h
void imprimirTabuleiro(int **matriz, int **matrizJogo, int tamTabu, int* vetLinha, int* vetColuna) {
    printf("\n");
    for (int i = 0; i < tamTabu; i++) {
        for (int j = 0; j < tamTabu; j++) {
            if (matrizJogo[i][j] == 0) {
                printf(RED("  x ")); // 'x' para indicar remoção
            } else {
                printf(GREEN("%2d "), matriz[i][j]);
            }
        }
        printf(" | %d\n", vetLinha[i]);
    }
    
    for(int i = 0; i < tamTabu; i++){
        printf("----");
    }
    printf("\n");
    for(int i = 0; i< tamTabu; i++){
        printf("%2d ", vetColuna[i]);
    }
    printf("\n\n");
}


// Agora usa a mesma sintaxe de ponteiro do funcoes.h
void jogabilidadeFacil(int **matriz, int **matrizResultado, int **matrizJogo, int tamTabu, int* vetLinha, int* vetColuna){
    int escolhaL, escolhaC; // escolha das posicoes do usuario
    char opcaoColocacao[100]; // armazena palavras ''manter'' ''remover''
    int tempoInic = time(NULL);
    int ganhou = 0;
    
    imprimirTabuleiro(matriz, matrizJogo, tamTabu, vetLinha, vetColuna);

    while (!ganhou) {
        printf("Digite o comando (remover L C, manter L C, salvar, resolver, dica): ");
        scanf("%s", opcaoColocacao);

        if (strcmp(opcaoColocacao, "salvar") == 0) {
            printf("Digite o nome do arquivo que você quer salvar o jogo: ");
            char salvaJogo[100];
            scanf("%s", salvaJogo);
            FILE *arquivo = fopen(salvaJogo, "w");
            if (arquivo == NULL) {
                printf("Erro ao criar arquivo!\n");
                continue;
            }
            fprintf(arquivo, "%d\n", tamTabu);
            for (int i = 0; i < tamTabu; i++) {
                fprintf(arquivo, "%d ", vetLinha[i]);
            }
            fprintf(arquivo, "\n");
            for (int i = 0; i < tamTabu; i++) {
                fprintf(arquivo, "%d ", vetColuna[i]);
            }
            fprintf(arquivo, "\n");
            for (int i = 0; i < tamTabu; i++) {
                for (int j = 0; j < tamTabu; j++) {
                    fprintf(arquivo, "%d %d %d ", matriz[i][j], matrizResultado[i][j], matrizJogo[i][j]);
                }
            }
            fclose(arquivo);
            printf("Jogo salvo com sucesso!\n");
        } else if (strcmp(opcaoColocacao, "resolver") == 0) {
            for (int i = 0; i < tamTabu; i++) {
                for (int j = 0; j < tamTabu; j++) {
                    matrizJogo[i][j] = matrizResultado[i][j];
                }
            }
            printf("Tabuleiro resolvido:\n");
        } else if (strcmp(opcaoColocacao, "dica") == 0) {
            // Lógica de dica melhorada: mostra a primeira célula incorreta
            int dicaEncontrada = 0;
            for (int i = 0; i < tamTabu; i++) {
                for (int j = 0; j < tamTabu; j++) {
                    if (matrizJogo[i][j] != matrizResultado[i][j]) {
                        printf(YELLOW("Dica: a célula na linha %d, coluna %d está incorreta.\n"), i, j);
                        dicaEncontrada = 1;
                        break;
                    }
                }
                if (dicaEncontrada) {
                    break;
                }
            }
        } else if (strcmp(opcaoColocacao, "manter") == 0 || strcmp(opcaoColocacao, "remover") == 0) {
            scanf("%d %d", &escolhaL, &escolhaC);
            // Verifica se as coordenadas estão dentro dos limites
            if (escolhaL >= 0 && escolhaL < tamTabu && escolhaC >= 0 && escolhaC < tamTabu) {
                if (strcmp(opcaoColocacao, "manter") == 0) {
                    matrizJogo[escolhaL][escolhaC] = 1; // A coordenada escolhida para manter vira 1
                } else { // remover
                    matrizJogo[escolhaL][escolhaC] = 0; // A coordenada escolhida para remover vira 0
                }
            } else {
                printf(RED("Coordenadas inválidas. Digite valores entre 0 e %d.\n"), tamTabu - 1);
            }
        } else {
            printf(RED("Comando inválido. Tente novamente.\n"));
        }
        
        imprimirTabuleiro(matriz, matrizJogo, tamTabu, vetLinha, vetColuna);

        ganhou = verificaSeGanhou(matrizJogo, matrizResultado, tamTabu);
    }
    
    if (ganhou == 1) {
        printf("Você ganhou!\n");
        int tempoFin = time(NULL);
        int tempoGasto = tempoFin - tempoInic;
        printf("Tempo gasto = %d segundos\n", tempoGasto);
    }
}


//colocando matriz jogo 
// 1 (manter) ou 0 (remover)
void matrizJogoPadrao(int tamTabu, int **matrizJogo){
    for(int i=0;i<tamTabu;i++){
        for(int j=0;j<tamTabu;j++){
            matrizJogo[i][j] = 1;
        }
    }
}

// Agora usa a mesma sintaxe de ponteiro do funcoes.h
void continuarJogoSalvo(int tamTabu, int **matrizJogo, int **matriz, int **matrizResultado, int* vetLinha, int* vetColuna){
    char nomeArqNov[100];
    printf("Digite o nome do arquivo que seu jogo está salvo: ");
    scanf("%s", nomeArqNov);
    FILE *arquivo = fopen(nomeArqNov, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo. Verifique o nome.\n");
        return;
    }
    fscanf(arquivo, "%d", &tamTabu);
    for (int i = 0; i < tamTabu; i++) {
        fscanf(arquivo, "%d", &vetLinha[i]);
    }
    for (int i = 0; i < tamTabu; i++) {
        fscanf(arquivo, "%d", &vetColuna[i]);
    }
    for (int i = 0; i < tamTabu; i++) {
        for (int j = 0; j < tamTabu; j++) {
            fscanf(arquivo, "%d %d %d", &matriz[i][j], &matrizResultado[i][j], &matrizJogo[i][j]);
        }
    }
    fclose(arquivo);
    jogabilidadeFacil(matriz, matrizResultado, matrizJogo, tamTabu, vetLinha, vetColuna);
}