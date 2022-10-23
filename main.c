#include "main.h"
#include "complemento.h"
#include "gerarAFD.h"
#include "produto.h"
#include "reconhecer.h"

void minimizacao(afd *afd1){
    
    char **estados_alcancaveis = calloc(1,sizeof(char*));
    estados_alcancaveis[0] = calloc(25, sizeof(char));
    afd *afd_min = calloc(1, sizeof(afd));
    afd_min->transicao = calloc(100,sizeof(*afd_min->transicao));
    strcpy(estados_alcancaveis[0], afd1->estado_inicial);
   
    int qtd_trans = 0, alc = 0, conta = 0;

    for (int i = 0; i < afd1->qtd_estados; i++){
        for (int j = 0; j < afd1->qtd_transicoes; j++){
            for (int k = 0; k < alc+1; k++){
            if (strcmp(estados_alcancaveis[k], afd1->transicao[j].origem) == 0
                && strcmp(afd1->estado[i], afd1->transicao[j].destino) == 0 
                && !verifica_existencia(estados_alcancaveis, alc+1, afd1->estado[i])
                ){   
                //printf("ALC %s\n", estados_alcancaveis[alc]);                
                alc++;                
                estados_alcancaveis = realloc(estados_alcancaveis, (alc+1)*sizeof(char*));
                estados_alcancaveis[alc] = calloc(25,sizeof(char));
                strcpy(estados_alcancaveis[alc], afd1->estado[i]);                
            }}
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

    int n = 0, F = 0, NF = 0;
    for (int i = 0; i <= alc; i++){
        for (int j = 0; j < afd1->qtd_estados_finais; j++){
            //printf("%d i\n",i);
//printf("%s %s %s\n", estados_alcancaveis[i], conjunto[1].estado[NF], afd1->estados_finais[j]);

            if (strcmp(estados_alcancaveis[i], afd1->estados_finais[j]) == 0 
                && !verifica_existencia(conjunto[1].estado, NF, estados_alcancaveis[i]) 
                && !verifica_existencia(conjunto[0].estado, F, afd1->estados_finais[j])
                ){
                strcpy(conjunto[0].estado[F], afd1->estados_finais[j]);
                //printf("F = %s\n", conjunto[0].estado[F]);

                F++;
            }

            else if (strcmp(estados_alcancaveis[i], afd1->estados_finais[j]) != 0
                    && !verifica_existencia(conjunto[1].estado, NF, estados_alcancaveis[i])
                    && !verifica_existencia(conjunto[0].estado, F,  estados_alcancaveis[i])
                    && !verifica_existencia(conjunto[0].estado, F, afd1->estados_finais[j])
                    ){
                    strcpy(conjunto[1].estado[NF], estados_alcancaveis[i]);
                    //printf("NF = %s\n", conjunto[1].estado[NF]);
                    //printf("ENTROU %s %s %s\n", estados_alcancaveis[i], conjunto[1].estado[NF], afd1->estados_finais[j]);
                    NF++;
                
            }
            

    //NF++
// printf("W J[%d]%s %s %s\n",j, estados_alcancaveis[i], conjunto[1].estado[NF], afd1->estados_finais[j]);
//NF--;
           
        }
        if(!verifica_existencia(conjunto[1].estado, NF, estados_alcancaveis[i])
                    && !verifica_existencia(conjunto[0].estado, F,  estados_alcancaveis[i])

            ){
               
                strcpy(conjunto[1].estado[NF], estados_alcancaveis[i]);
                //printf("NF = %s\n", conjunto[1].estado[NF]);
                NF++;
            }

    }
    int vet [2] = {F,NF};
    int x = 0, y = 0, aux = 0;
    //tam = sizeof(conjunto[0].estado);
    for (int i = 0; i < 2; i++) printf("TAM %d\n",vet[i]);
    //printf("TAM %d\n",tam);
    int Z;;
   
        for (int i = 0; i < n+2; i++){
            if (i < 2) {
                x = vet[i];
                y = vet[i];
            }
            for (int j = 0; j < x; j++){
                for (int j2 = 0; j2 < x; j2++){
                    if (j != j2){
                        Z = verifica(afd_min, conjunto[i].estado[j], conjunto[i].estado[j2], conjunto[i].estado,
                        qtd_trans, y);
                        // retorna 0 se ambos estão no mesmo conjunto ou em conjunto diferentes
                        if (Z == 1) {
                            printf("Z %d DIST %s %s\n",Z, conjunto[i].estado[j], conjunto[i].estado[j2]);
                           if (!verifica_existencia(conjunto[2+n].estado, x, conjunto[i].estado[j2])){
                            strcpy(conjunto[2+n].estado[aux], conjunto[i].estado[j2]);
                          
                            n++;
                        }

                        }
                    }

                }
            }
                
        }

        for (int i = 0; i < n+2; i++){
            for (int j = 0; j < 3-i ; j++){
                
                printf("%s ", conjunto[i].estado[j]);
            }
            printf("\n");
        }

   // }

    for (int i = 0; i < F; i++) printf("CONJUNTO F = %s\n", conjunto[0].estado[i]);
    for (int i = 0; i < NF; i++){
        
        printf("CONJUNTO NF = %s\n", conjunto[1].estado[i]);
    }
    for (int i = 0; i < qtd_trans; i++){
        //printf("%s - %s - %s\n",afd_min->transicao[i].origem, afd_min->transicao[i].ler,
        //afd_min->transicao[i].destino);
    }
    for (int i = 0; i <= alc; i++){
        printf("Alcancavel %s\n", estados_alcancaveis[i]);
    }
}

void atualiza_conjuntos(char **conjunto, int pos, int TAM){

    for (int i = pos-1; i < TAM-1; i++){
        //
    }
}

int verifica(afd *min, char *E, char *e, char **conjunto, int TAM, int tamc){
    int a = 0, b = 0;
    
    //for (int i = 0; i < 1; i++){
       a = 0; b = 0;
        
                                         
    

    for (int j = 0; j < TAM; j++){
          a = 0;          
        if (strcmp(E, min->transicao[j].origem) == 0){
                
            for (int j2 = 0; j2 < TAM; j2++){
                    
                    if (strcmp(e, min->transicao[j2].origem) == 0){
                        
                        if (strcmp(min->transicao[j].ler, min->transicao[j2].ler) == 0
                        && verifica_existencia(conjunto, tamc,  min->transicao[j].destino)
                         && verifica_existencia(conjunto, tamc,  min->transicao[j2].destino)
                        ){
                            //printf("contagem %d %d %d Q %s\n",j,j2);
                            //printf("%s %s %s\n",E, min->transicao[j].ler, min->transicao[j].destino);
                            //printf("%s %s %s\n",e, min->transicao[j2].ler, min->transicao[j2].destino);
                            //printf("ESTAO\n");
                            a = 1;
                            break;
                            
                        }
                        if (!verifica_existencia(conjunto, tamc,  min->transicao[j].destino)
                            && !verifica_existencia(conjunto, tamc,  min->transicao[j2].destino)
                            ){
                            //printf("%s %s %s\n",E, min->transicao[j].ler, min->transicao[j].destino);
                            //printf("%s %s %s\n",e, min->transicao[j2].ler, min->transicao[j2].destino);
                            //printf("NAO %d\n",a);
                            return 2;
                        }  
                          if (!verifica_existencia(conjunto, tamc,  min->transicao[j].destino)
                            && !verifica_existencia(conjunto, tamc,  min->transicao[j2].destino)
                            || verifica_existencia(conjunto, tamc,  min->transicao[j].destino)
                            && verifica_existencia(conjunto, tamc,  min->transicao[j2].destino)
                            ){
                            //printf("%s %s %s\n",E, min->transicao[j].ler, min->transicao[j].destino);
                            //printf("%s %s %s\n",e, min->transicao[j2].ler, min->transicao[j2].destino);
                            //printf("TALVEZ %d\n",a);
                            
                        }                      
                        
                    }
                    
                
            }       
        }
        
    }           
    //printf("AAAA %d\n",a);
         return 1;
    
   // }
   
}

int main(){
    FILE *AFD1 = fopen("/home/jonatas/Jonatas/VSCODE/FTC/AFD4.txt", "r");
    FILE *AFD2 = fopen("/home/jonatas/Jonatas/VSCODE/FTC/AFD3.txt", "r");
    system("clear"); 
    afd *afd1 = calloc(1,sizeof(afd));
    //afd *afd2 = calloc(1,sizeof(afd));
    cria_AFD(afd1, AFD1);
    //cria_AFD(afd2, AFD2);
    //afd *afd3 = produto(afd1,afd2);
    //afd *afd3 = uniao(afd3, afd1, afd2);
    //complemento(afd3);
    //afd *afd3 = intersecao(afd3,afd1,afd2);
    //complemento(afd3);
    //printf("RESULTADO %d\n", _reconhecer(afd2, "10101"));
    visualizacao(afd1);
    minimizacao((afd1));
    libera_memoria(afd1);
    //libera_memoria(afd2);
    //libera_memoria(afd3);
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