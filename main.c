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

void menu() {
    printf("\nSISTEMA FILA DE PRIORIDADE\n");
    printf("1 - Adicionar paciente\n");
    printf("2 - Atender paciente\n");
    printf("3 - Desfazer atendimento\n");
    printf("4 - Processar arquivo\n");
    printf("5 - Mostrar fila (ordenada)\n");
    printf("6 - Mostrar pilha de atendidos\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

int lerInt(const char *msg) {
    int valor;
    while (1) {
        printf("%s", msg);
        if (scanf("%d", &valor) == 1) return valor;
        printf("Entrada invalida. Tente novamente.\n");
        while (getchar() != '\n');
    }
}

// Comparador para exibição ordenada (não altera o heap original)
int comparadorParaExibicao(const void *a, const void *b) {
    Paciente *p1 = (Paciente *)a;
    Paciente *p2 = (Paciente *)b;

    if (p1->prioridade == p2->prioridade)
        return p1->horaChegada - p2->horaChegada;

    return p2->prioridade - p1->prioridade;
}

// CORREÇÃO: usa malloc em vez de array na stack para evitar stack overflow
void mostrarFilaOrdenada(FilaPrioridade *fila) {
    if (fila->tamanho == 0) {
        printf("Fila vazia.\n");
        return;
    }

    Paciente *copia = malloc(fila->tamanho * sizeof(Paciente));
    if (!copia) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }

    for (int i = 0; i < fila->tamanho; i++)
        copia[i] = fila->dados[i];

    qsort(copia, fila->tamanho, sizeof(Paciente), comparadorParaExibicao);

    printf("\n--- FILA DE ATENDIMENTO (ORDENADA) ---\n");
    for (int i = 0; i < fila->tamanho; i++) {
        printf("ID: %d | Nome: %s | Prioridade: %d | Chegada: %d\n",
            copia[i].id, copia[i].nome, copia[i].prioridade, copia[i].horaChegada);
    }

    free(copia); // IMPORTANTE: libera a memória alocada
}

void mostrarPilha(Pilha *pilha) {
    if (vazia(pilha)) {
        printf("Nenhum paciente atendido.\n");
        return;
    }

    printf("\nPILHA DE ATENDIDOS\n");

    No *atual = pilha->topo;
    while (atual != NULL) {
        printf("ID:%d | Nome:%s | Atendido em:%d\n",
            atual->p.id,
            atual->p.nome,
            atual->p.horaAtendimento);
        atual = atual->prox;
    }
}

int main() {
    FilaPrioridade fila = {.tamanho = 0};
    Pilha pilha = {.topo = NULL};

    int opcao, contador = 0;
    int tempoGlobal = 0;

    do {
        system(CLEAR);
        menu();
        opcao = lerInt("");

        switch (opcao) {

            case 1: {
                Paciente p = {0};

                p.id = lerInt("ID: ");

                printf("Nome: ");
                // CORREÇÃO: scanf correto para ler nome com espacos
                scanf(" %99[^\n]", p.nome);

                do {
                    p.gravidade = lerInt("Gravidade (1-5): ");
                } while (p.gravidade < 1 || p.gravidade > 5);

                tempoGlobal++;
                p.horaChegada = tempoGlobal;
                p.prioridade = p.gravidade;

                inserir(&fila, p);
                contador++;

                if (contador % 5 == 0)
                    aumentarPrioridade(&fila);

                printf("Paciente adicionado!\n");
                break;
            }

            case 2:
                if (fila.tamanho == 0) {
                    printf("Fila vazia.\n");
                } else {
                    tempoGlobal++;
                    atender(&fila, &pilha, tempoGlobal);
                    printf("Paciente atendido.\n");
                }
                break;

            case 3:
                if (vazia(&pilha)) {
                    printf("Nada para desfazer.\n");
                } else {
                    desfazer(&pilha, &fila);
                    printf("Atendimento desfeito.\n");
                }
                break;

            case 4: {
                char nome[100];
                printf("Arquivo: ");
                scanf("%s", nome);

                clock_t ini = clock();
                processarArquivo(nome, &fila, &pilha);
                clock_t fim = clock();

                printf("Processado em %.4f segundos\n",
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
                printf("Opcao invalida.\n");
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            while (getchar() != '\n');
            getchar();
        }

    } while (opcao != 0);

    limparPilha(&pilha);

    return 0;
}
