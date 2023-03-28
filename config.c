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
    int numeroclientes;
    char email[320];
    char nome[50];
    char telefone[20];
    char menu;

    printf("Banco de Dados MySQL, digite a função desejada: \n");
    printf("1. Adicionar novo usuário, 2. Ler os dados, 3. Alterar os dados, 4. Apagar dados, 5. Encerrar;\n");
    scanf(" %c", &menu);

    switch(menu)
    {
    case '1':
        printf("\n*** CADASTRO DE CLIENTES ***\n");
        printf("Quantos clientes gostaria de adicionar?\n");
        scanf("%d", &numeroclientes);
        while (getchar() != '\n');
        printf("\n");

        for (i = 0; i < numeroclientes; i++)
        {
            printf("%d - Email: ", i);
            fgets (email, 320, stdin);
            email[strcspn(email, "\n")] = '\0';
            printf("%d - Nome: ", i);
            fgets(nome, 50, stdin);
            nome[strcspn(nome, "\n")] = '\0';
            printf("%d - Telefone: ", i);
            fgets(telefone, 20, stdin);
            telefone[strcspn(telefone, "\n")] = '\0';
            ;
            inserir(conexao, email, nome, telefone);
        }
        break;

    case '2':
        ler(conexao);
        break;

    case '3':
        atualizar(conexao);
        ler(conexao);
        break;

    case '4':
        apagar(conexao);
        ler(conexao);
        break;

    default:
        printf("\nObrigado e volte logo!\n");
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
    char email[320];
    char nome[50];
    char novonome[50];
    char telefone[20];
    int op;

    printf("Quais dados gostaria de alterar?\n");
    printf("1. E-mail, 2. Nome, 3 Telefone;\n");
    printf("Digite aqui: ");
    scanf("%d", &op);
    getchar();

    switch(op)
    {
    case 1:
        printf("Qual o NOME do Cliente que gostaria de alterar dados?\n");
        getchar();
        fgets(nome, 50, stdin);
        printf("Qual o novo E-MAIL?\n");
        getchar();
        fgets(email, 320, stdin);
        email[strcspn(email, "\n")] = '\0';
        sprintf(query, "UPDATE clientes SET email = '%s' WHERE nome = '%s'", email, nome);
        break;
    case 2:
        printf("Qual o NOME atual do Cliente que gostaria de alterar dados?\n");
        fgets(nome, 50, stdin);
        getchar();
        printf("Qual o novo NOME?\n");
        fgets(novonome, 50, stdin);
        novonome[strcspn(novonome, "\n")] = '\0';
        sprintf(query, "UPDATE clientes SET nome = '%s' WHERE nome = '%s'", novonome, nome);
        break;
    case 3:
        printf("Qual o NOME do Cliente que gostaria de alterar dados?\n");
        fgets(nome, 50, stdin);
        printf("Qual o novo TELEFONE?\n");
        getchar();
        fgets(telefone, 20, stdin);
        telefone[strcspn(telefone, "\n")] = '\0';
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
    char email[320];
    printf("Qual o E-MAIL do cliente a ser apagado?\n");
    getchar();
    scanf("%s", email);

    char *token = strtok(email, "@");
    char nome[100];
    char dominio[100];
    strcpy(nome, token);

    token = strtok(NULL, "@");
    strcpy(dominio, token);

    sprintf(query, "DELETE FROM clientes WHERE email = '%s' AND nome = '%s' AND dominio = '%s'", email, nome, dominio);

    if (mysql_query(conexao, query))
    {
        erro(conexao);
    }
    else
    {
        printf("\nDados apagados com sucesso!\n");
    }
}
