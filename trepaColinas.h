#ifndef PROJETOIIA_TREPACOLINAS_H
#define PROJETOIIA_TREPACOLINAS_H

#define MAX_ITERACOES 1000
#define TOLERANCIA 1e-6

typedef struct {
    int *solucao;
    int tamanho;
} Solucao;

int gerar_aleatorio(int min, int max);
void gerar_solucao_aleatoria_trepa(Solucao *s, double *moedas, double alvo);
double calcular_soma_trepa(Solucao *s, double *moedas);
void reparar_solucao_trepa(Solucao *s, double *moedas, double alvo);
int avaliar_solucao_trepa(Solucao *s, double *moedas, double alvo);
void gerar_vizinho(Solucao *atual, Solucao *vizinho, double *moedas, double alvo);
void gerar_vizinho2(Solucao *atual, Solucao *vizinho, double *moedas, double alvo);
void substituir_solucao(Solucao *destino, Solucao *origem);
int trepa_colinas(double *moedas, int n, double alvo);

#endif //PROJETOIIA_TREPACOLINAS_H


