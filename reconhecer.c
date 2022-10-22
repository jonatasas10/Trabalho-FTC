#include "reconhecer.h"

// Transicao delta
char* _delta(afd *afd1, char* estado_atual, char *simbolo){
    for (int i = 0; i < afd1->qtd_transicoes; ++i) {
        if((strcmp(estado_atual, afd1->transicao[i].origem) == 0)
            && (strcmp(simbolo, afd1->transicao[i].ler)) == 0){
            return afd1->transicao[i].destino;
        }
    }
    return NULL;
}

int _reconhecer(afd *afd1, char *palavra){
    char *estado_atual;
    char *estado_temp;
    char ler_temp[2];
    ler_temp[1] = '\0';

    estado_atual = afd1->estado_inicial;
    for (int i = 0; i < strlen(palavra); ++i) {
        ler_temp[0] = palavra[i];
        //printf("<%c>", palavra[i]);
        estado_temp = _delta(afd1, estado_atual, ler_temp);

        // Caso pare em um estado de erro ou transicao invalida
        if(estado_temp == NULL){
           // printf("[Nao reconheceu, estado de erro]");
            return 0;
            break;
        }
        estado_atual = estado_temp;
    }

    // Verifica se o estado atual e um estado final
    for (int i = 0; i < afd1->qtd_estados_finais; ++i) {
        if(strcmp(estado_temp, afd1->estados_finais[i]) == 0){ // <- alterar afd1->estados_finais[i]
           // printf("[Reconheceu]");
            return 1;
            break;
        }
    }
    // Caso nao for, retorna falso
   // printf("[Nao reconheceu, estado nao final]");
    return 0;
}

int reconhecer_palavra(afd *afd1, char* palavra){
    return _reconhecer(afd1, palavra);
}
