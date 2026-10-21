#ifndef TASKS_H
#define TASKS_H

#include <stdio.h>
#include "position.h"
void processar_quests(FILE *f_quests, FILE *f_results, 
                      int **Cluster, int *ClusterSize, int numClusters, 
                      double **D, Posicao *cidades, int C);
#endif 
