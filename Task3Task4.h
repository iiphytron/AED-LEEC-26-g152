#ifndef TASK3TASK4_H
#define TASK3TASK4_H

/*
 * Cityx e Cityy são arrays indexados pelo ID real da cidade (1..C).
 * Pressupõe-se que têm C+1 posições, deixando a posição 0 sem uso.
 * Cluster[k][j] contém o ID real da cidade, e ClusterSize[k] o tamanho
 * do cluster k.
 * As funções devolvem o ID da cidade encontrada, ou -2 se inexequível.
 */
int Task3(
    int referencia,
    int C,
    int numeroClusters,
    int **Cluster,
    const int ClusterSize[],
    const int Cityx[],
    const int Cityy[]
);

int Task4(
    int referencia,
    int C,
    int numeroClusters,
    int **Cluster,
    const int ClusterSize[],
    const int Cityx[],
    const int Cityy[]
);

#endif
