#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RegistroDeHumor.h"
#include "ListaDuplamenteEnc.h"

int main() {
    Nolista* lista;
    CriarLista(&lista);
    
    CarregarRegistrosDoArquivo(&lista);

    int opcao, idBusca, humorBusca;
    
    //Menu de opções
    do {
        printf("\n----------------MENU------------------\n");
        printf("1 - Adicionar novo registro\n");
        printf("2 - Remover registro por id\n");
        printf("3 - Buscar por humor\n");
        printf("4 - Imprimir todos os registros\n");
        printf("5 - Mostrar média da notaDoDia\n");
        printf("6 - Mostrar humor mais frequente\n");
        printf("7 - Mostrar os motivos do humor\n");
        printf("8 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        printf("-------------------------------------------\n");
        getchar();

        switch(opcao) {
            case 1: //Adicionar novo registro
                RegistroDeHumor *novoRegistro = criarRegistro();
                InserirNoFim(&lista, *novoRegistro);
                printf("\nREGISTRO ADICIONADO COM SUCESSO!\n");
                break;

            case 2: //Remover por ID
                if(!EstaVazia(&lista)){
                    printf("\nDIGITE O ID DO REGISTRO QUE DESEJA REMOVER: ");
                    scanf("%d", &idBusca);
                    RemoverElemento(&lista, idBusca);
                }
                else
                    printf("\nLISTA VAZIA!\n");
                break;

            case 3: //Buscar por humor
                if(!EstaVazia(&lista)){
                    printf("\nDIGITE O HUMOR QUE DESEJA BUSCAR (0-FELIZ, 1-TRISTE, 2-ANSIOSO, 3-CANSADO, 4-MOTIVADO, 5-ESTRESSADO, 6-NEUTRO): ");
                    scanf("%d", &humorBusca);
                    BuscarHumor(&lista, humorBusca);
                }
                else
                    printf("\nLISTA VAZIA!\n");
                break;

            case 4: //Imprimir todos os registros
                if(!EstaVazia(&lista)){ 
                    printf("\n---IMPRIMINDO TODOS OS REGISTROS---\n");
                    ImprimirTudo(&lista);
                    printf("\n---FIM DOS REGISTROS---\n");
                }
                else
                    printf("\nLISTA VAZIA!\n");
                break;

            case 5: //Média de notas dos ultimos X dias
                if(!EstaVazia(&lista)){
                    int x;
                    printf("\nDIGITE A QUANTIDADE DE ULTIMOS REGISTROS QUE DESEJA CALCULAR A MEDIA: ");
                    scanf("%d", &x);
                    if(x < 1)
                        printf("\nQUANTIDADE INVALIDA, DEVE SER PELO MENOS 1!\n");
                    else{
                        float media = MediaDasNotasUltimosX(&lista, x);
                        printf("\nMEDIA DAS NOTAS DOS ULTIMOS %d REGISTROS: %.1f\n", x, media);
                    } 
                }
                else{
                    printf("\nLISTA VAZIA!\n");
                }
                    break;
            
            case 6: //Mostra o humor mais frequente dos ultimos X dias
                if(!EstaVazia(&lista)){
                    int x;
                    printf("\nDIGITE A QUANTIDADE DE ULTIMOS REGISTROS PARA BUSCAR O HUMOR MAIS FREQUENTE: ");
                    scanf("%d", &x);
                    if(x < 1)
                        printf("\nQUANTIDADE INVALIDA, DEVE SER PELO MENOS 1!\n");
                    else{
                        Humor humorMaisFreq = HumorMaisFrequenteUltimosX(&lista, x);
                        printf("\nO HUMOR MAIS FREQUENTE DOS ULTIMOS %d REGISTROS É: %s\n", x, Identificador[humorMaisFreq]);
                    }      
                }
                else
                    printf("\nLISTA VAZIA!\n");   
                break;
                
            case 7: //Mostra todos os motivos de determinado humor X
                int humorProcurado;
                if(!EstaVazia(&lista)){
                    printf("\nDIGITE O HUMOR QUE DESEJA SABER OS MOTIVOS:\n");
                    printf("0 - FELIZ\n1 - TRISTE\n2 - ANSIOSO\n3 - CANSADO\n4 - MOTIVADO\n5 - ESTRESSADO\n6 - NEUTRO\n");
                    printf("ESCOLHA UMA OPCAO: ");
                    scanf("%d", &humorProcurado);
                    if(humorProcurado < 0 || humorProcurado > 6)
                        printf("\nHUMOR INVALIDO!\n");
                    else   
                        MostrarMotivosPorHumorX(&lista, humorProcurado);
                }
                else
                    printf("\nLISTA VAZIA!\n");
                break;
                
            case 8: //Desliga o programa
                SalvarRegistrosEmArquivo(&lista, "arquivo.txt");
                printf("\nDESLIGANDO PROGRAMA!\n");
                break;
                
            default: //Caso o usuario digite uma opção invalida 
                printf("\nOPÇÂO INVALIDA, TENTE NOVAMENTE!\n");
        }
    } 
    while(opcao != 8);

    return 0;
}