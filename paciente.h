#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct {
    int id;
    char nome[100];
    int gravidade;
    int prioridade;
    int horaChegada;
    int horaAtendimento;
} Paciente;

#endif
