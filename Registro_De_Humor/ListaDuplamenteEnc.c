#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "RegistroDeHumor.h"

//Cria o Nó da lista da lista duplamente encadeada
typedef struct nolista{
    RegistroDeHumor *info;
    struct nolista *prox;
    struct nolista *ant;
} Nolista;

//Cria a lista
void CriarLista(Nolista** l){
    *l = NULL;
}

//Verifica se a lista está vazia
int EstaVazia(Nolista** l){
    return *l == NULL;
}

//Insere um registro no fim da lista
void InserirNoFim(Nolista** l, RegistroDeHumor *registro){
    Nolista* novo = (Nolista*)malloc(sizeof(Nolista));
    if(novo != NULL){
        novo->info = registro;
        novo->prox = NULL;
        if(EstaVazia(l)){ 
            novo->ant = NULL;
            *l = novo;
        } 
        else{  
            Nolista* p;
            for (p = *l; p->prox != NULL; p = p->prox);
            p->prox = novo;   
            novo->ant = p;    
        }
    } 
    else 
        printf("\nNAO FOI POSSIVEL ALOCAR ESPAÇO\n");
}

//Imprime todos os registros da lista
void ImprimirTudo(Nolista** l){
    for(Nolista *p = *l; p != NULL; p = p->prox)
        ImprimirRegistro(p->info);
}

//Remove um registro da lista
void RemoverElemento(Nolista** l, int v){
    Nolista *p;
    for(p = *l; p != NULL && p->info->id != v ; p = p->prox);
    if(p == NULL)
        printf("\nREGISTRO NAO ENCONTRADO!\n");
    else{
        if(p->ant == NULL){
            *l = p->prox;
            if(p->prox != NULL)
                p->prox->ant = NULL;
        }
        else if(p->prox == NULL){
            p->ant->prox = NULL;
        }
        else{
            p->ant->prox = p->prox;
            p->prox->ant = p->ant;     
        }
        LiberarRegistro(p->info);
        free(p);
        printf("\nREGISTRO REMOVIDO COM SUCESSO!\n");
    }
}

//Busca um humor informado pelo usuario
void BuscarHumor(Nolista** l, int v){
    int encontrou = 0;
    for(Nolista *p = *l; p != NULL; p = p->prox){
        if(p->info->humor == v){
            ImprimirRegistro(p->info);
            encontrou++;
        }
    }
    if(encontrou == 0)
        printf("\nNAO EXISTE REGISTRO COM ESSE HUMOR\n");
}

//Retorna a média de notas dos últimos X dias
float MediaDasNotasUltimosX(Nolista** l, int x){
    int totalElementos = 0;
    
    for(Nolista *p = *l; p != NULL; p = p->prox)
        totalElementos++;
    
    if(x > totalElementos) 
        x = totalElementos;
        
    Nolista *p = *l;
    int inicio = totalElementos - x;
    
    for(int i = 0; i < inicio; i++)
        p = p->prox;
        
    float totalNotas = 0;
    int quantidade = 0;
    
    for(; p != NULL; p = p->prox){
        totalNotas += p->info->notaDoDia;
        quantidade++;
    }
    return totalNotas / quantidade;
}

//Retorna o humor mais frequente dos últimos X dias
Humor HumorMaisFrequenteUltimosX(Nolista** l, int x){
    int totalElementos = 0;
    for(Nolista *p = *l; p != NULL; p = p->prox)
        totalElementos++;
    if(x > totalElementos)
        x = totalElementos;
        
    Nolista *p = *l;
    int inicio = totalElementos - x;
    for(int i = 0; i < inicio; i++)
        p = p->prox;
        
    int contagem[7] = {0};
    for(; p != NULL; p = p->prox)
        contagem[p->info->humor]++;
        
    int maxIndex = 0;
    for(int i = 1; i < 7; i++){
        if(contagem[i] > contagem[maxIndex])
            maxIndex = i;
    }
    return (Humor)maxIndex;
}

//Mostrar motivos por humor X
void MostrarMotivosPorHumorX(Nolista** l, int humorDesejado){
    int encontrou = 0;
    for(Nolista *p = *l; p != NULL; p = p->prox){
        if (p->info->humor == humorDesejado) {
            encontrou = 1;
            break;
        }
    }
    if(encontrou){
        printf("\n---MOTIVOS PARA O HUMOR %s---\n", Identificador[humorDesejado]);
        for(Nolista *p = *l; p != NULL; p = p->prox){
            if (p->info->humor == humorDesejado) {
                printf("ID: %d | DATA: %s | MOTIVO: %s\n", p->info->id, p->info->data, p->info->motivo);
            }
        }
        printf("---------FIM DOS MOTIVOS---------\n");
    }
    else{
        printf("\nNENHUM REGISTRO ENCONTRADO COM ESTE HUMOR!\n");
    }
}

//Salvar registros em arquivo
void SalvarRegistrosEmArquivo(Nolista** l, char* nomeArquivo){
    FILE *arquivo = fopen(nomeArquivo, "w");
    if(arquivo == NULL){
        printf("ERRO AO ABRIR O ARQUIVO PARA SALVAR OS REGISTROS!\n");
    }
    
    for(Nolista *p = *l; p != NULL; p = p->prox){
        fprintf(arquivo, "%d %s %d \"%s\" %d\n", 
            p->info->id, 
            p->info->data, 
            p->info->humor, 
            p->info->motivo, 
            p->info->notaDoDia);
    }
    
    fclose(arquivo);
    printf("\nREGISTROS SALVOS EM ARQUIVO COM SUCESSO!\n");
}

//Carregar os registros salvos no arquivo
void CarregarRegistrosDoArquivo(Nolista** l){
    FILE *arquivo = fopen("arquivo.txt", "r");
    if(arquivo == NULL){
        printf("\nARQUIVO NAO ENCONTRADO!\n");
        return;
    }
    
    char linha[200];

    while(fgets(linha, sizeof(linha), arquivo) != NULL){
        //Aloca memória para um novo registro
        RegistroDeHumor *r = (RegistroDeHumor*)malloc(sizeof(RegistroDeHumor));
        if(r == NULL){
            printf("\nERRO AO ALOCAR MEMORIA!\n");
            fclose(arquivo);
            return;
        }

        //Lê os campos
        if(sscanf(linha, "%d %10s %d \"%[^\"]\" %d",
                   &r->id, r->data, (int*)&r->humor, r->motivo, &r->notaDoDia) == 5){

            InserirNoFim(l, r);

            extern int contadorID;
            contadorID = r->id + 1;
        } 
        else{
            //Caso a linha não tenha o formato esperado, libera e ignora
            free(r);
        }
    }
    fclose(arquivo);
    printf("\nREGISTROS CARREGADOS COM SUCESSO!\n");
}




