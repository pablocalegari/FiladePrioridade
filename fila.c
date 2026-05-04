#include <stdio.h>
#include "fila.h"

void trocar(Paciente *a, Paciente *b) {
    Paciente temp = *a;
    *a = *b;
    *b = temp;
}
//comparando as prioridades por ordem de chegada
int comparar(Paciente a, Paciente b) {
    if (a.prioridade == b.prioridade)
        return a.horaChegada < b.horaChegada;
    return a.prioridade > b.prioridade;
}

void inserir(FilaPrioridade *f, Paciente p) {
    int i = f->tamanho++;
    f->dados[i] = p;

    while (i > 0) {
        int pai = (i - 1) / 2;
        if (comparar(f->dados[pai], f->dados[i])) break;
        trocar(&f->dados[pai], &f->dados[i]);
        i = pai;
    }
}

Paciente remover(FilaPrioridade *f) {
    Paciente raiz = f->dados[0];
    f->dados[0] = f->dados[--f->tamanho];

    int i = 0;
    while (1) {
        int esq = 2*i + 1;
        int dir = 2*i + 2;
        int maior = i;

        if (esq < f->tamanho && comparar(f->dados[esq], f->dados[maior]))
            maior = esq;

        if (dir < f->tamanho && comparar(f->dados[dir], f->dados[maior]))
            maior = dir;

        if (maior == i) break;

        trocar(&f->dados[i], &f->dados[maior]);
        i = maior;
    }

    return raiz;
}
//aumenta a prioridade do paciente
void aumentarPrioridade(FilaPrioridade *f) {
    for (int i = 5; i < f->tamanho; i++) {
        if (f->dados[i].prioridade < 10)
            f->dados[i].prioridade++;
    }
}
