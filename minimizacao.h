#ifndef MINIMIZACAO_H
#define MINIMIZACAO_H

#include "main.h"

void minimizacao(afd *afd1);

void mostra(conjuntos *conjuntos,int n, int *x);

void atualiza_conjuntos(char **conjunto, int pos, int TAM);

int verifica(afd *min, char *E, char *e, char **conjunto, int TAM, int tamc);
#endif