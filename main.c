#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mysql.h>
#include <locale.h>

void erro(MYSQL *conexao)
{
    fprintf(stderr, "\n%s\n", mysql_error(conexao));
    mysql_close(conexao);
    exit(1);
}

MYSQL *__stdcall obterConexao()
{
    char *servidor = "127.0.0.1";
    char *usuario = "root";
    char *senha = "";
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

void inserir(MYSQL *conexao, char *nome, char *telefone, char *email )
{
    char query[100];
    sprintf(query, "INSERT INTO clientes(nome, telefone, email) VALUES('%s', '%s', '%s');", nome, telefone, email);

    if (mysql_query(conexao, query))
    {
        erro(conexao);
    }
    else
    {
        printf("\nDados inseridos com sucesso!\n");
    }
}

void ler(MYSQL *conexao)
{
    MYSQL_RES *resultado;
    MYSQL_ROW row;

    if (mysql_query(conexao, "SELECT * FROM clientes"))
    {
        erro(conexao);
    }

    resultado = mysql_store_result(conexao);
    if (resultado == NULL)
    {
        erro(conexao);
    }

    while ((row = mysql_fetch_row(resultado)) != NULL)
    {
        printf("\nNome: %s\n", row[0]);
        printf("Telefone: %s\n", row[1]);
        printf("Email: %s\n", row[2]);
    }

    mysql_free_result(resultado);
}

void atualizar(MYSQL *conexao, char email)
{
    char query[100];
    sprintf(query, "UPDATE clientes SET email = %s WHERE email = %s;", email, email);

    if (mysql_query(conexao, query))
    {
        erro(conexao);
    }
    else
    {
        printf("\nDados atualizados com sucesso!\n");
    }
}

void apagar(MYSQL *conexao, char email)
{
    char query[100];
    sprintf(query, "DELETE FROM clientes WHERE email = %s;", email);

    if (mysql_query(conexao, query))
    {
        erro(conexao);
    }
    else
    {
        printf("\nDados apagados com sucesso!\n");
    }
}

int main()
{
    setlocale(LC_ALL, "portuguese-brazilian");
    MYSQL *conexao = obterConexao();
    char email[100];
    char nome[100];
    char telefone[100];
    int i;

    /*printf("\n*** CADASTRO DE CLIENTES ***\n");
    for (i = 0; i < 3; i++)
    {
        printf("%d - Email: ", i);
        fflush(stdin);
        gets (email);
        printf("%d - Nome: ", i);
        fflush(stdin);
        gets(nome);
        printf("%d - Telefone: ", i);
        fflush(stdin);
        gets(telefone);
        inserir(conexao, nome, telefone, email);
    }*/

    printf("\n*** CLIENTES CADASTRADOS ***\n");
    ler(conexao);

    atualizar(conexao, email);

    printf("\n*** CLIENTES CADASTRADOS ***\n");
    ler(conexao);

    // apagar(conexao, 11);

    // printf("\n*** CLIENTES CADASTRADOS ***\n");
    // ler(conexao);

    mysql_close(conexao);
    return 0;
}
