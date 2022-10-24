#include "gerarAFD.h"

void cria_AFD(afd *entrada, FILE *afd_arq){

    fscanf(afd_arq, "%d", &entrada->qtd_estados);
    entrada->estado = calloc(sizeof(*entrada->estado),entrada->qtd_estados);
   
    for (int i = 0; i < entrada->qtd_estados; i++){
        
        entrada->estado[i] = calloc(sizeof(entrada->estado),25);
        fscanf(afd_arq, "%s", entrada->estado[i]);
    }

    fscanf(afd_arq, "%d", &entrada->qtd_alfabeto);
    entrada->alfabeto = calloc(sizeof(*entrada->alfabeto),entrada->qtd_alfabeto);
    
    for (int i = 0; i < entrada->qtd_alfabeto; i++){
        
        entrada->alfabeto[i] = calloc(sizeof(entrada->alfabeto), 1);
        fscanf(afd_arq, "%s", entrada->alfabeto[i]);
    }
    
    fscanf(afd_arq, "%d", &entrada->qtd_transicoes);
   
    entrada->transicao = calloc(sizeof(transicao), entrada->qtd_transicoes);
    
    for (int i = 0; i < entrada->qtd_transicoes; i++){
    
        fscanf(afd_arq, "%s%s%s", entrada->transicao[i].origem, 
                entrada->transicao[i].ler, entrada->transicao[i].destino);
        
    } 
    
    entrada->estado_inicial = calloc(sizeof(entrada->estado_inicial),25);
    fscanf(afd_arq, "%s", entrada->estado_inicial);

    fscanf(afd_arq, "%d", &entrada->qtd_estados_finais);
    entrada->estados_finais = calloc(sizeof(*entrada->estados_finais),entrada->qtd_estados_finais);
    
    for (int i = 0; i < entrada->qtd_estados_finais; i++){
        
        entrada->estados_finais[i] = calloc(sizeof(entrada->estados_finais[i]),25);
        fscanf(afd_arq, "%s", entrada->estados_finais[i]);
    }        
}

void saida(afd *afd1, char *afdsaida){
    FILE *arq = fopen(afdsaida, "w");
    fprintf(arq, "%d\n", afd1->qtd_estados);
    
    for (int i = 0; i < afd1->qtd_estados; i++){
        fprintf(arq, "%s\n",afd1->estado[i]);
    }
    
    fprintf(arq, "%d\n", afd1->qtd_alfabeto);

    for (int i = 0; i < afd1->qtd_alfabeto; i++){
        fprintf(arq, "%s\n", afd1->alfabeto[i]);
    }

    fprintf(arq, "%d\n",afd1->qtd_transicoes);
    
    for (int i = 0; i < afd1->qtd_transicoes; i++){
        fprintf(arq, "%s %s %s\n", afd1->transicao[i].origem, afd1->transicao[i].ler, afd1->transicao[i].destino);
    }
    fprintf(arq, "%s\n", afd1->estado_inicial);

    fprintf(arq, "%d\n", afd1->qtd_estados_finais);
    
    for (int i = 0; i < afd1->qtd_estados_finais; i++){
        fprintf(arq, "%s\n", afd1->estados_finais[i]);
    }
    fclose(arq);
}

void visualizacao(afd *saida, char *dot){
    
    FILE* arquivo = fopen(dot,"w");
    fprintf(arquivo, "digraph finite_state_machine {\n");
    fprintf(arquivo, "\tfontname=\"Helvetica,Arial,sans-serif\"\n");
    fprintf(arquivo, "\tnode [fontname=\"Helvetica,Arial,sans-serif\"]\n");
    fprintf(arquivo, "\tedge [fontname=\"Helvetica,Arial,sans-serif\"]\n");
    fprintf(arquivo, "\tnode [shape = point ]; qi");
    fprintf(arquivo, "\trankdir=LR;\n");

    fprintf(arquivo, "\tnode [shape = doublecircle, width=.75, height=.5];");
    
    for (int i = 0; i < saida->qtd_estados_finais; i++){
        
        fprintf(arquivo, "%s ", saida->estados_finais[i]);
    }
    fprintf(arquivo,";\n");
    fprintf(arquivo, "\tnode [shape = circle,width=.75, height=.05];\n");
    fprintf(arquivo, "\tqi -> %s;\n", saida->estado_inicial);
    
    for (int i = 0; i < saida->qtd_transicoes; i++){
    
        fprintf(arquivo,"\t%s -> %s [label = \"%s\"];\n", saida->transicao[i].origem,
                 saida->transicao[i].destino,saida->transicao[i].ler);
    }
     
    fprintf(arquivo,"}");
    fclose(arquivo);
}