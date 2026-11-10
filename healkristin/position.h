#ifndef POSITION_H
#include <stdio.h>
#define POSITION_H

typedef struct {
    int id;
    int x;
    int y;
} 
Posicao;

Posicao *ler_e_validar_posicoes(FILE *f_pos, int C);


#endif // POSITION_H
