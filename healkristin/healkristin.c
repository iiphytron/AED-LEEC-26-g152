#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Tasks1_2.h"
#include "position.h"
#include "task.h"

/* Verifica se o nome termina com a extensão indicada. */
static int tem_extensao(const char *nome, const char *ext)
{
    if (nome == NULL || ext == NULL)
        return 0;

    size_t n = strlen(nome);
    size_t e = strlen(ext);

    return n >= e && strcmp(nome + n - e, ext) == 0;
}

int main(int argc, char *argv[])
{
    /* 1. Validar os argumentos. */
    if (argc != 4 ||
        !tem_extensao(argv[1], ".quests") ||
        !tem_extensao(argv[2], ".map") ||
        !tem_extensao(argv[3], ".position")) {
        return 0;
    }

    /* 2. Abrir primeiro os ficheiros de entrada. */
    FILE *f_quests = fopen(argv[1], "r");
    FILE *f_map = fopen(argv[2], "r");
    FILE *f_pos = fopen(argv[3], "r");

    if (f_quests == NULL ||
        f_map == NULL ||
        f_pos == NULL) {

        if (f_quests != NULL)
            fclose(f_quests);

        if (f_map != NULL)
            fclose(f_map);

        if (f_pos != NULL)
            fclose(f_pos);

        return 0;
    }

    /* 3. Ler o mapa e construir os clusters. */
    Rede *rede = carregar_e_processar_mapa(f_map);

    if (rede == NULL) {
        fclose(f_quests);
        fclose(f_map);
        fclose(f_pos);
        return 0;
    }

    /* 4. Ler e validar as coordenadas das cidades. */
    Posicao *cidades =
        ler_e_validar_posicoes(f_pos, rede->C);

    if (cidades == NULL) {
        libertar_rede(rede);

        fclose(f_quests);
        fclose(f_map);
        fclose(f_pos);

        return 0;
    }

    /* 5. Construir o nome do ficheiro .results. */
    size_t qlen = strlen(argv[1]);
    const size_t qext = strlen(".quests");
    const char *rext = ".results";

    size_t rlen = qlen - qext + strlen(rext);

    char *nome_results = malloc(rlen + 1);

    if (nome_results == NULL) {
        free(cidades);
        libertar_rede(rede);

        fclose(f_quests);
        fclose(f_map);
        fclose(f_pos);

        return 0;
    }

    memcpy(nome_results, argv[1], qlen - qext);
    strcpy(nome_results + qlen - qext, rext);

    /* 6. Criar o ficheiro de resultados. */
    FILE *f_results = fopen(nome_results, "w");

    free(nome_results);

    if (f_results != NULL) {
        /* Executar as tarefas pela ordem do ficheiro .quests. */
        (void)processar_quests(
            f_quests,
            f_results,
            rede,
            cidades
        );

        fclose(f_results);
    }

    /* 7. Libertar a memória utilizada. */
    free(cidades);
    libertar_rede(rede);

    /* 8. Fechar os ficheiros de entrada. */
    fclose(f_quests);
    fclose(f_map);
    fclose(f_pos);

    return 0;
}