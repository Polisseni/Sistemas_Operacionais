// Programa com semáforo, solucionando a condição de corrida:

 /*********************************\
 2 * *
 3 * COMPILAR COM PARÂMETRO -pthread *
 4 * *
 5 \*********************************/
 6
 7 #define _GNU_SOURCE
 8 #include <stdio.h>
 9 #include <stdlib.h>
10 #include <unistd.h>
11 #include <sched.h>
12 #include <sys/wait.h>
13 #include <semaphore.h>
14
15 #define TAMANHO_PILHA 65536
16
17 sem_t mutex; // Cria semáforo mutex
18
19 void up(sem_t *sem) {
20 sem_wait(sem);
21 }
22
23 void down(sem_t *sem) {
24 sem_post(sem);
25 }
26
27 typedef struct {
28 double saldo;
29 } Registro;
30
31 Registro registro;
32
33 Registro le_registro(int conta){
34 return registro;
35 }
36
37 void grava_registro(Registro reg, int conta){
38 registro = reg;
39 }
40
41 void atualiza_saldo(double valor, int conta) {
42 Registro registro;
43 up(&mutex);
44 printf("Iniciando operação [%.2f]\n", valor);
45 registro = le_registro(conta);
46 usleep(1000);
47 registro.saldo = registro.saldo + valor;
48 grava_registro(registro, conta);
49 printf("Terminada operação [%.2f]\n", valor);
50 down(&mutex);
51 }
52
53 int funcaoDeposito(void *arg) {
54 // Faz deposito de 100,00
55 atualiza_saldo(100, 0);
56 }
57
58 int funcaoSaque(void *arg) {
59 // Faz saque de 200,00
60 atualiza_saldo(-200, 0);
61 }
62
63 int main() {
64 void *pilha1, *pilha2;
65 int pid1, pid2;
66
67 // Inicializa mutex om valor 1 (somente um thread na região crítica)
68 sem_init(&mutex, 1, 1);
69
70 registro.saldo = 500; // Inicializa saldo
71 printf("Saldo antes das operações = %.2f\n", registro.saldo);
72
73 // Aloca pilha para thread de depósito
74 if ((pilha1 = malloc(TAMANHO_PILHA)) == 0) {
75 perror("Erro na alocação da pilha.");
76 exit(1);
77 }
78 // Inicia thread de depósito
79 pid1 = clone(funcaoDeposito,
80 pilha1 + TAMANHO_PILHA,
81 CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | SIGCHLD,
82 NULL);
83
84 // Aloca pilha para thread de saque
85 if ((pilha2 = malloc(TAMANHO_PILHA)) == 0) {
86 perror("Erro na alocação da pilha.");
87 exit(1);
88 }
89 // Inicia thread de saque
90 pid2 = clone(funcaoSaque,
91 pilha2 + TAMANHO_PILHA,
92 CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | SIGCHLD,
93 NULL);
94
95 //Aguarda final da operações
96 waitpid(pid1, 0, 0);
97 waitpid(pid2, 0, 0);
98
99 printf("Saldo depois das operações = %.2f\n", registro.saldo);
100 }