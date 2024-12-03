/* evolutivo.c */
#include "evolutivo.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void inicializar_populacao(Individuo *populacao, int tamanho, double *moedas, int n, double alvo) {
    for (int i = 0; i < tamanho; i++) {
        populacao[i].solucao.tamanho = n;
        populacao[i].solucao.solucao = malloc(n * sizeof(int));
        if (populacao[i].solucao.solucao == NULL) {
            printf("Erro ao alocar memoria para a solucao.\n");
            exit(EXIT_FAILURE);
        }
        gerar_solucao_aleatoria_trepa(&populacao[i].solucao, moedas, alvo);
        reparar_solucao_trepa(&populacao[i].solucao, moedas, alvo);
        populacao[i].fitness = avaliar_solucao_trepa(&populacao[i].solucao, moedas, alvo);
    }
}

void avaliar_populacao(Individuo *populacao, int tamanho, double *moedas, double alvo) {
    for (int i = 0; i < tamanho; i++) {
        double soma = calcular_soma_trepa(&populacao[i].solucao, moedas);
        int num_moedas = 0;
        for (int j = 0; j < populacao[i].solucao.tamanho; j++) {
            num_moedas += populacao[i].solucao.solucao[j];
        }

        // Penalizar soluções que excedem o valor-alvo e priorizar o menor número de moedas
        if (soma > alvo) {
            populacao[i].fitness = (int)((soma - alvo) * 100) + num_moedas * 10;
        } else if (soma < alvo) {
            populacao[i].fitness = (int)((alvo - soma) * 100) + num_moedas * 10;
        } else {
            populacao[i].fitness = num_moedas; // Solução válida com menor número de moedas
        }
    }
}

int comparar_individuos(const void *a, const void *b) {
    return ((Individuo *)a)->fitness - ((Individuo *)b)->fitness;
}

void selecao_torneio(Individuo *populacao, Individuo *pais, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        int indice1 = rand() % tamanho;
        int indice2 = rand() % tamanho;
        if (populacao[indice1].fitness < populacao[indice2].fitness) {
            pais[i] = populacao[indice1];
        } else {
            pais[i] = populacao[indice2];
        }
    }
}

void recombinacao_uniforme(Individuo *pais, Individuo *filhos, int tamanho) {
    for (int i = 0; i < tamanho; i += 2) {
        Individuo *filho1 = &filhos[i];
        Individuo *filho2 = &filhos[i + 1];
        filho1->solucao.tamanho = pais[i].solucao.tamanho;
        filho2->solucao.tamanho = pais[i + 1].solucao.tamanho;
        filho1->solucao.solucao = malloc(filho1->solucao.tamanho * sizeof(int));
        filho2->solucao.solucao = malloc(filho2->solucao.tamanho * sizeof(int));
        if (filho1->solucao.solucao == NULL || filho2->solucao.solucao == NULL) {
            printf("Erro ao alocar memoria para a solucao dos filhos.\n");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < pais[i].solucao.tamanho; j++) {
            if (rand() % 2 == 0) {
                filho1->solucao.solucao[j] = pais[i].solucao.solucao[j];
                filho2->solucao.solucao[j] = pais[i + 1].solucao.solucao[j];
            } else {
                filho1->solucao.solucao[j] = pais[i + 1].solucao.solucao[j];
                filho2->solucao.solucao[j] = pais[i].solucao.solucao[j];
            }
        }
    }
}

void mutacao(Individuo *populacao, int tamanho, double taxa_mutacao, double *moedas, double alvo) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < populacao[i].solucao.tamanho; j++) {
            if (((double)rand() / RAND_MAX) < taxa_mutacao) {
                // Aumentar ou diminuir a quantidade da moeda, respeitando os limites
                int mudanca = gerar_aleatorio(-1, 1);
                populacao[i].solucao.solucao[j] += mudanca;
                if (populacao[i].solucao.solucao[j] < 0) {
                    populacao[i].solucao.solucao[j] = 0;
                }
            }
        }
        reparar_solucao_trepa(&populacao[i].solucao, moedas, alvo);
    }
}

void liberar_memoria_populacao(Individuo *populacao, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        free(populacao[i].solucao.solucao);
    }
}

void algoritmo_evolutivo(double *moedas, int n, double alvo) {
    Individuo populacao[TAMANHO_POPULACAO];
    Individuo pais[TAMANHO_POPULACAO];
    Individuo filhos[TAMANHO_POPULACAO];

    inicializar_populacao(populacao, TAMANHO_POPULACAO, moedas, n, alvo);

    for (int geracao = 0; geracao < NUM_GERACOES; geracao++) {
        selecao_torneio(populacao, pais, TAMANHO_POPULACAO);
        recombinacao_uniforme(pais, filhos, TAMANHO_POPULACAO);
        mutacao(filhos, TAMANHO_POPULACAO, TAXA_MUTACAO, moedas, alvo);
        avaliar_populacao(filhos, TAMANHO_POPULACAO, moedas, alvo);

        qsort(filhos, TAMANHO_POPULACAO, sizeof(Individuo), comparar_individuos);
        qsort(populacao, TAMANHO_POPULACAO, sizeof(Individuo), comparar_individuos);

        for (int i = 0; i < TAMANHO_POPULACAO / 2; i++) {
            free(populacao[TAMANHO_POPULACAO - 1 - i].solucao.solucao);
            populacao[TAMANHO_POPULACAO - 1 - i] = filhos[i];
        }
    }

    Individuo melhor = populacao[0];
    printf("Melhor solucao encontrada:\n");
    double soma = calcular_soma_trepa(&melhor.solucao, moedas);
    for (int i = 0; i < melhor.solucao.tamanho; i++) {
        printf("Moeda %.2f: %d\n", moedas[i], melhor.solucao.solucao[i]);
    }
    printf("Valor total: %.2f\n", soma);
    printf("Custo final: %d\n", melhor.fitness);

    liberar_memoria_populacao(populacao, TAMANHO_POPULACAO);
}
