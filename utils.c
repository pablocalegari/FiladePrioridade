#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

void atender(FilaPrioridade *fila, Pilha *pilha, int hora) {
    if (fila->tamanho == 0) return;

    Paciente p = remover(fila);
    p.horaAtendimento = hora;
    push(pilha, p);
}

void desfazer(Pilha *pilha, FilaPrioridade *fila) {
    if (vazia(pilha)) return;

    Paciente p = pop(pilha);
    p.prioridade = 6; // prioridade máxima ao desfazer
    inserir(fila, p);
}

void processarArquivo(char *nome, FilaPrioridade *fila, Pilha *pilha) {
    FILE *arq = fopen(nome, "r");

   
    if (!arq) {
        printf("Erro: arquivo '%s' nao encontrado ou sem permissao de leitura.\n", nome);
        return;
    }

    char cmd[20];
    int contador = 0;

    while (fscanf(arq, "%s", cmd) != EOF) {

        if (strcmp(cmd, "ADD") == 0) {
            Paciente p;
            fscanf(arq, "%d %s %d %d", &p.id, p.nome, &p.gravidade, &p.horaChegada);
            p.prioridade = p.gravidade;

            inserir(fila, p);
            contador++;

            if (contador % 5 == 0)
                aumentarPrioridade(fila);
        }

        else if (strcmp(cmd, "ATENDER") == 0) {
            contador++;
            atender(fila, pilha, contador);
        }

        else if (strcmp(cmd, "DESFAZER") == 0) {
            desfazer(pilha, fila);
        }
    }

    fclose(arq);
}
