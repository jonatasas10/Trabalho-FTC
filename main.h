#ifndef MAIN_H
#define MAIN_H

typedef struct transicao{
    char origem[20];
    char destino[20];
    char ler [2];
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

int verifica_existencia(char **comp, int x, char *e);

#endif