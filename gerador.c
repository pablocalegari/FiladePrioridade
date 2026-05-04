#include <stdio.h>
#include <stdlib.h>

void gerarArquivo(char *nome, int quantidade) {
    FILE *f = fopen(nome, "w");

    for (int i = 1; i <= quantidade; i++) {
        fprintf(f, "ADD %d P%d %d %d\n",
            i,
            i,
            rand() % 5 + 1,   // gravidade 1-5
            i                 // hora crescente
        );

        if (i % 7 == 0)
            fprintf(f, "ATENDER\n");

        if (i % 13 == 0)
            fprintf(f, "DESFAZER\n");
    }

    fclose(f);
}

int main() {
    gerarArquivo("entrada_100.txt", 100);
    gerarArquivo("entrada_1000.txt", 1000);
    gerarArquivo("entrada_10000.txt", 10000);

    printf("Arquivos gerados com sucesso!\n");
    return 0;
}
