#ifndef FILA_H
#define FILA_H

#include "paciente.h"

#define MAX 10000
//definindo como vai ser a fila
typedef struct {
    Paciente dados[MAX];
    int tamanho;
} FilaPrioridade;

void inserir(FilaPrioridade *f, Paciente p);
Paciente remover(FilaPrioridade *f);
void aumentarPrioridade(FilaPrioridade *f);

#endif
