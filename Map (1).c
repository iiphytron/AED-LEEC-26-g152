#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <Openfile.c>


/*
 * Une os clusters das cidades A e B usando Quick-Find.
 */
void quick_find_union(int id[], int C, int A, int B)
{
    int valorA = id[A];
    int valorB = id[B];
    int i;

    /*
     * Se A e B já pertencem ao mesmo cluster,
     * não é necessário alterar nada.
     */
    if (valorA == valorB) {
        return;
    }

    /*
     * Todas as cidades que pertenciam ao cluster
     * de A passam para o cluster de B.
     */
    for (i = 1; i <= C; i++) {

        if (id[i] == valorA) {
            id[i] = valorB;
        }
    }
}


int Map(
    int ***ClusterOut,
    int **ClusterSizeOut,
    int *numeroClustersOut,
    int *COut
)
{
    FILE *f_map = fopen(".map", "r");

    char line[256];

    if (f_map == NULL) {
        perror("fopen");
        return 1;
    }


    /*
     * C = número de cidades
     * L = número de ligações
     */
    int C = 0;
    int L = 0;

    char valor1[256];
    char valor2[256];


    /*
     * ============================================================
     * 1. LER A PRIMEIRA LINHA
     * ============================================================
     */

    if (fscanf(f_map, "%s %s", valor1, valor2) == 2) {

        C = atoi(valor1);
        L = atoi(valor2);
    }
    else {

        printf("Erro ao ler a primeira linha do ficheiro map.\n");

        fclose(f_map);

        return 0;
    }


    /*
     * ============================================================
     * 2. CRIAR AS ESTRUTURAS NECESSÁRIAS
     * ============================================================
     *
     * ligacaoA[i] e ligacaoB[i]
     *      -> guardam os números originais das cidades.
     *
     * id[i]
     *      -> é a cópia que o Quick-Find vai alterar.
     *
     * usado[i]
     *      -> indica se a cidade já foi colocada num cluster.
     */

    int *ligacaoA = malloc(L * sizeof(int));
    int *ligacaoB = malloc(L * sizeof(int));

    int *id = malloc((C + 1) * sizeof(int));
    int *usado = calloc((C + 1), sizeof(int));


    /*
     * Cluster[i] vai guardar as cidades pertencentes
     * ao cluster i.
     *
     * Existem no máximo C clusters.
     */
    int **Cluster = malloc(C * sizeof(int *));

    /*
     * ClusterSize[i] diz quantas cidades existem
     * dentro de Cluster[i].
     */
    int *ClusterSize = calloc(C, sizeof(int));

    int i;
    int j;


    /*
     * Verificar se foi possível reservar memória.
     */
    if (ligacaoA == NULL ||
        ligacaoB == NULL ||
        id == NULL ||
        usado == NULL ||
        Cluster == NULL ||
        ClusterSize == NULL) {

        printf("Erro ao reservar memoria.\n");

        fclose(f_map);

        free(ligacaoA);
        free(ligacaoB);
        free(id);
        free(usado);
        free(Cluster);
        free(ClusterSize);

        return 1;
    }


    /*
     * Cada cluster pode ter, no máximo, C cidades.
     */
    for (i = 0; i < C; i++) {

        Cluster[i] = malloc(C * sizeof(int));

        if (Cluster[i] == NULL) {

            printf("Erro ao reservar memoria.\n");

            for (j = 0; j < i; j++) {
                free(Cluster[j]);
            }

            fclose(f_map);

            free(ligacaoA);
            free(ligacaoB);
            free(id);
            free(usado);
            free(Cluster);
            free(ClusterSize);

            return 1;
        }
    }


    /*
     * ============================================================
     * 3. INICIALIZAR O QUICK-FIND
     * ============================================================
     *
     * No início cada cidade pertence ao seu próprio cluster:
     *
     * id[1] = 1
     * id[2] = 2
     * id[3] = 3
     * ...
     */
    for (i = 1; i <= C; i++) {
        id[i] = i;
    }


    /*
     * ============================================================
     * 4. LER AS L LIGAÇÕES
     * ============================================================
     */

    /*
     * Como o fscanf anterior deixou o '\n' da primeira linha
     * no ficheiro, consumimos o resto dessa primeira linha.
     */
    fgets(line, sizeof(line), f_map);


    for (i = 0; i < L; i++) {

        int A;
        int B;


        /*
         * Ler duas cidades.
         */
        if (fscanf(f_map, "%d %d", &A, &B) != 2) {

            printf("Erro ao ler uma ligacao.\n");

            /*
             * Libertar memória antes de terminar.
             */
            for (j = 0; j < C; j++) {
                free(Cluster[j]);
            }
            *ClusterOut = Cluster;
            *ClusterSizeOut = ClusterSizeOut;
            *COut = C;
            free(ligacaoA);
            free(ligacaoB);
            free(id);
            free(usado);
            free(Cluster);
            free(ClusterSize);

            fclose(f_map);

            return 1;
        }


        /*
         * ========================================================
         * VERIFICAR SE AS CIDADES ESTÃO ENTRE 1 E C
         * ========================================================
         *
         * Se aparecer uma cidade maior que C,
         * o ficheiro é inválido.
         */
        if (A < 1 || A > C || B < 1 || B > C) {

            printf("Erro: numero de cidade invalido.\n");

            for (j = 0; j < C; j++) {
                free(Cluster[j]);
            }

            free(ligacaoA);
            free(ligacaoB);
            free(id);
            free(usado);
            free(Cluster);
            free(ClusterSize);

            fclose(f_map);

            return 1;
        }


        /*
         * Guardamos os números originais.
         *
         * Estes valores nunca são alterados.
         */
        ligacaoA[i] = A;
        ligacaoB[i] = B;
    }


    /*
     * ============================================================
     * 5. APLICAR O QUICK-FIND ÀS LIGAÇÕES
     * ============================================================
     *
     * Aqui usamos a cópia id[].
     *
     * ligacaoA[] e ligacaoB[] continuam com os números
     * originais das cidades.
     */
    for (i = 0; i < L; i++) {

        quick_find_union(
            id,
            C,
            ligacaoA[i],
            ligacaoB[i]
        );
    }


    /*
     * ============================================================
     * 6. CONSTRUIR OS CLUSTERS
     * ============================================================
     */

    int numeroClusters = 0;


    while (1) {

        int primeiraCidade = -1;
        int valorCluster;


        /*
         * Procurar a primeira cidade que ainda não
         * foi colocada num cluster.
         *
         * Como começamos em 1 e avançamos até C,
         * encontramos sempre a menor cidade disponível.
         */
        for (i = 1; i <= C; i++) {

            if (usado[i] == 0) {

                primeiraCidade = i;

                break;
            }
        }


        /*
         * Não existem mais cidades por utilizar.
         */
        if (primeiraCidade == -1) {
            break;
        }


        /*
         * Guardamos o valor que identifica o cluster
         * da primeira cidade encontrada.
         */
        valorCluster = id[primeiraCidade];


        /*
         * Inicialmente este cluster não tem cidades.
         */
        ClusterSize[numeroClusters] = 0;


        /*
         * Procurar todas as cidades que tenham
         * exatamente o mesmo valor em id[].
         */
        for (j = 1; j <= C; j++) {

            if (usado[j] == 0 &&
                id[j] == valorCluster) {

                /*
                 * j continua a ser o número ORIGINAL
                 * da cidade.
                 */
                Cluster[numeroClusters]
                       [ClusterSize[numeroClusters]]
                    = j;


                ClusterSize[numeroClusters]++;


                /*
                 * Esta cidade já foi utilizada.
                 */
                usado[j] = 1;
            }
        }


        /*
         * Passamos para o próximo cluster.
         */
        numeroClusters++;
    }


    /*
     * ============================================================
     * 7. MOSTRAR OS CLUSTERS
     * ============================================================
     */

    printf("Numero de clusters: %d\n", numeroClusters);

    *numeroClustersOut = numeroClusters;

    for (i = 0; i < numeroClusters; i++) {

        printf("Cluster[%d]:", i);

        for (j = 0; j < ClusterSize[i]; j++) {

            printf(" %d", Cluster[i][j]);
        }

        printf("\n");
    }


    /*
     * ============================================================
     * 8. LIBERTAR MEMÓRIA
     * ============================================================
     */

    for (i = 0; i < C; i++) {
        free(Cluster[i]);
    }

    free(ligacaoA);
    free(ligacaoB);
    free(id);
    free(usado);
    free(Cluster);
    free(ClusterSize);

    fclose(f_map);

    return 0;
}