#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


void visualizacao(afd *saida){
    FILE* arquivo = fopen("/home/jonatas/Jonatas/VSCODE/FTC/afd.txt","w");
    fprintf(arquivo, "digraph finite_state_machine {\n");
    fprintf(arquivo, "fontname=\"Helvetica,Arial,sans-serif\"\n");
    fprintf(arquivo, "node [fontname=\"Helvetica,Arial,sans-serif\"]\n");
    fprintf(arquivo, "edge [fontname=\"Helvetica,Arial,sans-serif\"]\n");
    fprintf(arquivo, "\trankdir=LR;\n");

    fprintf(arquivo, "\tnode [shape = doublecircle, width=.75, height=.5]\;");
    for (int i = 0; i < saida->qtd_estados_finais; i++){
        fprintf(arquivo, "%s ", saida->estados_finais[i]);
    }
    fprintf(arquivo,";\n");
    fprintf(arquivo, "\tnode [shape = circle,width=.75, height=.05];\n");
    for (int i = 0; i < saida->qtd_transicoes; i++){
        fprintf(arquivo,"\t%s -> %s [label = \"%s\"];\n", saida->transicao[i].origem, saida->transicao[i].destino,saida->transicao[i].ler);
    }
   
    
    fprintf(arquivo,"}");
    fclose(arquivo);
}


void cria_AFD(afd *entrada){
    entrada->qtd_estados = 2;
    entrada->estado = calloc(sizeof(*entrada->estado),2);

    printf("ESTADO:\n");
    for (int i = 0; i < entrada->qtd_estados; i++){
        entrada->estado[i] = calloc(sizeof(entrada->estado),20);
        scanf("%s", entrada->estado[i]);
        fflush(stdin);
    }

    entrada->qtd_alfabeto = 2;
    entrada->alfabeto = calloc(sizeof(*entrada->alfabeto),entrada->qtd_alfabeto);
    printf("ALFABETO:\n");
    for (int i = 0; i < entrada->qtd_alfabeto; i++){
        entrada->alfabeto[i] = calloc(sizeof(entrada->alfabeto), 1);
        scanf("%s", entrada->alfabeto[i]);
    }
    
    entrada->qtd_transicoes = 2;
   printf("TRANSICOES:\n");
   entrada->transicao = calloc(sizeof(transicao), entrada->qtd_transicoes);
    for (int i = 0; i < entrada->qtd_transicoes; i++){
        scanf("%s", entrada->transicao[i].origem);
        scanf("%s", entrada->transicao[i].ler);
        scanf("%s", entrada->transicao[i].destino);  
        fflush(stdin);         
    }
    
    printf("ESTADO INICIAL:\n");
    entrada->estado_inicial = calloc(sizeof(entrada->estado_inicial),20);
    scanf("%s", entrada->estado_inicial);

    entrada->qtd_estados_finais = 1;
    entrada->estados_finais = calloc(sizeof(*entrada->estados_finais),entrada->qtd_estados_finais);
    
    for (int i = 0; i < entrada->qtd_estados_finais; i++){
        entrada->estados_finais[i] = calloc(sizeof(entrada->estados_finais[i]),20);
        scanf("%s", entrada->estados_finais[i]);
        fflush(stdin);
    }
    
}

int main(){
    
    afd *nome = calloc(1,sizeof(afd));
    cria_AFD(nome);
    visualizacao(nome);
    printf("RESULTADO\n");
    
    for (int i = 0; i < 2; i++){
        printf("%s\n", nome->transicao[i].origem);
         printf("%s\n", nome->transicao[i].ler);
          printf("%s\n", nome->transicao[i].destino);
    }
    return 0;
}