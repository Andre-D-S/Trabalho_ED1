#ifndef LISTADUPLAMENTEENC_H
#define LISTADUPLAMENTEENC_H

typedef struct nolista{
    RegistroDeHumor info;
    struct nolista *prox;
    struct nolista *ant;
}Nolista;

void CriarLista(Nolista** l);

int EstaVazia(Nolista** l);

void InserirNoFim(Nolista** l, RegistroDeHumor registro);

void ImprimirTudo(Nolista** l);

void RemoverElemento(Nolista** l, int v);

Nolista* BuscarHumor(Nolista** l, int v);

float MediaDasNotasUltimosX(Nolista** l, int x);

Humor HumorMaisFrequenteUltimosX(Nolista** l, int x);

void MostrarMotivosPorHumorX(Nolista** l, int humorDesejado);

void SalvarRegistrosEmArquivo(Nolista** l, const char* nomeArquivo);

void CarregarRegistrosDoArquivo(Nolista** l);

#endif /* LISTADUPLAMENTEENC_H */

