#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>



/*
  Une os clusters das cidades A e B usando Quick-Find.
 */
void estrutura_para_ler(int id[], int C, int A, int B)
{
    int valorA = id[A];
    int valorB = id[B];
    int i;

    /*
     * Se A e B já pertencem ao mesmo cluster,
     * não é necessário alterar nada.
     */
    if (valorA == valorB) {
        return;
    }

    /*
     * Todas as cidades que pertenciam ao cluster
     * de A passam para o cluster de B.
     */
    for (i = 1; i <= C; i++) {

        if (id[i] == valorA) {
            id[i] = valorB;
        }
    }
}
void ler_C_L(int C, int L){



    FILE *f_map = fopen(".map", "r");



    if (f_map == NULL) {
        perror("fopen");
        return;
    }


    /*
     * C = número de cidades
     * L = número de ligações
     1. LER A PRIMEIRA LINHA*/

    if (fscanf(f_map, "%d %d", &C, &L) == 2) {
    }
    else {

        printf("Erro ao ler a primeira linha do ficheiro map.\n");

        fclose(f_map);

        return;
    }
}
