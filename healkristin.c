#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Task3Task4.h"
#include "position.h"
#include "Tasks.h"
// Função real do teu Map.c
int Map(int ***ClusterOut, int **ClusterSizeOut, int *numeroClustersOut, int *COut);



extern int Task3C;
extern int Task4C;
extern int CC3; // Variável global para armazenar a cidade mais próxima do cluster de referência
extern int CC4; // Variável global para armazenar a cidade mais próxima do cluster de referência

// Validação da extensão
int tem_extensao(const char *nome, const char *ext) {
    if (!nome || !ext) return 0;
    int len_nome = strlen(nome);
    int len_ext = strlen(ext);
    if (len_nome < len_ext) return 0;
    return strcmp(&nome[len_nome - len_ext], ext) == 0;
}

int main(int argc, char *argv[]) {
    // 1. Validação estrita de argumentos[cite: 4]
    if (argc != 4 ||
        !tem_extensao(argv[1], ".quests") ||
        !tem_extensao(argv[2], ".map") ||
        !tem_extensao(argv[3], ".position")) {
        return 0; // Sai sem output se a invocação for inválida
    }

    // 2. Abertura dos ficheiros[cite: 4]
    FILE *f_quests = fopen(argv[1], "r");
    FILE *f_map    = fopen(argv[2], "r");
    FILE *f_pos    = fopen(argv[3], "r");

    if (!f_quests || !f_map || !f_pos) {
        if (f_quests) fclose(f_quests);
        if (f_map)    fclose(f_map);
        if (f_pos)    fclose(f_pos);
        return 0;
    }

    /* ---------------------------------------------------------------------
     * 3. CARREGAR DADOS REAIS DO MAPA (Map.c)
     * --------------------------------------------------------------------- */
    int C = 0;
    int numeroClusters = 0;
    int **Cluster = NULL;
    int *ClusterSize = NULL;

    // Chamas o teu Map() passando os endereços das variáveis.
    // O teu Map.c vai preencher o C real, o numeroClusters, a matriz Cluster e os tamanhos!
    if (Map(&Cluster, &ClusterSize, &numeroClusters, &C) != 0) {
        fclose(f_quests); fclose(f_map); fclose(f_pos);
        return 0;
    }

    /* ---------------------------------------------------------------------
     * 4. CARREGAR E VALIDAR POSIÇÕES REAIS (position.c)
     * --------------------------------------------------------------------- */
    // Passa o f_pos e o 'C' REAL devolvido pelo Map.c
    Posicao *cidades = ler_e_validar_posicoes(f_pos, C);
    if (cidades == NULL) { 
        // Se houver erro de validação no .position, fecha tudo e sai sem output
        fclose(f_quests); fclose(f_map); fclose(f_pos);
        return 0; 
    }



    /* ---------------------------------------------------------------------
     * 5. CRIAR FICHEIRO .results
     * --------------------------------------------------------------------- */
    char nome_results[256];
    strcpy(nome_results, argv[1]);
    int len = strlen(nome_results);
    strcpy(&nome_results[len - 7], ".results"); // Troca ".quests" por ".results"

    
    FILE *f_results = fopen(nome_results, "w");
    if (f_results != NULL) {

        // Exemplo direto de escrita da Task 1 e Task 2 usando os dados REAIS:
        
        // Task 1
        fprintf(f_results, "Task1 %d\n\n", numeroClusters);

        // Task 2
        fprintf(f_results, "Task2 %d\n", numeroClusters);
        for (int i = 0; i < numeroClusters; i++) {
            fprintf(f_results, "Cluster:");
            for (int j = 0; j < ClusterSize[i]; j++) {
                fprintf(f_results, " %d", Cluster[i][j]);
            }
            fprintf(f_results, "\n");
        }
        fprintf(f_results, "\n");

        // Task 4
        fprintf(f_results, "Task4 %d ", Task4C);
        fprintf(f_results, "%d\n", CC4); // CC4 é a cidade mais próxima do cluster de referência

        // Task 3
        fprintf(f_results, "Task3 %d ", Task3C);
        fprintf(f_results, "%d\n", CC3); // CC3 é a cidade mais próxima do cidade de referência

        fclose(f_results);
    }

    /* ---------------------------------------------------------------------
     * 6. LIBERTAÇÃO DE MEMÓRIA E FECHO DE FICHEIROS
     * --------------------------------------------------------------------- */

    free(cidades);
    
    // Libertar os clusters que o Map.c alocou
    for (int i = 0; i < C; i++) {
        free(Cluster[i]);
    }
    free(Cluster);
    free(ClusterSize);

    fclose(f_quests);
    fclose(f_map);
    fclose(f_pos);

    return 0;
}
