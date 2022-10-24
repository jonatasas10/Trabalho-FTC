#include "minimizacao.h"
#include "complemento.h"
#include "gerarAFD.h"
void minimizacao(afd *afd1){
    
    char **estados_alcancaveis = calloc(1,sizeof(char*));
    estados_alcancaveis[0] = calloc(25, sizeof(char));
    afd *afd_min = calloc(1, sizeof(afd));
    afd_min->transicao = calloc(100,sizeof(*afd_min->transicao));
    strcpy(estados_alcancaveis[0], afd1->estado_inicial);
       
    int qtd_trans = 0, alc = 0, conta = 2;

    for (int i = 0; i < afd1->qtd_estados; i++){
        
        for (int j = 0; j < afd1->qtd_transicoes; j++){
        
            for (int k = 0; k < alc+1; k++){
        
                if (strcmp(estados_alcancaveis[k], afd1->transicao[j].origem) == 0
                    && strcmp(afd1->estado[i], afd1->transicao[j].destino) == 0 
                    && !verifica_existencia(estados_alcancaveis, alc+1, afd1->estado[i])
                    ){   
                            
                    alc++;                
                    estados_alcancaveis = realloc(estados_alcancaveis, (alc+1)*sizeof(char*));
                    estados_alcancaveis[alc] = calloc(25,sizeof(char));
                    strcpy(estados_alcancaveis[alc], afd1->estado[i]);                
                }
            }
        }
    }
    
    for (int i = 0; i < afd1->qtd_transicoes; i++){
        for (int j = 0; j <= alc; j++){
            
            if (strcmp(estados_alcancaveis[j], afd1->transicao[i].origem) == 0 ){
                    strcpy(afd_min->transicao[qtd_trans].origem, afd1->transicao[i].origem);
                    strcpy(afd_min->transicao[qtd_trans].ler, afd1->transicao[i].ler);
                    strcpy(afd_min->transicao[qtd_trans].destino, afd1->transicao[i].destino);
                    qtd_trans++;
                    
            }
        }
    }

    conjuntos conjunto[20];
    
    for (int i = 0; i < 20; i++){
        conjunto[i].estado = calloc(25, sizeof(*conjunto[i].estado));
        for (int j = 0; j < 25; j++){
            conjunto[i].estado[j] = calloc(25,sizeof(conjunto[i].estado));
            
        }
        
    }

    int n = 2, F = 0, NF = 0;
    for (int i = 0; i <= alc; i++){
  
        for (int j = 0; j < afd1->qtd_estados_finais; j++){
  
            if (strcmp(estados_alcancaveis[i], afd1->estados_finais[j]) == 0 
                && !verifica_existencia(conjunto[1].estado, NF, estados_alcancaveis[i]) 
                && !verifica_existencia(conjunto[0].estado, F, afd1->estados_finais[j])
                ){
                strcpy(conjunto[0].estado[F], afd1->estados_finais[j]);                
                F++;
            }

            else if (strcmp(estados_alcancaveis[i], afd1->estados_finais[j]) != 0
                    && !verifica_existencia(conjunto[1].estado, NF, estados_alcancaveis[i])
                    && !verifica_existencia(conjunto[0].estado, F,  estados_alcancaveis[i])
                    && !verifica_existencia(conjunto[0].estado, F, afd1->estados_finais[j])
                    ){
                    strcpy(conjunto[1].estado[NF], estados_alcancaveis[i]);                    
                    NF++;
                
            }
        
           
        }
        if(!verifica_existencia(conjunto[1].estado, NF, estados_alcancaveis[i])
                    && !verifica_existencia(conjunto[0].estado, F,  estados_alcancaveis[i])

            ){
               
                strcpy(conjunto[1].estado[NF], estados_alcancaveis[i]);                
                NF++;
            }

    }
    int vet [25] = {F,NF};
   

    int x = 0, y = 0, aux = 0, fim = 0;
    
    for (int i = 0; i < 2; i++) printf("TAM %d\n",vet[i]);
    
    int ver;
   
    for (int i = 0; i < n && fim == 0 && n < 20; i++){
        if (i < 2) {
            x = vet[i];
            
        }
        else{
            x = aux;
            
        }
        aux = 0;
        for (int j = 0; j < x; j++){
            
            for (int j2 = j; j2 < x; j2++){
                if (j != j2){
                    
                    ver = verifica(afd_min, conjunto[i].estado[j], conjunto[i].estado[j2], conjunto[i].estado,
                    qtd_trans, x);
                    
                    if(ver){
                        if (conta == n) {
                            aux--;
                            
                        }
                        
                        strcpy(conjunto[conta].estado[aux], conjunto[i].estado[j2]);
                        atualiza_conjuntos(conjunto[i].estado, j2, x);
                        aux++;                        
                        
                        x--;
                        vet[i] = x;
                        vet[conta] = aux;
                       
                        conta = n;
                        
                    }                                                                               
                    
                    if (n > 2 && verifica_existencia(conjunto[conta-1].estado, x, conjunto[i].estado[j2])){
                        fim = 1;                         
                        break; //sem mudanças no último passo
                    }                   

                }
            }       
                       
        }
        n++;
    }

    if (conta == x) conta++;
    //mostra(conjunto,conta, vet);
    afd_min->estado = calloc (conta,sizeof(*afd_min->estado));
    afd_min->estado_inicial = calloc(25,sizeof(afd_min->estado_inicial));
    

    for (int j = 0; j < conta; j++){
        afd_min->estado[j] = calloc(25,sizeof(afd_min->estado));
        for (int k = 0; k < vet[j]; k++){
            strcat(afd_min->estado[j], conjunto[j].estado[k]);
        }
          printf("%s\n", afd_min->estado[j]);             
    }
    strcpy(afd_min->estado_inicial, afd_min->estado[0]);

    printf("\n");
    int qtd_transicao = 0;
    for (int i = 0; i < qtd_trans; i++){
        for (int j = 0; j < conta; j++){
            if (strstr(afd_min->estado[j], afd_min->transicao[i].origem) 
            && strcmp(afd_min->estado[j],strstr(afd_min->estado[j], afd_min->transicao[i].origem)) == 0
            ){
                strcpy(afd_min->transicao[qtd_transicao].origem, afd_min->estado[j]);
                
                for (int k = 0; k < conta; k++){
                    if (strstr(afd_min->estado[k], afd_min->transicao[i].destino) 
                    && strcmp(afd_min->estado[k],strstr(afd_min->estado[k], afd_min->transicao[i].destino)) == 0
                    && strstr(afd_min->estado[k], afd_min->transicao[i].destino) 
                    && strcmp(afd_min->estado[k],strstr(afd_min->estado[k], afd_min->transicao[i].destino)) == 0
                    ){
                        strcpy(afd_min->transicao[qtd_transicao].destino, afd_min->estado[k]);
                    }
            }
                qtd_transicao++;
                break;
            }
            
        }
        
    }
    afd_min->qtd_estados = conta;
    afd_min->estados_finais = calloc(1,sizeof(*afd_min->estados_finais));
    afd_min->estados_finais[0] = calloc(25,sizeof(afd_min->estados_finais));   
    strcpy(afd_min->estados_finais[0], afd1->estados_finais[0]);
    strcpy(afd_min->estado_inicial, afd_min->estado[0]);
    afd_min->qtd_estados_finais = 1;
    afd_min->qtd_transicoes = qtd_transicao;
    visualizacao(afd_min, "abc.dot");
    
}
void mostra(conjuntos *conjuntos,int n, int *x){
    
    for (int i = 0; i < n; i++){
        printf("[%d] [%d]",i,x[i]);
        for (int j = 0; j < x[i]; j++){
            printf("%s ",conjuntos[i].estado[j]);
            
        }    

       printf("\n");
    }
   
}

void atualiza_conjuntos(char **conjunto, int pos, int TAM){

    for (int i = pos; i < TAM-1; i++){
        
        strcpy(conjunto[i], conjunto[i+1]);

    }
    strcpy(conjunto[TAM-1], "X");
   
}

int verifica(afd *min, char *E, char *e, char **conjunto, int TAM, int tamc){

    for (int j = 0; j < TAM; j++){
                   
        if (strcmp(E, min->transicao[j].origem) == 0){
                
            for (int j2 = 0; j2 < TAM; j2++){
                    
                if (strcmp(e, min->transicao[j2].origem) == 0){
                    
                    if (strcmp(min->transicao[j].ler, min->transicao[j2].ler) == 0){
                                               
                        if(!verifica_existencia(conjunto, tamc, min->transicao[j].destino)
                        && verifica_existencia(conjunto, tamc, min->transicao[j2].destino)
                        || verifica_existencia(conjunto, tamc, min->transicao[j].destino)
                        && !verifica_existencia(conjunto, tamc, min->transicao[j2].destino)
                        ){
                            
                            return 1;
                        }
                        
                    }                                                             
                    
                }
                                    
            }       
        }
        
    }           
    return 0;     
   
}