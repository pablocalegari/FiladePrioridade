#ifndef UTILS_H
#define UTILS_H

#include "fila.h"
#include "pilha.h"

//definindo a função de atender, tirar da fila e colocar pilha
void atender(FilaPrioridade *fila, Pilha *pilha, int hora);

//definindo a função de desfazer
void desfazer(Pilha *pilha, FilaPrioridade *fila);


void processarArquivo(char *nome, FilaPrioridade *fila, Pilha *pilha);

#endif
