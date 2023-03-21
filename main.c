#include <stdio.h>
#include <mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "root";
    char *password = "1234";
    char *database = "BancoTest";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, NULL, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    char query[100];
    sprintf(query, "CREATE DATABASE %s", database);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    mysql_close(conn);

    return 0;
}
