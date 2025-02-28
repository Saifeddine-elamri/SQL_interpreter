#include "query.h"
#include <string.h>
#include <stdio.h>

void execute_query(Database *db, const char *query) {
    // Exemple simple de traitement de requête
    if (strncmp(query, "SELECT", 6) == 0) {
        char table_name[50];
        sscanf(query, "SELECT * FROM %s", table_name);
        print_table(db, table_name);
    } else if (strncmp(query, "INSERT", 6) == 0) {
        char table_name[50], row_data[100];
        sscanf(query, "INSERT INTO %s VALUES %s", table_name, row_data);
        insert_row(db, table_name, row_data);
    } else {
        printf("Requête non reconnue.\n");
    }
}