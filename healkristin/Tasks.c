#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "task.h"
#include "Task3Task4.h"

static void escrever_invalida(FILE *out,
                              const char *linha)
{
    size_t n = strlen(linha);

    while (n > 0 && isspace((unsigned char)linha[n - 1]))
        n--;

    fprintf(out, "%.*s -2\n\n", (int)n, linha);
}

int processar_quests(FILE *f_quests,
                     FILE *f_results,
                     const Rede *rede,
                     const Posicao *cidades)
{
    char linha[1024];

    if (!f_quests || !f_results || !rede || !cidades)
        return 0;

    while (fgets(linha, sizeof(linha), f_quests) != NULL) {
        char original[sizeof(linha)];
        strcpy(original, linha);

        size_t nlinha = strlen(linha);

        while (nlinha > 0 &&
               (linha[nlinha - 1] == '\n' ||
                linha[nlinha - 1] == '\r')) {
            linha[--nlinha] = '\0';
        }

        int so_espacos = 1;

        for (size_t i = 0; linha[i]; i++) {
            if (!isspace((unsigned char)linha[i])) {
                so_espacos = 0;
                break;
            }
        }

        if (so_espacos)
            continue;

        char tarefa[32], extra[32];
        int referencia = 0;

        int n = sscanf(linha, " %31s %d %31s",
                       tarefa, &referencia, extra);

        if (n == 1 && strcmp(tarefa, "Task1") == 0) {
            fprintf(f_results, "Task1 %d\n\n",
                    rede->num_clusters);

        } else if (n == 1 &&
                   strcmp(tarefa, "Task2") == 0) {

            fprintf(f_results, "Task2 %d\n",
                    rede->num_clusters);

            for (int k = 0; k < rede->num_clusters; k++) {
                fputs("Cluster:", f_results);

                for (int j = 0;
                     j < rede->cluster_sizes[k]; j++) {
                    fprintf(f_results, " %d",
                            rede->clusters[k][j]);
                }

                fputc('\n', f_results);
            }

            fputc('\n', f_results);

        } else if (n == 2 &&
                   strcmp(tarefa, "Task3") == 0) {

            fprintf(f_results, "Task3 %d %d\n\n",
                    referencia,
                    Task3(referencia, rede, cidades));

        } else if (n == 2 &&
                   strcmp(tarefa, "Task4") == 0) {

            fprintf(f_results, "Task4 %d %d\n\n",
                    referencia,
                    Task4(referencia, rede, cidades));

        } else {
            escrever_invalida(f_results, original);
        }
    }

    return !ferror(f_quests) && !ferror(f_results);
}