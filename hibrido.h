#ifndef PROJETOIIA_HIBRIDO_H
#define PROJETOIIA_HIBRIDO_H

#include "evolutivo.h"  // Inclui a estrutura Individuo e funções do algoritmo evolutivo
#include "trepaColinas.h" // Inclui funções relacionadas ao Trepa Colinas
#include <stdlib.h>
#include <stdio.h>

// Funções específicas do algoritmo híbrido
void inicializar_populacao_hibrida(Individuo *populacao, int tamanho, double *moedas, int n, double alvo);
void algoritmo_hibrido_1(double *moedas, int n, double alvo);
void algoritmo_hibrido_2(double *moedas, int n, double alvo);



#endif //PROJETOIIA_HIBRIDO_H
