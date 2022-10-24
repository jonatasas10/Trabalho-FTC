#include "main.h"
#include "complemento.h"
#include "gerarAFD.h"
#include "produto.h"
#include "reconhecer.h"
#include "minimizacao.h"

int main(int argc, char *argv[]){
    
   if (strcmp(argv[1], "--dot") == 0){
        
        afd *afd1 = calloc(1, sizeof(afd));
        FILE *AFD1 = fopen(argv[2], "r");

        if (!AFD1) {
            printf("Erro ao abrir arquivo de entrada\n");
            return -1;
        }
        cria_AFD(afd1, AFD1);
        
        if (strcmp(argv[3], "--output") == 0){
            visualizacao(afd1, argv[4]);
        }
        libera_memoria(afd1);
        fclose(AFD1);
    }
    else if (strcmp(argv[1], "--complemento") == 0){
        afd *afd1 = calloc(1, sizeof(afd));
        FILE *AFD1 = fopen(argv[2], "r");
        
        if (!AFD1) {
            printf("Erro ao abrir arquivo de entrada\n");
            return -1;
        }
        cria_AFD(afd1, AFD1);
        
        if (strcmp(argv[3], "--output") == 0){
            complemento(afd1);
            saida(afd1, argv[4]);
        }
        libera_memoria(afd1);
        fclose(AFD1);
    }
    else if (strcmp(argv[1], "--uniao") == 0){
        afd *afd1 = calloc(1, sizeof(afd));
        FILE *AFD1 = fopen(argv[2], "r");
        afd *afd2 = calloc(1, sizeof(afd));
        FILE *AFD2 = fopen(argv[3], "r");
        afd *afd3;
        
        if (!AFD1 || !AFD2) {
            printf("Erro ao abrir arquivos de entrada\n");
            return -1;
        }
        cria_AFD(afd1, AFD1);
        cria_AFD(afd2, AFD2);

        if (strcmp(argv[4], "--output") == 0){
            afd3 = uniao(afd3, afd1, afd2);
            saida(afd3, argv[5]);
        }

        libera_memoria(afd1);
        libera_memoria(afd2);
        libera_memoria(afd3);
        fclose(AFD1);
        fclose(AFD2);

    }
    else if (strcmp(argv[1], "--intersecao") == 0){
        
        afd *afd1 = calloc(1, sizeof(afd));      
        FILE *AFD1 = fopen(argv[2], "r");
        afd *afd2 = calloc(1, sizeof(afd));
        FILE *AFD2 = fopen(argv[3], "r");
        
        afd *afd3;
        
        if (!AFD1 || !AFD2) {
            printf("Erro ao abrir arquivos de entrada\n");
            return -1;
        }
        cria_AFD(afd1, AFD1);
        cria_AFD(afd2, AFD2);
    
        if (strcmp(argv[4], "--output") == 0){
            
            afd3 = intersecao(afd3, afd1, afd2);
            saida(afd3, argv[5]);
            
        }
        
        libera_memoria(afd1);
        libera_memoria(afd2);
        libera_memoria(afd3);
        fclose(AFD1);
        fclose(AFD2);
        
    }
    else if (strcmp(argv[1], "--reconhecer") == 0){
        afd *afd1 = calloc(1, sizeof(afd));
        FILE *AFD1 = fopen(argv[2], "r");
        FILE *a_palavras = fopen(argv[3], "r");
        FILE *palavras_aceitas = fopen(argv[5], "w");
        char *palavras = calloc(100,sizeof(char));

        if (!AFD1 || !a_palavras) {
            printf("Erro ao abrir arquivos de entrada\n");
            return -1;
        }
        cria_AFD(afd1, AFD1);
        
        if (strcmp(argv[4], "--output") == 0){
            
            while(fscanf(a_palavras, "%s\n", palavras) != EOF){
                
                fprintf(palavras_aceitas, "%d\n", _reconhecer(afd1, palavras)); 

            }
        }

        free(palavras);
        libera_memoria(afd1);
        fclose(AFD1);
        fclose(palavras_aceitas);
        fclose(a_palavras);
    }
    else if (strcmp(argv[1], "--minimizacao") == 0){
        afd *afd1 = calloc(1, sizeof(afd));
        FILE *AFD1 = fopen(argv[2], "r");

        if (!AFD1) {
            printf("Erro ao abrir arquivo de entrada\n");
            return -1;
        }
        cria_AFD(afd1, AFD1);
        
        if (strcmp(argv[3], "--output") == 0){
            minimizacao(afd1);
            saida(afd1, argv[4]);
        }
        libera_memoria(afd1);
        fclose(AFD1);
    }
  
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