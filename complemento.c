#include "complemento.h"

void complemento (afd *afd){
    
    int diferenca = afd->qtd_estados - afd->qtd_estados_finais;
    char **estados_finais_c = calloc(sizeof(char*),diferenca);
    
    for (int i = 0; i < diferenca; i++){
    
        estados_finais_c[i] = calloc(sizeof(char), 25);
    }
    
    int i,j,contador =0;

    for (i = 0; i < afd->qtd_estados; i++){
        
        for (j = 0; j < afd->qtd_estados_finais; j++){
            
            if (strcmp(afd->estado[i], afd->estados_finais[j]) == 0) break;
           
        }
        
        if (j == afd->qtd_estados_finais){

            if (!(verifica_existencia(estados_finais_c, contador, afd->estado[i]))){
                
                strcpy(estados_finais_c[contador], afd->estado[i]);
                contador++;
            }
        }       
    }
    for(int i = 0; i < afd->qtd_estados_finais; i++) free(afd->estados_finais[i]);
    
    free(afd->estados_finais);
    
    afd->estados_finais = estados_finais_c;

    afd->qtd_estados_finais = diferenca;
       
}
int verifica_existencia(char **comp, int x, char *e){
    
    for (int i = 0; i < x; i++){
        
        if (strcmp(e, comp[i]) == 0) return 1;
    }
    return 0;
}