#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "complemento.h"
#include "gerarAFD.h"
#include "produto.h"

int main(){
    FILE *AFD1 = fopen("/home/jonatas/Jonatas/VSCODE/FTC/AFD.txt", "r");
    FILE *AFD2 = fopen("/home/jonatas/Jonatas/VSCODE/FTC/AFD2.txt", "r");
    
    afd *afd1 = calloc(1,sizeof(afd));
    afd *afd2 = calloc(1,sizeof(afd));
    cria_AFD(afd1, AFD1);
    cria_AFD(afd2, AFD2);
    afd *afd3 = produto(afd1,afd2);
    uniao(afd3, afd1, afd2);
    //complemento(nome);
    //intersecao(afd3,afd1,afd2);
    visualizacao(afd3);

    libera_memoria(afd1);
    libera_memoria(afd2);
    libera_memoria(afd3);
    fclose(AFD1);
    fclose(AFD2);
    return 0;
}

void libera_memoria(afd *afd){
    if (afd->estado != NULL){
        for (int i = 0; i < afd->qtd_estados; i++) free(afd->estado[i]);
        free(afd->estado);
        afd->estado = NULL;
    }
    if (afd->alfabeto != NULL){
        for (int i = 0; i < afd->qtd_alfabeto; i++) free(afd->alfabeto[i]);
        free(afd->alfabeto);
        afd->alfabeto= NULL;
    }
    if (afd->estados_finais != NULL){
        for (int i = 0; i < afd->qtd_estados_finais; i++) free(afd->estados_finais[i]);
        free(afd->estados_finais);
        afd->estados_finais = NULL;
    }
    if (afd->estado_inicial != NULL){
        free(afd->estado_inicial);
        afd->estado_inicial = NULL;
    }
    if (afd->transicao != NULL){
            free(afd->transicao);
            afd->transicao = NULL;
    }
    if (afd != NULL){
        free(afd);
        afd = NULL;
    }
    
}