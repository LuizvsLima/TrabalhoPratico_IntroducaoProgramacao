#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cores.h"
#include "funcoes.h"

#define TAM 100

int main() {
    int **matriz, **matrizResultado, **matrizJogo;
    int opcao;
    int tamTabu = 0; // Inicializado para evitar valor lixo
    char dificuldade;
    char nome[100];
    int vetLinha[TAM], vetColuna[TAM];
    
    srand(time(NULL));
    
    // Loop principal para o menu
    do {
        printf("Bem vindo ao jogo sumplete!!\nEscolha suas opções\n");
        printf("0 - Sair\n1 - Começar Novo Jogo\n2 - Continuar Jogo Salvo\n"); // Opções 3 e 4 removidas pois não estão implementadas
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer('\n');

        switch (opcao) {
            case 0:
                printf("Saindo do jogo...\n");
                // A memória é liberada no final do jogo, não é necessário aqui,
                // já que o programa será encerrado.
                return 0;
            
            case 1:
                printf("Digite seu nome:");
                scanf("%s", nome);
                printf("Digite o tamanho do tabuleiro:");
                scanf("%d", &tamTabu);
                limparBuffer('\n');
                
                // Alocação das matrizes
                alocamatriz(&matriz, tamTabu);
                alocamatriz(&matrizResultado, tamTabu);
                alocamatriz(&matrizJogo, tamTabu);
                
                matrizJogoPadrao(tamTabu, matrizJogo);

                printf("Digite a dificuldade do jogo ('f' para facil):");
                scanf(" %c", &dificuldade); // Espaço antes de %c para consumir o newline
                limparBuffer('\n');
                
                if (dificuldade == 'f') {
                    criarMatAleatF(matriz, matrizResultado, tamTabu, vetLinha, vetColuna);
                    printf("\n%s, digite o comando:\n", nome);
                    jogabilidadeFacil(matriz, matrizResultado, matrizJogo, tamTabu, vetLinha, vetColuna);
                    
                    liberarMatriz(matriz, tamTabu);
                    liberarMatriz(matrizJogo, tamTabu);
                    liberarMatriz(matrizResultado, tamTabu);
                } else {
                    printf("Opção de dificuldade inválida.\n");
                }
                break;
            
            case 2:
                // Implementação da opção 2
                // A alocação da matriz precisa ser feita antes de carregar o jogo
                printf("Carregando jogo salvo...\n");
                // Note que aqui a variável tamTabu será atualizada pela função.
                // Não é necessário ler o tamanho antes.
                alocamatriz(&matriz, 1); // Aloca com tamanho temporário
                alocamatriz(&matrizResultado, 1);
                alocamatriz(&matrizJogo, 1);
                
                continuarJogoSalvo(tamTabu, matrizJogo, matriz, matrizResultado, vetLinha, vetColuna);
                break;
                
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}