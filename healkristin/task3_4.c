#include <float.h>
#include "Task3Task4.h"

static int cluster_da_cidade(int cidade, const Rede *rede)
{
    if (rede == NULL || cidade < 1 || cidade > rede->C)
        return -1;

    for (int k = 0; k < rede->num_clusters; k++) {
        for (int j = 0; j < rede->cluster_sizes[k]; j++) {
            if (rede->clusters[k][j] == cidade)
                return k;
        }
    }

    return -1;
}

static double distancia2(int a, int b,
                         const Posicao *cidades)
{
    double dx = (double)cidades[a].x - cidades[b].x;
    double dy = (double)cidades[a].y - cidades[b].y;

    return dx * dx + dy * dy;
}

int Task3(int referencia, const Rede *rede,
          const Posicao *cidades)
{
    if (rede == NULL || cidades == NULL ||
        referencia < 1 || referencia > rede->C ||
        rede->num_clusters <= 1)
        return -2;

    int kref = cluster_da_cidade(referencia, rede);

    if (kref < 0)
        return -2;

    int melhor = -1;
    double melhor_d2 = DBL_MAX;

    for (int cidade = 1; cidade <= rede->C; cidade++) {
        if (cluster_da_cidade(cidade, rede) == kref)
            continue;

        double d2 = distancia2(referencia, cidade, cidades);

        if (d2 < melhor_d2) {
            melhor_d2 = d2;
            melhor = cidade;
        }
    }

    return melhor < 0 ? -2 : melhor;
}

int Task4(int referencia, const Rede *rede,
          const Posicao *cidades)
{
    if (rede == NULL || cidades == NULL ||
        referencia < 1 || referencia > rede->C ||
        rede->num_clusters <= 1)
        return -2;

    int kref = cluster_da_cidade(referencia, rede);

    if (kref < 0)
        return -2;

    int melhor = -1;
    double melhor_d2 = DBL_MAX;

    for (int externa = 1; externa <= rede->C; externa++) {
        if (cluster_da_cidade(externa, rede) == kref)
            continue;

        double minima = DBL_MAX;

        for (int j = 0;
             j < rede->cluster_sizes[kref]; j++) {
            int membro = rede->clusters[kref][j];

            double d2 = distancia2(membro, externa, cidades);

            if (d2 < minima)
                minima = d2;
        }

        if (minima < melhor_d2) {
            melhor_d2 = minima;
            melhor = externa;
        }
    }

    return melhor < 0 ? -2 : melhor;
}