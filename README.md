# 🏥 Sistema de Gerenciamento de Atendimento Médico (C)

> Sistema em linguagem C para gerenciamento de fluxo de pacientes em uma Unidade de Pronto Atendimento (UPA), utilizando Fila de Prioridade e Pilha.

---

## 🚀 Sobre o Projeto

Este projeto simula o funcionamento de um sistema real de triagem médica baseado no **Sistema de Manchester**.

O sistema é responsável por:
- Controlar a entrada de pacientes
- Organizar o atendimento por prioridade
- Armazenar histórico de atendimentos
- Permitir desfazer atendimentos

---

## 🧠 Conceitos Utilizados

- Estruturas de Dados:
  - Fila de Prioridade
  - Pilha (Stack)
- Controle de tempo (ordem de chegada)
- Alocação dinâmica de memória (`malloc` / `free`)
- Leitura de arquivos `.txt`
- Testes de desempenho
- Análise de memória com Valgrind

---

## ⚙️ Funcionalidades

### 🧍 Cadastro de Pacientes
Cada paciente possui:
- ID
- Nome
- Gravidade clínica
- Grau de prioridade
- Hora de chegada

---

### 🚑 Fila de Prioridade
O atendimento segue:
1. Maior prioridade
2. Maior tempo de espera

---

### 📈 Aumento de Prioridade
- A cada 5 novos pacientes inseridos:
  - A prioridade dos pacientes a partir do 6º é aumentada
  - Existe um limite máximo de prioridade

---

### 📚 Pilha de Atendidos
- Pacientes atendidos são armazenados em uma pilha
- Permite controle temporário dos atendimentos realizados

---

### ↩️ Desfazer Atendimento
- Remove o último paciente atendido
- Retorna para a fila com prioridade máxima

---

### 📄 Processamento de Arquivo
O sistema também funciona com arquivos `.txt`, simulando:
- Entrada de pacientes
- Atendimento
- Desfazer atendimento

---

### 🧪 Testes de Desempenho
Testes realizados com:
- 100 registros
- 1.000 registros
- 10.000 registros

Comparação de tempo de execução entre cenários.

---

## 🛠️ Tecnologias

- Linguagem: **C**
- Compilador: `gcc`
- Ferramenta de análise: `Valgrind`

---

## 📦 Como Executar

`bash`
# Clone o repositório
git clone https://github.com/seu-usuario/seu-repo.git

# Acesse a pasta
cd seu-repo

# Compile o código
gcc main.c -o programa

# Execute
./programa
## 👥 Integrantes
Douglas Leal
Gustavo Vaz
Luiz Guilherme Romão
Pablo Antonio Calegari
