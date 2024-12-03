#ifndef PROJETOIIA_EVOLUTIVO_H
#define PROJETOIIA_EVOLUTIVO_H

#include "trepaColinas.h"
#include <stdlib.h>

#define TAMANHO_POPULACAO 50
#define TAXA_RECOMBINACAO 0.7
#define TAXA_MUTACAO 0.1
#define NUM_GERACOES 1000

// Estrutura para representar uma solução
typedef struct {
    Solucao solucao;
    int fitness;
} Individuo;

// Funções para inicializar, avaliar e gerenciar a população
void inicializar_populacao(Individuo *populacao, int tamanho, double *moedas, int n, double alvo);
void avaliar_populacao(Individuo *populacao, int tamanho, double *moedas, double alvo);
int comparar_individuos(const void *a, const void *b);
void selecao_torneio(Individuo *populacao, Individuo *pais, int tamanho);
void recombinacao_uniforme(Individuo *pais, Individuo *filhos, int tamanho);
void mutacao(Individuo *populacao, int tamanho, double taxa_mutacao, double *moedas, double alvo);
void liberar_memoria_populacao(Individuo *populacao, int tamanho);

// Função principal do algoritmo evolutivo
void algoritmo_evolutivo(double *moedas, int n, double alvo);

#endif // PROJETOIIA_EVOLUTIVO_H
