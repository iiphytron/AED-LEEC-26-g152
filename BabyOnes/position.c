#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
typedef struct {
    int id; // ID da cidade (1 a C)
    int x;  // Coordenada X (1 a X_max)
    int y;  // Coordenada Y (1 a Y_max)
} Posicao;

/*
    f_pos: Ponteiro do ficheiro .position já aberto para leitura
    C: Número total de cidades lido previamente do ficheiro .map
    Ponteiro para o vetor de Posicao (índices 1 a C) em caso de sucesso.
    Retorna NULL se existir qualquer erro de validação (ex.: coordenadas fora
    dos limites, cidades em falta ou duplicadas), permitindo sair sem output.
 */
Posicao *ler_e_validar_posicoes(FILE *f_pos, int C) {
    if (f_pos == NULL || C <= 0) {
        return NULL;
    }

    int X_max = 0, Y_max = 0;

    // dimensões máximas
    if (fscanf(f_pos, "%d %d", &X_max, &Y_max) != 2 || X_max <= 0 || Y_max <= 0) {
        return NULL; 
    }

    // Alocação dinâmica do vetor de posições (índices 1 a C)
    Posicao *cidades = (Posicao *) malloc((C + 1) * sizeof(Posicao));
    // Vetor de marcação para controlar duplicados e cidades em falta
    int *registada = (int *) calloc((C + 1), sizeof(int));

    if (cidades == NULL || registada == NULL) {
        if (cidades) free(cidades);
        if (registada) free(registada);
        return NULL;
    }

    int id_cidade = 0, x = 0, y = 0;
    int total_lidas = 0;

    // 2. Ler as posições linha a linha
    while (fscanf(f_pos, "%d %d %d", &id_cidade, &x, &y) == 3) {

        // Validação 1: ID da cidade fora do intervalo [1, C]
        if (id_cidade < 1 || id_cidade > C) {
            free(cidades); free(registada);
            return NULL;
        }

        // Validação 2: Cidade duplicada no ficheiro
        if (registada[id_cidade] == 1) {
            free(cidades); free(registada);
            return NULL;
        }

        // Validação 3: Coordenadas fora dos limites do plano [1, X_max] e [1, Y_max]
        if (x < 1 || x > X_max || y < 1 || y > Y_max) {
            free(cidades); free(registada);
            return NULL;
        }

        // Registo válido
        cidades[id_cidade].id = id_cidade;
        cidades[id_cidade].x  = x;
        cidades[id_cidade].y  = y;
        registada[id_cidade]  = 1;
        total_lidas++;
    }

    // Validação 4: Garantir que TODAS as C cidades foram registadas
    if (total_lidas != C) {
        free(cidades); free(registada);
        return NULL; // Faltam cidades no ficheiro .position
    }

    free(registada);
    return cidades;
}

/**
 * Aloca e calcula a matriz de distâncias Euclidianas D[C+1][C+1].
 * D[i][j] guardará a distância geométrica entre a cidade 'i' e a cidade 'j'.
 */
double **calcular_matriz_distancias(Posicao *cidades, int C) {
    if (cidades == NULL || C <= 0) {
        return NULL;
    }

    // Alocar a matriz D de ponteiros para ponteiros
    double **D = (double **) malloc((C + 1) * sizeof(double *));
    if (D == NULL) return NULL;

    for (int i = 1; i <= C; i++) {
        D[i] = (double *) malloc((C + 1) * sizeof(double));
        if (D[i] == NULL) {
            // Se falhar a alocação a meio, liberta o que já foi alocado
            for (int k = 1; k < i; k++) free(D[k]);
            free(D);
            return NULL;
        }
    }

    // Calcular a distância entre cada par de cidades (i, j)
    for (int i = 1; i <= C; i++) {
        for (int j = 1; j <= C; j++) {
            if (i == j) {
                D[i][j] = 0.0;
            } else {
                double dx = (double) (cidades[i].x - cidades[j].x);
                double dy = (double) (cidades[i].y - cidades[j].y);
                D[i][j] = sqrt(dx * dx + dy * dy); // Distância geométrica
            }
        }
    }

    return D;
}

/**
 * Liberta a memória alocada dinamicamente para a matriz de distâncias D.
 */
void libertar_matriz_distancias(double **D, int C) {
    if (D == NULL) return;
    for (int i = 1; i <= C; i++) {
        if (D[i] != NULL) {
            free(D[i]);
        }
    }
    free(D);
}
