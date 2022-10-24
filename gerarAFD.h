#ifndef GERARAFD_H
#define GERARAFD_H
#include "main.h"

void visualizacao(afd *saida, char *dot);
void cria_AFD(afd *entrada, FILE *afd_arq);
void saida (afd *afd1, char *afdsaida);
#endif