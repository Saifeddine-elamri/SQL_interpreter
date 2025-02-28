#include "table.h"
#include <string.h>
#include <stdio.h>
void add_column(Table *table, const char *column_name) {
    if (table->column_count >= 10) {
        printf("Nombre maximum de colonnes atteint.\n");
        return;
    }
    
    strcpy(table->columns[table->column_count++], column_name);
}

void delete_column(Table *table, const char *column_name) {
    for (int i = 0; i < table->column_count; i++) {
        if (strcmp(table->columns[i], column_name) == 0) {
            for (int j = i; j < table->column_count - 1; j++) {
                strcpy(table->columns[j], table->columns[j + 1]);
            }
            table->column_count--;
            return;
        }
    }
    
    printf("Colonne non trouvée.\n");
}