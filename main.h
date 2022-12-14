#ifndef MAIN_H
#define MAIN_H
#define tam 25

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct transicao{
    char origem[tam];
    char destino[tam];
    char ler[tam];
}transicao;

typedef struct afd{
    int qtd_estados;
    int qtd_transicoes;
    int qtd_alfabeto;
    int qtd_estados_finais;
    char **estado;
    char **alfabeto;
    transicao *transicao;
    char *estado_inicial;
    char **estados_finais;

} afd;

typedef struct conjuntos{
    char **estado;
} conjuntos;

void libera_memoria(afd *afd);
int verifica(afd *min, char *E, char *e, char **conjunto, int TAM, int tamc);
void atualiza_conjuntos(char **conjunto, int pos, int TAM);
void mostra(conjuntos *conjuntos,int n, int *x);
#endif