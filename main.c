#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mysql.h>
#include <locale.h>
#include "header.h"

int main()
{
    setlocale(LC_ALL, "portuguese-brazilian");
    MYSQL *conexao = obterConexao();
    char *email[100];
    char nome[100];
    char telefone[100];
    int i;
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
            inserir(conexao, nome, telefone, email);
        }
        break;

    case '2':
        printf("\n*** CLIENTES CADASTRADOS ***\n");
        ler(conexao);
        break;

    case '3':
        atualizar(conexao, email);
        printf("\n*** CLIENTES CADASTRADOS ***\n");
        ler(conexao);
        break;

    case '4':
        apagar(conexao, 11);

        printf("\n*** CLIENTES CADASTRADOS ***\n");
        ler(conexao);
        break;

    default:
        break;
    }

    mysql_close(conexao);
    return 0;
}
