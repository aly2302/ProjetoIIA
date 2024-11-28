// hibrido.c

#include "hibrido.h"
#include "trepaColinas.h"
#include "evolutivo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void hibrido_iterativo(double *moedas, int n, double alvo) {
    Individuo populacao[TAMANHO_POPULACAO];
    inicializar_populacao(populacao, TAMANHO_POPULACAO, n, moedas, alvo);

    int iter_sem_melhoria = 0;
    int melhor_aptidao = avaliar_solucao_evolutivo(&populacao[0], moedas, alvo);

    for (int iter = 0; iter < MAX_ITERACOES && iter_sem_melhoria < 5; iter++) {
        for (int i = 0; i < TAMANHO_POPULACAO; i++) {
            trepa_colinas(moedas, n, alvo);
            populacao[i].aptidao = avaliar_solucao_evolutivo(&populacao[i], moedas, alvo);
        }

        Individuo *melhor_solucao_atual = &populacao[0];
        for (int i = 1; i < TAMANHO_POPULACAO; i++) {
            if (populacao[i].aptidao < melhor_solucao_atual->aptidao) {
                melhor_solucao_atual = &populacao[i];
            }
        }

        if (melhor_solucao_atual->aptidao < melhor_aptidao) {
            melhor_aptidao = melhor_solucao_atual->aptidao;
            iter_sem_melhoria = 0;
        } else {
            iter_sem_melhoria++;
        }
    }

    Individuo *melhor_solucao = &populacao[0];
    for (int i = 1; i < TAMANHO_POPULACAO; i++) {
        if (populacao[i].aptidao < melhor_solucao->aptidao) {
            melhor_solucao = &populacao[i];
        }
    }

    printf("Melhor solucao encontrada:\n");
    double soma = calcular_soma_evolutivo(melhor_solucao, moedas);
    for (int i = 0; i < melhor_solucao->tamanho; i++) {
        printf("Moeda %.2f: %d\n", moedas[i], melhor_solucao->solucao[i]);
    }
    printf("Valor total: %.2f\n", soma);
    printf("Custo final: %d\n", melhor_solucao->aptidao);

    for (int i = 0; i < TAMANHO_POPULACAO; i++) {
        free(populacao[i].solucao);
    }
}

void hibrido_pipelined(double *moedas, int n, double alvo) {
    Individuo populacao[TAMANHO_POPULACAO];
    inicializar_populacao(populacao, TAMANHO_POPULACAO, n, moedas, alvo);

    int iter_sem_melhoria = 0;
    int melhor_aptidao = avaliar_solucao_evolutivo(&populacao[0], moedas, alvo);

    for (int iter = 0; iter < MAX_ITERACOES && iter_sem_melhoria < 10; iter++) {
        for (int i = 0; i < TAMANHO_POPULACAO; i++) {
            trepa_colinas(moedas, n, alvo);
            populacao[i].aptidao = avaliar_solucao_evolutivo(&populacao[i], moedas, alvo);
        }
        algoritmo_evolutivo(moedas, n, alvo);

        Individuo *melhor_solucao_atual = &populacao[0];
        for (int i = 1; i < TAMANHO_POPULACAO; i++) {
            if (populacao[i].aptidao < melhor_solucao_atual->aptidao) {
                melhor_solucao_atual = &populacao[i];
            }
        }

        if (melhor_solucao_atual->aptidao < melhor_aptidao) {
            melhor_aptidao = melhor_solucao_atual->aptidao;
            iter_sem_melhoria = 0;
        } else {
            iter_sem_melhoria++;
        }
    }

    Individuo *melhor_solucao = &populacao[0];
    for (int i = 1; i < TAMANHO_POPULACAO; i++) {
        if (populacao[i].aptidao < melhor_solucao->aptidao) {
            melhor_solucao = &populacao[i];
        }
    }

    printf("Melhor solucao encontrada:\n");
    double soma = calcular_soma_evolutivo(melhor_solucao, moedas);
    for (int i = 0; i < melhor_solucao->tamanho; i++) {
        printf("Moeda %.2f: %d\n", moedas[i], melhor_solucao->solucao[i]);
    }
    printf("Valor total: %.2f\n", soma);
    printf("Custo final: %d\n", melhor_solucao->aptidao);

    for (int i = 0; i < TAMANHO_POPULACAO; i++) {
        free(populacao[i].solucao);
    }
}