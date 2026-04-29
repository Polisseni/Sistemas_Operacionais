// Imagine um programa que atualize o saldo de um cliente após o lançamento de um débito ou um crédito em um registro.

void atualiza_saldo(double valor, int conta) {
Registro registro;
registro = le_registro(conta);
registro.saldo = registro.saldo + valor;
grava_registro(registro, conta);
}

// A correção para o caso anterior de atualização do saldo de uma conta, com a utilização de semáforos, ficaria:

void atualiza_saldo(double valor, int conta) {
Registro registro;
down(mutex);
registro = le_registro(conta);
registro.saldo = registro.saldo + valor;
grava_registro(registro, conta);
up(mutex);
}

// As operações up e down são realizadas pelo sistema operacional, que deve garantir que elas sejam executadas atomicamente.