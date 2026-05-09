#include <stdlib.h>
#include "pilha.h"
//inserindo na pilha com PUSH
void push(Pilha *p, Paciente paciente) {
    No *novo = malloc(sizeof(No));
    novo->p = paciente;
    novo->prox = p->topo;
    p->topo = novo;
}
//Tirando da pilha com POP
Paciente pop(Pilha *p) {
    No *temp = p->topo;
    Paciente paciente = temp->p;
    p->topo = temp->prox;
    free(temp);
    return paciente;
}
//Definindo quando a pilha vai ser vazia
int vazia(Pilha *p) {
    return p->topo == NULL;
}
//limpar a pilha quando encerrar o programa
void limparPilha(Pilha *p) {
    while (!vazia(p)) {
        pop(p); // O pop já faz o free
    }
}
