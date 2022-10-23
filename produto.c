#include "produto.h"

afd *produto(afd *afd1, afd *afd2){
    
    afd *afd3 = calloc(1,sizeof(afd));
    afd3->qtd_estados = (afd1->qtd_estados)*(afd2->qtd_estados);
    afd3->estado = calloc(afd3->qtd_estados, sizeof(*afd3->estado));
    
    afd3->estado_inicial = calloc(20,sizeof(afd3->estado_inicial));
    
    for (int i = 0; i < afd3->qtd_estados; i++) afd3->estado[i] = calloc(50, sizeof(afd3->estado));

    afd3->qtd_alfabeto = afd1->qtd_alfabeto; 

    afd3->alfabeto = afd1->alfabeto;
    int conta = 0;

    for (int i = 0; i < afd1->qtd_estados; i++){
    
        for (int j = 0; j < afd2->qtd_estados; j++){
            
            strcpy(afd3->estado[conta], afd1->estado[i]);
            strcat(afd3->estado[conta], afd2->estado[j]);
            conta++;
        }

    }

    afd3->alfabeto = calloc(sizeof(*afd3->alfabeto),afd3->qtd_alfabeto);
    int i;
    for (i = 0; i < afd3->qtd_alfabeto; i++){
        afd3->alfabeto[i] = calloc(sizeof(afd3->alfabeto), 1);
        *afd3->alfabeto[i] = *afd1->alfabeto[i];
    }
    afd3->qtd_alfabeto = i;

    strcpy(afd3->estado_inicial, afd3->estado[0]);
    
    int qtd_transicao = 0;
    
    afd3->transicao = calloc(100,sizeof(*afd3->transicao));
    
    for (int i = 0; i < afd1->qtd_transicoes; i++){
        
        for (int j = 0; j < afd2->qtd_transicoes; j++){

            if (strcmp(afd1->transicao[i].ler, afd2->transicao[j].ler) == 0){

                strcpy(afd3->transicao[qtd_transicao].origem, afd1->transicao[i].origem);
                strcat(afd3->transicao[qtd_transicao].origem, afd2->transicao[j].origem);
                
                strcpy(afd3->transicao[qtd_transicao].ler, afd2->transicao[j].ler);
                
                
                strcpy(afd3->transicao[qtd_transicao].destino, afd1->transicao[i].destino);
                strcat(afd3->transicao[qtd_transicao].destino, afd2->transicao[j].destino);

                qtd_transicao++;               
                                            
            }           

        }
         
    }

    afd3->qtd_transicoes = qtd_transicao;

    return afd3;
}

afd *uniao(afd *afdproduto, afd *afd1, afd *afd2){
    
    afdproduto = produto(afd1,afd2);
    afdproduto->estados_finais = calloc(1, sizeof(*afdproduto->estados_finais));
    
    int conta = 1;

    for (int i = 0; i < afdproduto->qtd_estados; i++){
    
        for (int j = 0; j < afd1->qtd_estados_finais; j++){
    
            for (int k = 0; k < afd2->qtd_estados_finais; k++){

                if (strstr(afdproduto->estado[i], afd1->estados_finais[j])
                    && strcmp(afdproduto->estado[i], strstr(afdproduto->estado[i], afd1->estados_finais[j])) == 0 ){                                       
                        
                    afdproduto->estados_finais[conta-1] = calloc(25, sizeof(afdproduto->estados_finais));
                    strcpy(afdproduto->estados_finais[conta-1], afdproduto->estado[i]);
                    conta++;
                    afdproduto->estados_finais = realloc(afdproduto->estados_finais, 
                                                        conta*sizeof(*afdproduto->estados_finais));
                    break;
                
                }
                if (strstr(afdproduto->estado[i], afd2->estados_finais[k]) 
                    && strcmp(afd2->estados_finais[k], strstr(afdproduto->estado[i], afd2->estados_finais[k])) == 0){
                                                             
                    afdproduto->estados_finais[conta-1] = calloc(25, sizeof(afdproduto->estados_finais));
                    strcpy(afdproduto->estados_finais[conta-1], afdproduto->estado[i]);
                    conta++;
                    afdproduto->estados_finais = realloc(afdproduto->estados_finais, 
                                                        conta*sizeof(*afdproduto->estados_finais));                   
                }               
    
            }
        }
    }
    afdproduto->qtd_estados_finais = conta-1;

    return afdproduto;
}

afd *intersecao(afd *afdproduto, afd *afd1, afd *afd2){
    
    afdproduto = produto(afd1, afd2);
    afdproduto->estados_finais = calloc(1, sizeof(*afdproduto->estados_finais));
    
    int conta = 1;
    char A [25];

    for (int i = 0; i < afdproduto->qtd_estados; i++){
        
        for (int j = 0; j < afd1->qtd_estados_finais; j++){
            
            for (int k = 0; k < afd2->qtd_estados_finais; k++){
                
                strcpy(A, afd1->estados_finais[j]);
                strcat(A, afd2->estados_finais[k]);
                                   
                if (strcmp(afdproduto->estado[i], A) == 0){
                
                    afdproduto->estados_finais[conta-1] = calloc(25, sizeof(afdproduto->estados_finais));
                    strcpy(afdproduto->estados_finais[conta-1], afdproduto->estado[i]);
                    conta++;
                    afdproduto->estados_finais = realloc(afdproduto->estados_finais, 
                                                        conta*sizeof(*afdproduto->estados_finais));           
                }
            }                   
        }
    }
    
    afdproduto->qtd_estados_finais = conta-1;
}