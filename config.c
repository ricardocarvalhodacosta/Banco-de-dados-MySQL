#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mysql.h>
#include <locale.h>
#include "header.h"

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

void setup()
{
    MYSQL *conexao = obterConexao();
    int i;
    char *email[100];
    char *nome[100];
    char *telefone[100];
    char menu;

    printf("Olá, o que você gostaria de fazer?\n");
    printf("1. Adicionar novo usuário, 2. Ler os dados, 3. Alterar os dados, 4. Apagar dados;\n");
    scanf("%c", &menu);

    switch(menu)
    {
    case '1':
        printf("\n*** CADASTRO DE CLIENTES ***\n");
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
            inserir(conexao, email, nome, telefone);
        }
        break;

    case '2':
        printf("\n*** CLIENTES CADASTRADOS ***\n");
        ler(conexao);
        break;

    case '3':
        atualizar(conexao);
        printf("\n*** CLIENTES CADASTRADOS ***\n");
        ler(conexao);
        break;

    case '4':
        apagar(conexao);

        printf("\n*** CLIENTES CADASTRADOS ***\n");
        ler(conexao);
        break;

    default:
        break;
    }
}

void inserir(MYSQL *conexao, char *email, char *nome, char *telefone)
{
    char query[100];
    sprintf(query, "INSERT INTO clientes(email, nome, telefone) VALUES('%s', '%s', '%s');", email, nome, telefone);

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
        printf("\nEmail: %s\n", row[0]);
        printf("Nome: %s\n", row[1]);
        printf("Telefone: %s\n", row[2]);
    }

    mysql_free_result(resultado);
}

void atualizar(MYSQL *conexao)
{
    char query[100];
    char *email[100];
    char *nome[100];
    char *novonome[100];
    char *telefone[100];
    int op;

    printf("Quais dados gostaria de alterar?\n");
    printf("1. E-mail, 2. Nome, 3 Telefone;\n");
    printf("Digite aqui: ");
    scanf("%d", &op);

    switch(op)
    {
    case 1:
        printf("Qual o nome do Cliente que gostaria de alterar dados?\n");
        fflush(stdin);
        gets(nome);
        printf("Qual o novo E-MAIL?\n");
        fflush(stdin);
        gets(email);
        sprintf(query, "UPDATE clientes SET email = '%s' WHERE nome = '%s'", email, nome);
        break;
    case 2:
        printf("Qual o nome atual do Cliente que gostaria de alterar dados?\n");
        fflush(stdin);
        gets(nome);
        printf("Qual o novo NOME?\n");
        fflush(stdin);
        gets(novonome);
        sprintf(query, "UPDATE clientes SET nome = '%s' WHERE nome = '%s'", novonome, nome);
        break;
    case 3:
        printf("Qual o nome do Cliente que gostaria de alterar dados?\n");
        fflush(stdin);
        gets(nome);
        printf("Qual o novo TELEFONE?\n");
        fflush(stdin);
        gets(telefone);
        sprintf(query, "UPDATE clientes SET telefone = '%s' WHERE nome = '%s'", telefone, nome);
        break;
    default:
        break;
    }

    if (mysql_query(conexao, query))
    {
        erro(conexao);
    }
    else
    {
        printf("\nDados atualizados com sucesso!\n");
    }
}

void apagar(MYSQL *conexao)
{
    char query[100];
    char email[100];
    printf("Qual o E-mail do cliente a ser apagado?\n");
    fflush(stdin);
    gets(email);
    sprintf(query, "DELETE FROM clientes WHERE email = '%s'", email);

    if (mysql_query(conexao, query))
    {
        erro(conexao);
    }
    else
    {
        printf("\nDados apagados com sucesso!\n");
    }
}
