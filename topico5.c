// Segue um exemplo de programa em Linguagem C que exemplifica a utilização de threads. Nele, são criados três threads dentro
// de um processo. O thread principal termina sua execução somente quando o último thread finaliza sua execução.

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/wait.h>

#define TAMANHO_PILHA 65536
#define _1SEGUNDO 1000000

int global = 0; // Variável global alterada pelos threads

static int funcaoThread(void *arg) {
int id = *((int *) arg); // Identificação de cada thread
int i;

printf("Iniciou thread [%d]\n", id);
for (i=0; i<3; i++) { // Loop no qual o thread altera a variável global
    printf("Thread [%d] incrementou \"global\" para %d.\n", id, ++global);
    usleep(_1SEGUNDO * (1+id/10.0));
  }
printf("Saindo do thread [%d]\n", id);
}

int main () {
void *pilha;
int i, pid[3];
int id[3] = {1,2,3}; // Identificação a ser passada para cada thread

for (i=0; i<3; i++) { // Alocando espaço para a pilha de cada thread
if ((pilha = malloc(TAMANHO_PILHA)) == 0) {
perror("Erro na alocação da pilha.");
exit(1);
}
pid[i] = clone(funcaoThread,
pilha + TAMANHO_PILHA,
CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | SIGCHLD,
&(id[i])); // Criação de cada thread
}
printf("Thread principal aguardando demais threads terminarem.\n");
for (i=0; i < 3; i++)
if (waitpid(pid[i], 0, 0) == -1) { // Aguarda até o término do thread
perror("waitpid")
exit(2);
}
printf("Thread principal terminando.\n\n");
}

// Quando executado, o programa fornece a seguinte saída:

Thread principal aguardando demais threads terminarem.
Iniciou thread [3]
Thread [3] incrementou "global" para 1.
Iniciou thread [2]
Thread [2] incrementou "global" para 2.
Iniciou thread [1]
Thread [1] incrementou "global" para 3.
Thread [1] incrementou "global" para 4.
Thread [2] incrementou "global" para 5.
Thread [3] incrementou "global" para 6.
Thread [1] incrementou "global" para 7.
Thread [2] incrementou "global" para 8.
Thread [3] incrementou "global" para 9.
Saindo do thread [1]
Saindo do thread [2]
Saindo do thread [3]
Thread principal terminando.

// Pela execução, você pode perceber que os valores das variáveis locais de cada thread não são influenciados pela execução dos
// demais threads. Porém, quando a variável “global” é modificada por um thread, esta alteração é vista imediatamente por todos
// os demais threads.