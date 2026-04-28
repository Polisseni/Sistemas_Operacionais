// Quando o fork() é utilizado para a criação de um processo que executará o código de outro programa, a chamada de sistema
// execve() deve ser utilizada para que o processo filho mude sua imagem de memória e execute o novo programa.
// O código a seguir ilustra a utilização de execve(). Nele, o processo pai cria três processos filhos em sequência.
// O primeiro coloca em execução uma calculadora, o segundo, o editor de textos gedit, e o terceiro, o utilitário xeyes.

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv, char* envp[]) {
int pid, i;

for (i=1; i<=3; i++) {
pid = fork();
if (pid < 0) {
printf("Algo deu errado!!!\n");
return 0;
}
if (pid == 0) { // Processo filho
if (i == 1)
execve("/usr/bin/xcalc", argv, envp);
if (i == 2)
execve("/usr/bin/gedit", argv, envp);
if (i == 3)
execve("/usr/bin/xeyes", argv, envp);
}
else // Processo pai
waitpid(pid, NULL, 0)
}
}

// Após ter executado sua tarefa, o novo processo terminará devido a uma das seguintes condições:

// Saída normal (voluntária)
// A maioria dos processos termina por terem realizado o seu trabalho. Quando isto ocorre, o processo executa uma chamada 
// para dizer ao sistema operacional que ele terminou e para que o sistema possa tomar as providências necessárias ao 
// seu encerramento.

// Erro fatal (involuntário)
// O processo também pode terminar quando descobre um erro fatal. Ele pode solicitar ao usuário uma nova entrada de dados ou 
// simplesmente encerrar sua execução de maneira similar à saída normal.

// Saída por erro (voluntária)
// Outra razão para o término é um erro causado pelo processo, muitas vezes decorrente de um erro de programa. Exemplos incluem 
// executar uma instrução ilegal, referenciar uma memória não existente ou dividir por zero.

// Morto por outro processo (involuntário)
// A quarta razão pela qual um processo pode ser finalizado é a execução de uma chamada de sistema dizendo ao sistema operacional
// para matar outro processo. Para um processo matar outro, é necessário autorização.