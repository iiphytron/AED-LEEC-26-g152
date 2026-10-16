#ifndef MAP_H
#define MAP_H

/*
 * Lê o mapa e constrói os clusters.
 *
 * ClusterOut recebe a matriz de clusters; ClusterSizeOut recebe o tamanho
 * de cada cluster; numeroClustersOut recebe o número de clusters; e
 * numeroCidadesOut recebe C, o número de cidades do mapa.
 *
 * Os arrays devolvidos devem continuar válidos até o chamador os libertar.
 * Devolve 0 em caso de sucesso e um valor diferente de 0 em caso de erro.
 *
 * NOTA: é uma interface proposta. A implementação Map.c tem de ser adaptada
 * para ter exatamente esta assinatura se quiseres usá-la desta forma.
 */
int Map(
    const char *nomeMap,
    int ***ClusterOut,
    int **ClusterSizeOut,
    int *numeroClustersOut,
    int *numeroCidadesOut
);

/* Liberta os arrays devolvidos por Map(). */
void LibertarClusters(int numeroClusters, int **Cluster, int *ClusterSize);

#endif
