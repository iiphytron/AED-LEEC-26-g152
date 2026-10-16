#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <OpenFile.c>

int Task(void) {
    FILE *f_quests = fopen(".quest", "r"); //abre o ficheiro quests para leitura
    char line[256];
    int Task3C = 0;
    int Task4C = 0;

    if (f_quests == NULL) {
        perror("fopen");
        return 1;
    }

    while (fscanf(f_quests, "%s", line) == 1) { //lê cada linha do ficheiro quests
        if (strcmp(line, "Task1") == 0 || strcmp(line, "Task2") == 0) { //verifica se a linha corresponde a Task1 ou Task2
            printf("Task 1 and 2 %s are valid.\n", line);
        } else {
            break;
        }
    }

    while (fscanf(f_quests, "%s %d", line, &Task3C) == 2) { //lê cada linha do ficheiro quests e armazena o valor de Task3C
        if (strcmp(line, "Task3") == 0) {
            printf("Task 3 %s %d is valid.\n", line, Task3C);
        } else {
            break;
        }
    }
    while (fscanf(f_quests, "%s %d", line, &Task4C) == 2) { //lê cada linha do ficheiro quests e armazena o valor de Task4C
        if (strcmp(line, "Task4") == 0) {
            printf("Task 4 %s %d is valid.\n", line, Task4C);
        } else {
            break;
        }
    }

    fclose(f_quests);
    return 0;
}


