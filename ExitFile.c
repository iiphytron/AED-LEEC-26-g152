#include <stdio.h>
#include "ExitFile.h"

/*
 * Molde para gerar o ficheiro .results.
 *
 * IMPORTANTE:
 * - pedidos[] deve estar pela mesma ordem das tarefas em .quests.
 * - Para Task3/Task4, pedidos[i].resultado tem de ser o ID da cidade
 *   de destino, não a distância. Se a tarefa for inexequível, usa -2.
 * - Cluster[k][j] contém o ID da cidade j do cluster k.
 * - ClusterSize[k] contém o número de cidades do cluster k.
 */
int ExitFile(
    const char *nomeSaida,
    const PedidoSaida pedidos[],
    int numeroPedidos,
    int numeroClusters,
    int **Cluster,
    const int ClusterSize[]
) {
    FILE *fout;
    int i, k, j;

    if (nomeSaida == NULL || pedidos == NULL || numeroPedidos < 0) {
        return 1;
    }

    fout = fopen(nomeSaida, "w");
    if (fout == NULL) {
        perror("Erro ao criar ficheiro de resultados");
        return 1;
    }

    for (i = 0; i < numeroPedidos; i++) {
        switch (pedidos[i].tipo) {
            case 1:
                /* Task1: número total de clusters. */
                if (fprintf(fout, "Task1 %d\n", numeroClusters) < 0) {
                    fclose(fout);
                    return 1;
                }
                break;

            case 2:
                /* Task2: número de clusters e conteúdo de cada cluster. */
                if (fprintf(fout, "Task2 %d\n", numeroClusters) < 0) {
                    fclose(fout);
                    return 1;
                }

                if (numeroClusters > 0 &&
                    (Cluster == NULL || ClusterSize == NULL)) {
                    fclose(fout);
                    return 1;
                }

                for (k = 0; k < numeroClusters; k++) {
                    if (ClusterSize[k] > 0 && Cluster[k] == NULL) {
                        fclose(fout);
                        return 1;
                    }

                    if (fprintf(fout, "Cluster:") < 0) {
                        fclose(fout);
                        return 1;
                    }

                    for (j = 0; j < ClusterSize[k]; j++) {
                        if (fprintf(fout, " %d", Cluster[k][j]) < 0) {
                            fclose(fout);
                            return 1;
                        }
                    }

                    if (fputc('\n', fout) == EOF) {
                        fclose(fout);
                        return 1;
                    }
                }
                break;

            case 3:
                /* Task3: cidade de referência e cidade mais próxima externa. */
                if (fprintf(fout, "Task3 %d %d\n",
                            pedidos[i].referencia,
                            pedidos[i].resultado) < 0) {
                    fclose(fout);
                    return 1;
                }
                break;

            case 4:
                /* Task4: cidade de referência e cidade mais próxima ao cluster. */
                if (fprintf(fout, "Task4 %d %d\n",
                            pedidos[i].referencia,
                            pedidos[i].resultado) < 0) {
                    fclose(fout);
                    return 1;
                }
                break;

            default:
                fprintf(stderr, "Tipo de tarefa inválido: %d\n", pedidos[i].tipo);
                fclose(fout);
                return 1;
        }

        /* Uma linha vazia separa os resultados das tarefas. */
        if (i < numeroPedidos - 1 && fputc('\n', fout) == EOF) {
            fclose(fout);
            return 1;
        }
    }

    if (fclose(fout) != 0) {
        perror("Erro ao fechar o ficheiro de resultados");
        return 1;
    }

    return 0;
}
