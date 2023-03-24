#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

void erro(MYSQL *conexao);
MYSQL *__stdcall obterConexao();
void inserir(MYSQL *conexao, char *nome, char *telefone, char *email );
void ler(MYSQL *conexao);
void atualizar(MYSQL *conexao, char email);
void apagar(MYSQL *conexao, char email);

#endif // HEADER_H_INCLUDED
