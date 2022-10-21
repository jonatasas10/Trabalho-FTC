#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "complemento.h"
#include "gerarAFD.h"

void libera_memoria(afd *afd){
    for (int i = 0; i < afd->qtd_estados; i++) free(afd->estado[i]);
    free(afd->estado);
    for (int i = 0; i < afd->qtd_alfabeto; i++) free(afd->alfabeto[i]);
    free(afd->alfabeto);
    for (int i = 0; i < afd->qtd_estados_finais; i++) free(afd->estados_finais[i]);
    free(afd->estados_finais);
    free(afd->estado_inicial);
    free(afd->transicao);
    free(afd);
}
int main(){
    FILE *AFD_entrada = fopen("/home/jonatas/Jonatas/VSCODE/FTC/AFD2.txt", "r");
    afd *nome = calloc(1,sizeof(afd));
    cria_AFD(nome, AFD_entrada);
    complemento(nome);
    visualizacao(nome);
    libera_memoria(nome);
    fclose(AFD_entrada);
    return 0;
}