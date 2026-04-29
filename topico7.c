// Programa sem semáforo sujeito a condição de corrida:

1 #define _GNU_SOURCE
2 #include <stdio.h>
3 #include <stdlib.h>
4 #include <unistd.h>
5 #include <sched.h>
6 #include <sys/wait.h>
7
8 #define TAMANHO_PILHA 65536
9
10 typedef struct {
11 double saldo;
12 } Registro;
13
14 Registro registro;
15
16 Registro le_registro(int conta){
17 return registro;
18 }
19
20 void grava_registro(Registro reg, int conta){
21 registro = reg;
22 }
23
24 void atualiza_saldo(double valor, int conta) {
25 Registro registro;
26 printf("Iniciando operação [%.2f]\n", valor);
27 registro = le_registro(conta);
28 usleep(1000);
29 registro.saldo = registro.saldo + valor;
30 grava_registro(registro, conta);
31 printf("Terminada operação [%.2f]\n", valor);
32 }
33
34 int funcaoDeposito(void *arg) {
35 // Faz deposito de 100,00
36 atualiza_saldo(100, 0);
37 }
38
39 int funcaoSaque(void *arg) {
40 // Faz saque de 200,00
41 atualiza_saldo(-200, 0);
42 }
43
44 int main() {
45 void *pilha1, *pilha2;
46 int pid1, pid2;
47
48 registro.saldo = 500; // Inicializa saldo
49 printf("Saldo antes das operações = %.2f\n", registro.saldo);
50
51 // Aloca pilha para thread de depósito
52 if ((pilha1 = malloc(TAMANHO_PILHA)) == 0) {
53 perror("Erro na alocação da pilha.");
54 exit(1);
55 }
56 // Inicia thread de depósito
57 pid1 = clone(funcaoDeposito,
58 pilha1 + TAMANHO_PILHA,
59 CLONE_VM | SIGCHLD,
60 NULL);
61
62 // Aloca pilha para thread de saque
63 if ((pilha2 = malloc(TAMANHO_PILHA)) == 0) {
64 perror("Erro na alocação da pilha.");
65 exit(1);
66 }
67 // Inicia thread de saque
68 pid2 = clone(funcaoSaque,
69 pilha2 + TAMANHO_PILHA,
70 CLONE_VM | SIGCHLD,
71 NULL);
72
73 //Aguarda final da operações
74 waitpid(pid1, 0, 0);
75 waitpid(pid2, 0, 0);
76
77 printf("Saldo depois das operações = %.2f\n", registro.saldo); }