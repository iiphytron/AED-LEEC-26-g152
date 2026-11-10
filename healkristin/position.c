#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "position.h"



Posicao *ler_e_validar_posicoes(FILE *f_pos, int C) {
    if (f_pos == NULL || C <= 0) {
        return NULL;
    }

    int X_max = 0, Y_max = 0;

    // 1. Ler o cabeçalho (dimensões máximas permitidas para o plano)
    if (fscanf(f_pos, "%d %d", &X_max, &Y_max) != 2 || X_max <= 0 || Y_max <= 0) {
        return NULL; // Dimensões do plano inválidas
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