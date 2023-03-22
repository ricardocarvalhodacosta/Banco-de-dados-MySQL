#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mysql.h>
#include <locale.h>

MYSQL *__stdcall obterConexao()
{
    char *servidor = "127.0.0.1";
    char *usuario = "root";
    char *senha = "1234";
    char *nomeBanco = "bancoSQL_C";

    MYSQL *conexao = mysql_init(NULL);

    if (!mysql_real_connect(conexao, servidor, usuario, senha, nomeBanco, 0, NULL, 0))
    {
        fprintf(stderr, "\n%s\n", mysql_error(conexao));
        mysql_close(conexao);
        exit(1);
    }
    else
    {
        printf("\nConexão realizada com sucesso!\n");
        return conexao;
    }
}

int main()
{
    setlocale(LC_ALL, "portuguese-brazilian");
    MYSQL *conexao = obterConexao();
    return 0;
}
