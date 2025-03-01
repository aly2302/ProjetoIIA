#include "trepaColinas.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gerar_aleatorio(int min, int max) {
    return min + rand() % (max - min + 1);
}

void gerar_solucao_aleatoria_trepa(Solucao *s, double *moedas, double alvo) {
    double soma = 0.0;
    for (int i = 0; i < s->tamanho; i++) {
        s->solucao[i] = gerar_aleatorio(0, (int)(alvo / moedas[i]));
        soma += s->solucao[i] * moedas[i];
    }
    if (soma == 0) {
        int indice = gerar_aleatorio(0, s->tamanho - 1);
        s->solucao[indice] = 1;
    }
}

double calcular_soma_trepa(Solucao *s, double *moedas) {
    double soma = 0.0;
    for (int i = 0; i < s->tamanho; i++) {
        soma += s->solucao[i] * moedas[i];
    }
    return soma;
}

void reparar_solucao_trepa(Solucao *s, double *moedas, double alvo) {
    double soma = calcular_soma_trepa(s, moedas);
    for (int i = s->tamanho - 1; i >= 0 && soma > alvo; i--) {
        while (s->solucao[i] > 0 && soma - moedas[i] >= alvo) {
            s->solucao[i]--;
            soma -= moedas[i];
        }
    }
    for (int i = s->tamanho - 1; i >= 0 && soma < alvo; i--) {
        while (soma + moedas[i] <= alvo) {
            s->solucao[i]++;
            soma += moedas[i];
        }
    }
}

int avaliar_solucao_trepa(Solucao *s, double *moedas, double alvo) {
    reparar_solucao_trepa(s, moedas, alvo);
    int total_moedas = 0;
    for (int i = 0; i < s->tamanho; i++) {
        total_moedas += s->solucao[i];
    }
    return total_moedas;
}

void gerar_vizinho2(Solucao *atual, Solucao *vizinho, double *moedas, double alvo) {
    for (int i = 0; i < atual->tamanho; i++) {
        vizinho->solucao[i] = atual->solucao[i];
    }

    int indice1 = gerar_aleatorio(0, atual->tamanho - 1);
    int indice2 = gerar_aleatorio(0, atual->tamanho - 1);

    if (vizinho->solucao[indice1] > 0 && indice1 != indice2 && moedas[indice1] < moedas[indice2]) {
        vizinho->solucao[indice1]--;
        vizinho->solucao[indice2]++;
    }

    double soma = calcular_soma_trepa(vizinho, moedas);
    if (soma > alvo) {
        reparar_solucao_trepa(vizinho, moedas, alvo);
    }
}

void substituir_solucao(Solucao *destino, Solucao *origem) {
    for (int i = 0; i < origem->tamanho; i++) {
        destino->solucao[i] = origem->solucao[i];
    }
}

int trepa_colinas(double *moedas, int n, double alvo) {
    Solucao atual, vizinho;
    atual.tamanho = vizinho.tamanho = n;
    atual.solucao = malloc(n * sizeof(int));
    vizinho.solucao = malloc(n * sizeof(int));

    gerar_solucao_aleatoria_trepa(&atual, moedas, alvo);
    reparar_solucao_trepa(&atual, moedas, alvo);
    int custo_atual = avaliar_solucao_trepa(&atual, moedas, alvo);

    for (int i = 0; i < MAX_ITERACOES; i++) {
        gerar_vizinho2(&atual, &vizinho, moedas, alvo);
        int custo_vizinho = avaliar_solucao_trepa(&vizinho, moedas, alvo);

        double soma_atual = calcular_soma_trepa(&atual, moedas);
        double soma_vizinho = calcular_soma_trepa(&vizinho, moedas);

        if ((custo_vizinho < custo_atual && soma_vizinho <= alvo) ||
            (soma_vizinho <= alvo && fabs(soma_vizinho - alvo) < fabs(soma_atual - alvo) && custo_vizinho <= custo_atual)) {
            substituir_solucao(&atual, &vizinho);
            custo_atual = custo_vizinho;
        }
    }

    printf("Melhor solucao encontrada:\n");
    double soma = calcular_soma_trepa(&atual, moedas);
    for (int i = 0; i < atual.tamanho; i++) {
        printf("Moeda %.2f: %d\n", moedas[i], atual.solucao[i]);
    }
    printf("Valor total: %.2f\n", soma);
    printf("Custo final: %d\n", custo_atual);

    free(atual.solucao);
    free(vizinho.solucao);
    return custo_atual;
}