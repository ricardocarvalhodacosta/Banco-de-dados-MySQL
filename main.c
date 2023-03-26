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
    setup();

    mysql_close(conexao);
    return 0;
}
