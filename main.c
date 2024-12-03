#include "trepaColinas.h"
#include "evolutivo.h"
#include "hibrido.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
    char nome_ficheiro[300];
    double *moedas, alvo;
    int n;
    int escolha;
    char continuar;

    do {
        // Solicitar o nome do ficheiro
        printf("Insira o nome do ficheiro: ");
        fgets(nome_ficheiro, sizeof(nome_ficheiro), stdin);
        nome_ficheiro[strcspn(nome_ficheiro, "\n")] = '\0';

        // Processar o ficheiro
        n = ler_ficheiro(nome_ficheiro, &moedas, &alvo);
        if (n <= 0) {
            printf("Erro ao processar o ficheiro.\n");
            continue;
        }

        // Inicializar o gerador de números aleatórios
        srand((unsigned)time(NULL));

        // Menu de seleção de algoritmos
        printf("Escolha o algoritmo a executar:\n");
        printf("1 - Trepa Colinas\n");
        printf("2 - Algoritmo Evolutivo\n");
        printf("3 - Algoritmo Hibrido 1\n");
        printf("4 - Algoritmo Hibrido 2\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
        getchar(); // Limpar o buffer do teclado

        // Executar o algoritmo selecionado
        switch (escolha) {
            case 1:
                printf("\nExecutando Trepa Colinas...\n");
                trepa_colinas(moedas, n, alvo);
                break;
            case 2:
                printf("\nExecutando Algoritmo Evolutivo...\n");
                algoritmo_evolutivo(moedas, n, alvo);
                break;
            case 3:
                printf("\nExecutando Algoritmo Hibrido 1...\n");
                algoritmo_hibrido_1(moedas, n, alvo);
                break;
            case 4:
                printf("\nExecutando Algoritmo Hibrido 2...\n");
                algoritmo_hibrido_2(moedas, n, alvo);
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção de 1 a 4.\n");
                break;
        }

        // Liberar memória alocada para as moedas
        free(moedas);

        // Perguntar ao usuário se deseja repetir
        printf("\nDeseja executar novamente? (s/n): ");
        scanf(" %c", &continuar);
        getchar(); // Limpar o buffer do teclado

    } while (continuar == 's' || continuar == 'S');

    printf("Programa encerrado.\n");
    return 0;
}
