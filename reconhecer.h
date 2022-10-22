#ifndef TEST_RECONHECER_H
#define TEST_RECONHECER_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

char* _delta(afd *afd1, char* estado_atual, char *simbolo);

int _reconhecer(afd *afd1,char *palavra);

int reconhecer_palavra(afd *afd1, char* palavra);

#endif //TEST_RECONHECER_H
