all:
	gcc main.c fila.c pilha.c utils.c -o FiladePrioridade -Wall -Wextra

run:
	./FiladePrioridade

# Alvo para teste de memória com AddressSanitizer (Windows/Linux)
sanitize:
	gcc main.c fila.c pilha.c utils.c -o FiladePrioridade_test -fsanitize=address -g -Wall
