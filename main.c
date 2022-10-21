#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "complemento.h"
#include "gerarAFD.h"

afd *produto(afd *afd1, afd *afd2){
    afd *afd3 = calloc(1,sizeof(afd));
    afd3->qtd_estados = (afd1->qtd_estados)*(afd2->qtd_estados);
    afd3->estado = calloc(afd3->qtd_estados, sizeof(*afd3->estado));
    
    afd3->estado_inicial = calloc(20,sizeof(afd3->estado_inicial));
    
    for (int i = 0; i < afd3->qtd_estados; i++) afd3->estado[i] = calloc(50, sizeof(afd3->estado));
    afd3->qtd_alfabeto = afd1->qtd_alfabeto;
    afd3->alfabeto = afd1->alfabeto;
    int conta = 0,x;
    for (int i = 0; i < afd1->qtd_estados; i++){
        for (int j = 0; j < afd2->qtd_estados; j++){
            strcpy(afd3->estado[conta], afd1->estado[i]);
            strcat(afd3->estado[conta], afd2->estado[j]);
            //printf("%s\n",afd3->estado[conta]);
            conta++;
            //scanf("%d",&x );
        }

    }
    strcpy(afd3->estado_inicial, afd3->estado[0]);
    afd3->qtd_estados_finais = 1;
    afd3->estados_finais = calloc(1,sizeof(*afd3->estados_finais));
    afd3->estados_finais[0] = calloc(1,sizeof(afd3->estados_finais[0]));
    strcpy(afd3->estados_finais[0], afd3->estado_inicial);
    
    int qtd_transicao = 0;
    
    afd3->transicao = calloc(50,sizeof(afd3->transicao));
    for (int i = 0; i < 50; i++){
    afd3->transicao[i].origem = calloc(20,sizeof(char));
    afd3->transicao[i].ler = calloc(2,sizeof(char));
    afd3->transicao[i].destino = calloc(20,sizeof(char));
    }
    
    for (int i = 0; i < afd1->qtd_transicoes; i++){
        conta = 0;
        for (int j = 0; j < afd2->qtd_transicoes; j++){
            printf("%d == %d\n", i,j);
            if (strcmp(afd1->transicao[i].ler, afd2->transicao[j].ler) == 0){
                //printf("entra\n");
                strcpy(afd3->transicao[qtd_transicao].origem, afd1->transicao[i].origem);
                strcat(afd3->transicao[qtd_transicao].origem, afd2->transicao[j].origem);
                //printf("VERIFICA %s AFD %s\n",verifica,afd3->estado[conta]);
                //if (strcmp(verifica, afd3->estado[conta]) == 0){
                //strcat(afd3->transicao[qtd_transicao].origem, verifica);
                strcpy(afd3->transicao[qtd_transicao].ler, afd1->transicao[i].ler);
                strcpy(afd3->transicao[qtd_transicao].destino, afd1->transicao[i].destino);
                strcat(afd3->transicao[qtd_transicao].destino, afd2->transicao[j].destino);
                //printf("TRAN %s -%s - %s\n", afd3->transicao[qtd_transicao].origem, afd3->transicao[qtd_transicao].ler, afd3->transicao[qtd_transicao].destino);
                    //if (qtd_transicao == 12) break;
                    qtd_transicao++;
                    conta++;

                //}
                
                
            }           

        }
         
    }

    afd3->qtd_transicoes = qtd_transicao;
    //for (int i = 0; i < afd3->qtd_transicoes; i++) printf("%s %s %s\n", afd3->transicao[i].origem, afd3->transicao[i].ler, afd3->transicao[i].destino);
    //for (int i = 0; i < afd3->qtd_estados; i++) printf("%s\n", afd3->estado[i]);
    //for (int i = 0; i < afd3->qtd_alfabeto; i++) printf("%s\n", afd3->alfabeto[i]);
        
    return afd3;
}

int main(){
    FILE *AFD1 = fopen("/home/jonatas/Jonatas/VSCODE/FTC/AFD.txt", "r");
    FILE *AFD2 = fopen("/home/jonatas/Jonatas/VSCODE/FTC/AFD2.txt", "r");
    afd *afd1 = calloc(1,sizeof(afd));
    afd *afd2 = calloc(1,sizeof(afd));
    cria_AFD(afd1, AFD1);
    cria_AFD(afd2, AFD2);
    //afd *afd3 = produto(afd1,afd2);
    //complemento(nome);
    visualizacao(afd2);
   // for (int i = 0; i < afd3->qtd_transicoes; i++) printf("%s %s %s\n", afd3->transicao[i].origem, afd3->transicao[i].ler, afd3->transicao[i].destino);
    //for (int i = 0; i < afd3->qtd_estados_finais; i++) printf("%s\n",afd3->estados_finais[i]);
    //for (int i = 0; i < afd3->qtd_alfabeto; i++) printf("%s\n", afd3->alfabeto[i]);
    //for (int i = 0; i < afd3->qtd_estados; i++) printf("%s\n", afd3->estado[i]);
    //printf("%s\n", afd3->estado_inicial);

    //libera_memoria(afd1);
    //libera_memoria(afd2);
    fclose(AFD1);
    fclose(AFD2);
    return 0;
}

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