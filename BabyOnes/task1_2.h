#ifndef TASKS1_2_H
#define TASKS1_2_H

#include <stdio.h>
typedef struct {
    int C;                 // Número de cidades
    int L;                 // Número de ligações
    int num_clusters;      // Número  de clusters
    int **clusters;        // IDs das cidades
    int *cluster_sizes;    
} Rede;

Rede *carregar_e_processar_mapa(FILE *f_map);

/*
 Liberta a memória alocada dinamicamente para a estrutura da rede.
 */
void libertar_rede(Rede *rede);

/*
 Lê o ficheiro .quests, processa as instruções "Task1" e "Task2"
 e escreve as respostas formatadas no ficheiro .results.
 */
void processar_tarefas_1_e_2(FILE *f_quests, FILE *f_results, Rede *rede);

#endif 