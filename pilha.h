#ifndef PILHA_H
#define PILHA_H

#include "paciente.h"

typedef struct No {
    Paciente p;
    struct No *prox;
} No;

typedef struct {
    No *topo;
} Pilha;

void push(Pilha *p, Paciente paciente);
Paciente pop(Pilha *p);
int vazia(Pilha *p);

#endif
