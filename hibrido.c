#include "hibrido.h"
#include "evolutivo.h"
#include "trepaColinas.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void inicializar_populacao_hibrida(Individuo *populacao, int tamanho, double *moedas, int n, double alvo) {
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

void algoritmo_hibrido_1(double *moedas, int n, double alvo) {
    // Abordagem Híbrida 1: Aplicar Evolutivo e, em cada N gerações, usar Trepa Colinas na melhor solução
    Individuo populacao[TAMANHO_POPULACAO];
    Individuo pais[TAMANHO_POPULACAO];
    Individuo filhos[TAMANHO_POPULACAO];

    inicializar_populacao_hibrida(populacao, TAMANHO_POPULACAO, moedas, n, alvo);

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

        // A cada 50 gerações, aplicar Trepa Colinas na melhor solução
        if (geracao % 50 == 0) {
            trepa_colinas(moedas, n, alvo);
        }
    }

    Individuo melhor = populacao[0];
    printf("Melhor solucao encontrada (Híbrido 1):\n");
    double soma = calcular_soma_trepa(&melhor.solucao, moedas);
    for (int i = 0; i < melhor.solucao.tamanho; i++) {
        printf("Moeda %.2f: %d\n", moedas[i], melhor.solucao.solucao[i]);
    }
    printf("Valor total: %.2f\n", soma);
    printf("Custo final: %d\n", melhor.fitness);

    libertar_memoria_populacao(populacao, TAMANHO_POPULACAO);
}

void algoritmo_hibrido_2(double *moedas, int n, double alvo) {
    // Abordagem Híbrida 2 Simplificada: Aplicar Trepa Colinas apenas uma vez por geração na melhor solução
    Individuo populacao[TAMANHO_POPULACAO];
    Individuo pais[TAMANHO_POPULACAO];
    Individuo filhos[TAMANHO_POPULACAO];

    inicializar_populacao_hibrida(populacao, TAMANHO_POPULACAO, moedas, n, alvo);

    for (int geracao = 0; geracao < NUM_GERACOES; geracao++) {
        selecao_torneio(populacao, pais, TAMANHO_POPULACAO);
        recombinacao_uniforme(pais, filhos, TAMANHO_POPULACAO);
        mutacao(filhos, TAMANHO_POPULACAO, TAXA_MUTACAO, moedas, alvo);
        avaliar_populacao(filhos, TAMANHO_POPULACAO, moedas, alvo);

        qsort(filhos, TAMANHO_POPULACAO, sizeof(Individuo), comparar_individuos);
        qsort(populacao, TAMANHO_POPULACAO, sizeof(Individuo), comparar_individuos);

        // Aplicar Trepa Colinas na melhor solução apenas uma vez por geração
        trepa_colinas(moedas, n, alvo);

        for (int i = 0; i < TAMANHO_POPULACAO / 2; i++) {
            free(populacao[TAMANHO_POPULACAO - 1 - i].solucao.solucao);
            populacao[TAMANHO_POPULACAO - 1 - i] = filhos[i];
        }
    }

    Individuo melhor = populacao[0];
    printf("Melhor solucao encontrada (Híbrido 2 Simplificado):\n");
    double soma = calcular_soma_trepa(&melhor.solucao, moedas);
    for (int i = 0; i < melhor.solucao.tamanho; i++) {
        printf("Moeda %.2f: %d\n", moedas[i], melhor.solucao.solucao[i]);
    }
    printf("Valor total: %.2f\n", soma);
    printf("Custo final: %d\n", melhor.fitness);

    libertar_memoria_populacao(populacao, TAMANHO_POPULACAO);
}
