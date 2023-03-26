#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED


void erro(MYSQL *conexao);
MYSQL *__stdcall obterConexao();
void setup();
void inserir(MYSQL *conexao, char *nome, char *telefone, char *email );
void ler(MYSQL *conexao);
void atualizar(MYSQL *conexao);
void apagar(MYSQL *conexao);

#endif // HEADER_H_INCLUDED
