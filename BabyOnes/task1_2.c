#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estrutura para armazenar a informação global dos clusters da rede.
 
typedef struct {
    int C;                 // Número total de cidades
    int L;                 // Número total de ligações
    int num_clusters;      // Número total de clusters encontrados
    int **clusters;        // Matriz com o ID das cidades em cada cluster
    int *cluster_sizes;    // Tamanho de cada cluster
} Rede;

//Aplica o algoritmo Quick-Find para unir duas cidades (A e B) no mesmo cluster.
void quick_find_union(int id[], int C, int A, int B) {
    int valorA = id[A];
    int valorB = id[B];

    if (valorA == valorB) return;

    for (int i = 1; i <= C; i++) {
        if (id[i] == valorA) {
            id[i] = valorB;
        }
    }
}

/**
 * Lê o ficheiro .map e constrói a estrutura de clusters organizada.
 */
Rede *carregar_e_processar_mapa(FILE *f_map) {
    Rede *rede = (Rede *) malloc(sizeof(Rede));
    if (!rede) return NULL;

    // 1. Ler o número de cidades (C) e de ligações (L)
    if (fscanf(f_map, "%d %d", &(rede->C), &(rede->L)) != 2) {
        free(rede);
        return NULL;
    }

    int C = rede->C;
    int L = rede->L;

    int *id = (int *) malloc((C + 1) * sizeof(int));
    int *usado = (int *) calloc((C + 1), sizeof(int));

    // Inicialização do Quick-Find: cada cidade começa no seu próprio conjunto
    for (int i = 1; i <= C; i++) {
        id[i] = i;
    }

    // 2. Ler as L ligações físicas do ficheiro .map
    for (int i = 0; i < L; i++) {
        int A, B;
        if (fscanf(f_map, "%d %d", &A, &B) == 2) {
            if (A >= 1 && A <= C && B >= 1 && B <= C) {
                quick_find_union(id, C, A, B);
            }
        }
    }

    // 3. Alocar memória para os clusters
    rede->clusters = (int **) malloc(C * sizeof(int *));
    rede->cluster_sizes = (int *) calloc(C, sizeof(int));
    for (int i = 0; i < C; i++) {
        rede->clusters[i] = (int *) malloc(C * sizeof(int));
    }

    rede->num_clusters = 0;

    // Agrupar as cidades.
    while (1) {
        int primeiraCidade = -1;

        // Encontra a menor cidade ainda não processada
        for (int i = 1; i <= C; i++) {
            if (usado[i] == 0) {
                primeiraCidade = i;
                break;
            }
        }

        if (primeiraCidade == -1) break; // Todas as cidades processadas

        int valorCluster = id[primeiraCidade];
        int idx_cidade = 0;

        for (int j = 1; j <= C; j++) {
            if (usado[j] == 0 && id[j] == valorCluster) {
                rede->clusters[rede->num_clusters][idx_cidade++] = j;
                usado[j] = 1;
            }
        }

        rede->cluster_sizes[rede->num_clusters] = idx_cidade;
        rede->num_clusters++;
    }

    free(id);
    free(usado);
    return rede;
}

/**
 * Liberta a memória alocada para a estrutura da rede.
 */
void libertar_rede(Rede *rede) {
    if (!rede) return;
    for (int i = 0; i < rede->C; i++) {
        free(rede->clusters[i]);
    }
    free(rede->clusters);
    free(rede->cluster_sizes);
    free(rede);
}

/**
 * Executa as tarefas 1 e 2 ao ler o ficheiro .quests e escreve em .results[cite: 5, 8].
 */
void processar_tarefas_1_e_2(FILE *f_quests, FILE *f_results, Rede *rede) {
    char tarefa[256];

    while (fscanf(f_quests, "%s", tarefa) == 1) {
        
        // Task1: Apenas o número de clusters
        if (strcmp(tarefa, "Task1") == 0) {
            fprintf(f_results, "Task1 %d\n\n", rede->num_clusters);
        }
        
        // Task2: Número de clusters seguido da composição detalhada de cada um[cite: 6, 8]
        else if (strcmp(tarefa, "Task2") == 0) {
            fprintf(f_results, "Task2 %d\n", rede->num_clusters);
            for (int i = 0; i < rede->num_clusters; i++) {
                fprintf(f_results, "Cluster:");
                for (int j = 0; j < rede->cluster_sizes[i]; j++) {
                    fprintf(f_results, " %d", rede->clusters[i][j]);
                }
                fprintf(f_results, "\n");
            }
            fprintf(f_results, "\n"); // Linha em branco separadora no final
        }
    }
}