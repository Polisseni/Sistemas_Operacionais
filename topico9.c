// A troca de mensagens pode ser implementada pelo mecanismo de pipe. O pipe ( | ) é um mecanismo especial de redirecionamento 
// utilizado para conectar a saída padrão de um processo à entrada padrão de outro processo. Por exemplo, os comandos a seguir 
// juntam todos os arquivos com extensão “.txt”, ordenando suas linhas e retirando as duplicadas.

cat *.txt | sort | uniq

// O comando “cat *.txt” joga na saída padrão (tela) o conteúdo de todos os arquivos presentes no
//  diretório e que possuem extensão “.txt”.

// O comando “sort” recebe linhas por sua entrada padrão (inicialmente, o teclado), ordena as linhas e envia as linhas 
// devidamente ordenadas para a saída padrão.

// O comando “uniq” recebe linhas por sua entrada padrão e elimina as linhas duplicadas, enviando para a saída padrão 
// somente as linhas que não estão em duplicidade.