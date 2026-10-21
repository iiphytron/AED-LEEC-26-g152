#define POSITION_H
#include <stdio.h>

typedef struct {
    int id;
    int x;
    int y;
} 
Posicao;

Posicao *ler_e_validar_posicoes(FILE *f_pos, int C);
double **calcular_matriz_distancias(Posicao *cidades, int C);
void libertar_matriz_distancias(double **D, int C);

#endif // POSITION_H
