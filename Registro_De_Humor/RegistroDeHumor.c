#include <stdio.h>
#include <stdlib.h>

//Enum de todos os humores
typedef enum{
    FELIZ,
    TRISTE,        
    ANSIOSO,
    CANSADO,
    MOTIVADO,
    ESTRESSADO,
    NEUTRO        
}Humor;

//Estrutura de um registro de humor
typedef struct registrodehumor{
    int id;
    char data[11];
    Humor humor;
    char motivo[101];
    int notaDoDia;
}RegistroDeHumor;

//ID dos registros
int contadorID = 1;

//Cria um registro de humor
RegistroDeHumor* criarRegistro(){
    RegistroDeHumor *novo = (RegistroDeHumor*)malloc(sizeof(RegistroDeHumor));
    if(novo != NULL){
        int numerohumor;
        novo->id = contadorID++;
        
        printf("\nINSIRA A DATA (DD/MM/AA): ");
        scanf("%10[^\n]", novo->data);
        setbuf(stdin, NULL);
        
        do{
            printf("COMO ESTÁ SE SENTINDO?\n");
            printf("0 - FELIZ\n1 - TRISTE\n2 - ANSIOSO\n3 - CANSADO\n4 - MOTIVADO\n5 - ESTRESSADO\n6 - NEUTRO\n");
            printf("ESCOLHA UMA OPÇÃO (0 a 6): ");
            scanf("%d", &numerohumor);
            if(numerohumor < 0 || numerohumor > 6)
                printf("ESCOLHA UM VALOR ENTRE 0 A 6\n");         
        } 
        while(numerohumor < 0 || numerohumor > 6);
        novo->humor = numerohumor;
        
        printf("ESCREVA O MOTIVO DESSE HUMOR: ");
        getchar(); //Limpar Buffer
        scanf("%99[^\n]", novo->motivo);
        setbuf(stdin, NULL);
        
        do{
            printf("DÊ UMA NOTA PARA ESSE DIA (0 a 10): ");
            scanf("%d", &novo->notaDoDia);
            if(novo->notaDoDia < 0 || novo->notaDoDia > 10)
                printf("NOTA INVALIDA, APENAS VALORES ENTRE 0 E 10\n");         
        } 
        while(novo->notaDoDia < 0 || novo->notaDoDia > 10);
        
        return novo;
    }
    else{
        printf("NÃO FOI POSSIVEL ALOCAR ESPAÇO\n");
        return NULL;
    }
}

//Identifica o humor para printa-lo quando pedido
const char* Identificador[] = {
    "FELIZ", "TRISTE", "ANSIOSO", "CANSADO", "MOTIVADO", "ESTRESSADO", "NEUTRO"
};

//Imprimi um registro
void ImprimirRegistro(RegistroDeHumor *r){
    if(r != NULL){
        printf("\n---REGISTRO IMPRESSO---\n");
        printf("ID DESSE REGISTRO: %d\n", r->id);
        printf("DATA: %s\n", r->data);
        printf("HUMOR DESSE DIA: %s\n", Identificador[r->humor]);
        printf("MOTIVO DO HUMOR: %s\n", r->motivo);
        printf("NOTA DO DIA: %d\n", r->notaDoDia);
        printf("-----------------------\n");
    }
    else
        printf("\nNÃO EXISTEM REGISTROS\n");
}

//Libera o registro
void LiberarRegistro(RegistroDeHumor *r){
    if(r != NULL){
        free(r);
        r = NULL;
    }
    else
        printf("O REGISTRO JÁ ESTA VAZIO\n");
}
