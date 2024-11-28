#include "trepaColinas.h"
#include "evolutivo.h"
#include "hibrido.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utils.h"

int main() {
    char nome_ficheiro[300];
    double *moedas, alvo;
    int n;
    int escolha;
    char continuar;

    do {
        printf("Insira o nome do ficheiro: ");
        fgets(nome_ficheiro, sizeof(nome_ficheiro), stdin);
        nome_ficheiro[strcspn(nome_ficheiro, "\n")] = '\0';

        n = ler_ficheiro(nome_ficheiro, &moedas, &alvo);
        if (n <= 0) {
            printf("Erro ao processar o ficheiro.\n");
            return 1;
        }

        srand((unsigned)time(NULL));

        printf("Escolha o algoritmo a executar:\n");
        printf("1 - Trepa Colinas\n");
        printf("2 - Algoritmo Evolutivo\n");
        printf("3 - Hibrido Iterativo\n");
        printf("4 - Hibrido Pipelined\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
        getchar(); // Limpar o buffer do teclado

        if (escolha == 1) {
            trepa_colinas(moedas, n, alvo);
        } else if (escolha == 2) {
            algoritmo_evolutivo(moedas, n, alvo);
        } else if (escolha == 3) {
            hibrido_iterativo(moedas, n, alvo);
        } else if (escolha == 4) {
            hibrido_pipelined(moedas, n, alvo);
        } else {
            printf("Escolha invalida.\n");
        }

        free(moedas);

        printf("Deseja realizar outra operacao? (s/n): ");
        scanf(" %c", &continuar);
        getchar(); // Limpar o buffer do teclado

    } while (continuar == 's' || continuar == 'S');

    return 0;
}