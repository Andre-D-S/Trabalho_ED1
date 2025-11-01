#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "RegistroDeHumor.h"

//Cria o Nolista da lista duplamente encadeada
typedef struct nolista{
    RegistroDeHumor info;
    struct nolista *prox;
    struct nolista *ant;
}Nolista;

//Cria a lista
void CriarLista(Nolista** l){
    *l = NULL;
}

//Verifica se a lista está vazia
int EstaVazia(Nolista** l){
    if(*l == NULL)
        return 1;
    else
        return 0;
}

//Inseri um registro no fim da lista
void InserirNoFim(Nolista** l, RegistroDeHumor registro){
    Nolista* novo = (Nolista*)malloc(sizeof(Nolista));
    if (novo != NULL){
        novo->info = registro;
        novo->prox = NULL;
        if (EstaVazia(l)){ 
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

//Imprimi todos os registros da lista
void ImprimirTudo(Nolista** l){
    for(Nolista *p = *l; p != NULL; p = p->prox)
        ImprimirRegistro(p->info);
}

//Remove um registro da lista
void RemoverElemento(Nolista** l, int v){
    Nolista *p;
    for(p = *l; p != NULL && p->info.id != v ; p = p->prox);
    if(p == NULL)
        printf("\nREGISTRO NAO ENCONTRADO!\n");
    else{
        if(p->ant == NULL){
            *l = p->prox;
            if(p->prox != NULL)
                p->prox->ant = NULL;
            free(p);
        }
        else if(p->prox == NULL){
            p->ant->prox = NULL;
            free(p);
        }
        else{
            p->ant->prox = p->prox;
            p->prox->ant = p->ant;
            free(p);     
        }
        printf("\nREGISTRO REMOVIDO COM SUCESSO!\n");
    }
}

//Busca um humor informado pelo usuario
 void BuscarHumor(Nolista** l, int v){
    Nolista *p;
    int encontrou = 0;
    for(p = *l; p != NULL; p = p->prox)
        if(p->info.humor == v){
            ImprimirRegistro(p->info);
            encontrou++;
        }
    if(encontrou == 0)
        printf("\nNAO EXISTE REGISTRO COM ESSE HUMOR\n");
}


//Retorna a média de notas dos ultimos X dias
float MediaDasNotasUltimosX(Nolista** l, int x) {
    int totalElementos = 0;
    for (Nolista *p = *l; p != NULL; p = p->prox)
        totalElementos++;
    if(x <= 0){
        printf("\nQUANTIDADE INVALIDA, DEVE SER PELO MENOS 1\n");
        return 0.0;
    }
    if(x > totalElementos) 
        x = totalElementos;
        
    Nolista *p = *l;
    int inicio = totalElementos - x;
    for(int i = 0; i < inicio; i++)
        p = p->prox;
        
    float totalNotas = 0;
    int quantidade = 0;
    for(; p != NULL; p = p->prox){
        totalNotas += p->info.notaDoDia;
        quantidade++;
    }
    if (quantidade == 0) 
        return 0.0;
    
    return totalNotas / quantidade;
}


//Retorna o humor mais frequente dos ultimos X dias
Humor HumorMaisFrequenteUltimosX(Nolista** l, int x) {
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
        contagem[p->info.humor]++;
        
    int maxIndex = 0;
    for(int i = 1; i < 7; i++){
        if (contagem[i] > contagem[maxIndex])
            maxIndex = i;
    }
    return (Humor)maxIndex;
}


//Mostra todos os motivos do humor X
void MostrarMotivosPorHumorX(Nolista** l, int humorDesejado){
    int encontrou = 0;
    // Primeiro loop: verificar se existe pelo menos um registro com o humor desejado
    for(Nolista *p = *l; p != NULL; p = p->prox){
        if (p->info.humor == humorDesejado) {
            encontrou = 1;
            break;
        }
    }
    // Se achou, imprime o cabeçalho e os registros
    if(encontrou){
        printf("\n---MOTIVOS PARA O HUMOR %s---\n", Identificador[humorDesejado]);
        for(Nolista *p = *l; p != NULL; p = p->prox){
            if (p->info.humor == humorDesejado) {
                printf("ID: %d | DATA: %s | MOTIVO: %s\n", p->info.id, p->info.data, p->info.motivo);
            }
        }
        printf("---------FIM DOS MOTIVOS---------\n");
    }
    else{
        printf("\nNENHUM REGISTRO ENCONTRADO COM ESTE HUMOR!\n");
    }
}

//Salva os registros no arquivo.txt
void SalvarRegistrosEmArquivo(Nolista** l, const char* nomeArquivo){
    //Abre o arquivo para modificação
    FILE *arquivo = fopen(nomeArquivo, "w");
    if(arquivo == NULL){
        printf("ERRO AO ABRIR O ARQUIVO PARA SALVAR OS REGISTROS!\n");
        return;
    }
    
    //O for roda enquanto existirem registros
    for(Nolista *p = *l; p != NULL; p = p->prox){
        //Em motivos o uso da aspa serve para que na leitura do arquivo os motivos sejam lidos corretamente
        //fprintf inseri as informações no arquivo
        fprintf(arquivo, "%d %s %d \"%s\" %d\n", 
            p->info.id, 
            p->info.data, 
            p->info.humor, 
            p->info.motivo, 
            p->info.notaDoDia);
    }
    
    fclose(arquivo);
    printf("\nREGISTROS SALVOS EM ARQUIVO COM SUCESSO!\n");
}

//Carrega o arquivo e cria a lista
void CarregarRegistrosDoArquivo(Nolista** l){
    FILE *arquivo = fopen("arquivo.txt", "r");
    if (arquivo == NULL) {
        printf("\nARQUIVO NAO ENCONTRADO!\n");
        return;
    }
    
    //Registor de humor temporario e char para que a leitura das linhas, onde cada linha representa um registro
    RegistroDeHumor temp;
    char linha[200];
    
    //O while vai rodar enquanto existirem linhas no arquivo
    while(fgets(linha, sizeof(linha), arquivo) != NULL){
        //char especial para leitura failitada dos motivos
        char motivoComAspas[105];
        //Le os arquivos no formato esperado
        //O char motivoComAspas serve para que os motivos não sejam cortados na leitura
        //(int*)&temp.humor serve para que o sscanf leia o humor como int
        if (sscanf(linha, "%d %10s %d \"%[^\"]\" %d", &temp.id, temp.data, (int*)&temp.humor, motivoComAspas, &temp.notaDoDia) == 5){
            //strncpy serve para que o motivoComAspas passe suas informações para o temp.motivo
            strncpy(temp.motivo, motivoComAspas, sizeof(temp.motivo));
            //Inseri o registro da linha em questão no lista
            InserirNoFim(l, temp);

            //Atualiza o contadorID
            extern int contadorID;
            if(temp.id >= contadorID){
                contadorID = temp.id + 1;
            }
        }
    }

    fclose(arquivo);
    printf("\nREGISTROS CARREGADOS COM SUCESSO!\n");
}