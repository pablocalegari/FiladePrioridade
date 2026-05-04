#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utils.h"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

// ===== CORES =====
#define RESET "\033[0m"
#define VERDE "\033[32m"
#define VERMELHO "\033[31m"
#define AMARELO "\033[33m"
#define AZUL "\033[34m"

// ===== MENU =====
void menu() {
    printf(AZUL "\n===== SISTEMA UPA =====\n" RESET);
    printf("1 - Adicionar paciente\n");
    printf("2 - Atender paciente\n");
    printf("3 - Desfazer atendimento\n");
    printf("4 - Processar arquivo\n");
    printf("5 - Mostrar fila (ordenada)\n");
    printf("6 - Mostrar pilha de atendidos\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
}

// ===== VALIDAÇÕES =====
int lerInt(const char *msg) {
    int valor;
    while (1) {
        printf("%s", msg);
        if (scanf("%d", &valor) == 1) return valor;

        printf(VERMELHO "Entrada invalida. Tente novamente.\n" RESET);
        while (getchar() != '\n'); // limpa buffer
    }
}

// ===== COMPARADOR PARA ORDENAÇÃO =====
int cmp(const void *a, const void *b) {
    Paciente *p1 = (Paciente*)a;
    Paciente *p2 = (Paciente*)b;

    if (p1->prioridade == p2->prioridade)
        return p1->horaChegada - p2->horaChegada;

    return p2->prioridade - p1->prioridade;
}

// ===== MOSTRAR FILA ORDENADA =====
void mostrarFilaOrdenada(FilaPrioridade *fila) {
    if (fila->tamanho == 0) {
        printf(AMARELO "Fila vazia.\n" RESET);
        return;
    }

    Paciente copia[MAX];
    for (int i = 0; i < fila->tamanho; i++)
        copia[i] = fila->dados[i];

    qsort(copia, fila->tamanho, sizeof(Paciente), cmp);

    printf(VERDE "\n--- FILA ORDENADA ---\n" RESET);
    for (int i = 0; i < fila->tamanho; i++) {
        printf("ID:%d | Nome:%s | Prio:%d | Chegada:%d\n",
            copia[i].id,
            copia[i].nome,
            copia[i].prioridade,
            copia[i].horaChegada);
    }
}

// ===== MOSTRAR PILHA =====
void mostrarPilha(Pilha *pilha) {
    if (vazia(pilha)) {
        printf(AMARELO "Nenhum paciente atendido.\n" RESET);
        return;
    }

    printf(VERDE "\n--- PILHA DE ATENDIDOS ---\n" RESET);

    No *atual = pilha->topo;
    while (atual != NULL) {
        printf("ID:%d | Nome:%s | Atendido em:%d\n",
            atual->p.id,
            atual->p.nome,
            atual->p.horaAtendimento);
        atual = atual->prox;
    }
}

// ===== MAIN =====
int main() {
    FilaPrioridade fila = {.tamanho = 0};
    Pilha pilha = {.topo = NULL};

    int opcao, contador = 0;

    do {
        system(CLEAR);
        menu();
        opcao = lerInt("");

        switch (opcao) {

            case 1: {
                Paciente p;

                p.id = lerInt("ID: ");

                printf("Nome: ");
                scanf("%s", p.nome);

                do {
                    p.gravidade = lerInt("Gravidade (1-5): ");
                } while (p.gravidade < 1 || p.gravidade > 5);

                p.horaChegada = lerInt("Hora chegada: ");
                p.prioridade = p.gravidade;

                inserir(&fila, p);
                contador++;

                if (contador % 5 == 0)
                    aumentarPrioridade(&fila);

                printf(VERDE "Paciente adicionado!\n" RESET);
                break;
            }

            case 2:
                if (fila.tamanho == 0) {
                    printf(AMARELO "Fila vazia.\n" RESET);
                } else {
                    atender(&fila, &pilha, rand() % 100);
                    printf(VERDE "Paciente atendido.\n" RESET);
                }
                break;

            case 3:
                if (vazia(&pilha)) {
                    printf(AMARELO "Nada para desfazer.\n" RESET);
                } else {
                    desfazer(&pilha, &fila);
                    printf(VERDE "Atendimento desfeito.\n" RESET);
                }
                break;

            case 4: {
                char nome[100];
                printf("Arquivo: ");
                scanf("%s", nome);

                clock_t ini = clock();
                processarArquivo(nome, &fila, &pilha);
                clock_t fim = clock();

                printf(VERDE "Processado em %.4f segundos\n" RESET,
                    (double)(fim - ini) / CLOCKS_PER_SEC);
                break;
            }

            case 5:
                mostrarFilaOrdenada(&fila);
                break;

            case 6:
                mostrarPilha(&pilha);
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf(VERMELHO "Opcao invalida.\n" RESET);
        }

        printf("\nPressione ENTER para continuar...");
        getchar(); getchar();

    } while (opcao != 0);

    return 0;
}
