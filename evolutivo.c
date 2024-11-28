// evolutivo.c

#include "evolutivo.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

void gerar_solucao_aleatoria_evolutivo(Individuo *ind, double *moedas, double alvo) {
    double soma = 0.0;
    for (int i = 0; i < ind->tamanho; i++) {
        ind->solucao[i] = rand() % ((int)(alvo / moedas[i]) + 1);
        soma += ind->solucao[i] * moedas[i];
    }
    // Garantir que a soma não é zero
    if (soma == 0) {
        int indice = rand() % ind->tamanho;
        ind->solucao[indice] = 1;
    }
}

double calcular_soma_evolutivo(Individuo *ind, double *moedas) {
    double soma = 0.0;
    for (int i = 0; i < ind->tamanho; i++) {
        soma += ind->solucao[i] * moedas[i];
    }
    return soma;
}

void reparar_solucao_evolutivo(Individuo *ind, double *moedas, double alvo) {
    double soma = calcular_soma_evolutivo(ind, moedas);
    for (int i = ind->tamanho - 1; i >= 0 && soma > alvo; i--) {
        while (ind->solucao[i] > 0 && soma - moedas[i] >= alvo) {
            ind->solucao[i]--;
            soma -= moedas[i];
        }
    }
    // Ajuste para garantir que a soma é próxima do alvo
    for (int i = 0; i < ind->tamanho && soma < alvo; i++) {
        while (soma + moedas[i] <= alvo) {
            ind->solucao[i]++;
            soma += moedas[i];
        }
    }
}

int avaliar_solucao_evolutivo(Individuo *ind, double *moedas, double alvo) {
    reparar_solucao_evolutivo(ind, moedas, alvo);
    int total_moedas = 0;
    for (int i = 0; i < ind->tamanho; i++) {
        total_moedas += ind->solucao[i];
    }
    return total_moedas;
}

void inicializar_populacao(Individuo *populacao, int tamanho_populacao, int n, double *moedas, double alvo) {
    for (int i = 0; i < tamanho_populacao; i++) {
        populacao[i].tamanho = n;
        populacao[i].solucao = malloc(n * sizeof(int));
        gerar_solucao_aleatoria_evolutivo(&populacao[i], moedas, alvo);
        populacao[i].aptidao = avaliar_solucao_evolutivo(&populacao[i], moedas, alvo);
    }
}

void cruzamento(Individuo *pai1, Individuo *pai2, Individuo *filho, int n) {
    filho->tamanho = n;
    filho->solucao = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        filho->solucao[i] = (i < n / 2) ? pai1->solucao[i] : pai2->solucao[i];
    }
}

void cruzamento_uniforme(Individuo *pai1, Individuo *pai2, Individuo *filho, int n) {
    filho->tamanho = n;
    filho->solucao = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        filho->solucao[i] = (rand() % 2 == 0) ? pai1->solucao[i] : pai2->solucao[i];
    }
}

void mutacao(Individuo *ind, double *moedas, double alvo) {
    for (int i = 0; i < ind->tamanho; i++) {
        if (((double)rand() / RAND_MAX) < TAXA_MUTACAO) {
            int nova_quantidade = rand() % ((int)(alvo / moedas[i]) + 1);
            ind->solucao[i] = (nova_quantidade > 0) ? nova_quantidade : 1; // Garante que não seja zero
        }
    }
}

void mutacao_gaussiana(Individuo *ind, double *moedas, double alvo) {
    for (int i = 0; i < ind->tamanho; i++) {
        if (((double)rand() / RAND_MAX) < TAXA_MUTACAO) {
            int variacao = (int)(rand() % 3 - 1); // Valor entre -1 e 1
            if (ind->solucao[i] + variacao >= 0) {
                ind->solucao[i] += variacao;
            }
        }
    }
}

Individuo* selecao_torneio(Individuo *populacao, int tamanho_populacao) {
    int i1 = rand() % tamanho_populacao;
    int i2 = rand() % tamanho_populacao;
    return (populacao[i1].aptidao < populacao[i2].aptidao) ? &populacao[i1] : &populacao[i2];
}

Individuo* selecao_roleta(Individuo *populacao, int tamanho_populacao) {
    int soma_aptidoes = 0;
    for (int i = 0; i < tamanho_populacao; i++) {
        soma_aptidoes += populacao[i].aptidao;
    }
    int limite = rand() % soma_aptidoes;
    int soma_parcial = 0;
    for (int i = 0; i < tamanho_populacao; i++) {
        soma_parcial += populacao[i].aptidao;
        if (soma_parcial >= limite) {
            return &populacao[i];
        }
    }
    return &populacao[tamanho_populacao - 1];
}

void algoritmo_evolutivo(double *moedas, int n, double alvo) {
    Individuo populacao[TAMANHO_POPULACAO];
    inicializar_populacao(populacao, TAMANHO_POPULACAO, n, moedas, alvo);

    for (int iter = 0; iter < MAX_ITERACOES; iter++) {
        Individuo nova_populacao[TAMANHO_POPULACAO];
        for (int i = 0; i < TAMANHO_POPULACAO; i++) {
            Individuo *pai1 = selecao_torneio(populacao, TAMANHO_POPULACAO);
            Individuo *pai2 = selecao_roleta(populacao, TAMANHO_POPULACAO);
            cruzamento_uniforme(pai1, pai2, &nova_populacao[i], n);
            mutacao_gaussiana(&nova_populacao[i], moedas, alvo);
            nova_populacao[i].aptidao = avaliar_solucao_evolutivo(&nova_populacao[i], moedas, alvo);
        }
        for (int i = 0; i < TAMANHO_POPULACAO; i++) {
            free(populacao[i].solucao);
            populacao[i] = nova_populacao[i];
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
