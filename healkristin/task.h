#ifndef TASKS_H
#define TASKS_H

#include <stdio.h>
#include "Tasks1_2.h"
#include "position.h"

int processar_quests(FILE *f_quests,
                     FILE *f_results,
                     const Rede *rede,
                     const Posicao *cidades);

#endif