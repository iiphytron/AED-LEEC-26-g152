#ifndef EXITFILE_H
#define EXITFILE_H

/*
 * Um pedido corresponde a uma linha do ficheiro .quests.
 * tipo: 1, 2, 3 ou 4.
 * referencia: ID da cidade pedido em Task3/Task4; ignorado em Task1/Task2.
 * resultado: ID da cidade encontrada em Task3/Task4, ou -2 se inexequível.
 */
typedef struct {
    int tipo;
    int referencia;
    int resultado;
} PedidoSaida;

/* Escreve os resultados em nomeSaida (normalmente ".results"). */
int ExitFile(
    const char *nomeSaida,
    const PedidoSaida pedidos[],
    int numeroPedidos,
    int numeroClusters,
    int **Cluster,
    const int ClusterSize[]
);

#endif
