#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>

int ler_ficheiro(const char *nome_ficheiro, double **moedas, double *alvo) {
    printf("A abrir o ficheiro: %s\n", nome_ficheiro);
    FILE *ficheiro = fopen(nome_ficheiro, "r");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro: %s\n", nome_ficheiro);
        printf("Caminho atual: %s\n", _getcwd(NULL, 0));
        return -1;
    }

    int n;
    fscanf(ficheiro, "%d %lf", &n, alvo);

    *moedas = malloc(n * sizeof(double));
    if (*moedas == NULL) {
        printf("Erro ao alocar memoria para as moedas.\n");
        fclose(ficheiro);
        return -1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(ficheiro, "%lf", &(*moedas)[i]);
    }

    fclose(ficheiro);
    return n;
}
