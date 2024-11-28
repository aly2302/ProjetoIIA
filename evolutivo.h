#ifndef PROJETOIIA_EVOLUTIVO_H
#define PROJETOIIA_EVOLUTIVO_H

#define MAX_ITERACOES 1000
#define TAMANHO_POPULACAO 50
#define TAXA_MUTACAO 0.1

typedef struct {
    int *solucao;
    int tamanho;
    int aptidao;
} Individuo;

int ler_ficheiro(const char *nome_ficheiro, double **moedas, double *alvo);
void gerar_solucao_aleatoria_evolutivo(Individuo *ind, double *moedas, double alvo);
double calcular_soma_evolutivo(Individuo *ind, double *moedas);
void reparar_solucao_evolutivo(Individuo *ind, double *moedas, double alvo);
int avaliar_solucao_evolutivo(Individuo *ind, double *moedas, double alvo);
void inicializar_populacao(Individuo *populacao, int tamanho_populacao, int n, double *moedas, double alvo);
void cruzamento(Individuo *pai1, Individuo *pai2, Individuo *filho, int n);
void cruzamento_uniforme(Individuo *pai1, Individuo *pai2, Individuo *filho, int n);
void mutacao(Individuo *ind, double *moedas, double alvo);
void mutacao_gaussiana(Individuo *ind, double *moedas, double alvo);
Individuo* selecao_torneio(Individuo *populacao, int tamanho_populacao);
Individuo* selecao_roleta(Individuo *populacao, int tamanho_populacao);
void algoritmo_evolutivo(double *moedas, int n, double alvo);

#endif //PROJETOIIA_EVOLUTIVO_H


