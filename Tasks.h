#ifndef TASKS_H
#define TASKS_H

#include "ExitFile.h"

/*
 * Lê os pedidos de nomeQuests e guarda-os em pedidos[], pela mesma ordem
 * em que aparecem no ficheiro. capacidade é o número máximo de elementos.
 * numeroPedidos recebe quantos pedidos foram lidos.
 * Devolve 0 em caso de sucesso e um valor diferente de 0 em caso de erro.
 *
 * NOTA: é necessário implementar esta assinatura no Tasks.c; não corresponde
 * diretamente à versão antiga int Task(void).
 */
int LerTasks(
    const char *nomeQuests,
    PedidoSaida pedidos[],
    int capacidade,
    int *numeroPedidos
);

#endif
