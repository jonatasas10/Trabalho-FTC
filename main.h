#ifndef MAIN_H
#define MAIN_H
#define tam 25

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

void libera_memoria(afd *afd);
#endif