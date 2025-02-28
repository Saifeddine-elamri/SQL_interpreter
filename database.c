#include "database.h"
#include <string.h>
#include <stdio.h>

void init_db(Database *db) {
    db->table_count = 0;
}

void close_db(Database *db) {
    // Libérer les ressources si nécessaire
}

void create_table(Database *db, const char *table_name, const char *columns) {
    if (db->table_count >= 10) {
        printf("Nombre maximum de tables atteint.\n");
        return;
    }
    
    Table *table = &db->tables[db->table_count++];
    strcpy(table->name, table_name);
    
    char cols[100];
    strcpy(cols, columns);
    char *token = strtok(cols, ",");
    table->column_count = 0;
    
    while (token != NULL) {
        strcpy(table->columns[table->column_count++], token);
        token = strtok(NULL, ",");
    }
    
    table->row_count = 0;
}

void insert_row(Database *db, const char *table_name, const char *row_data) {
    Table *table = NULL;
    for (int i = 0; i < db->table_count; i++) {
        if (strcmp(db->tables[i].name, table_name) == 0) {
            table = &db->tables[i];
            break;
        }
    }
    
    if (table == NULL) {
        printf("Table non trouvée.\n");
        return;
    }
    
    if (table->row_count >= 100) {
        printf("Nombre maximum de lignes atteint.\n");
        return;
    }
    
    char row[100];
    strcpy(row, row_data);
    char *token = strtok(row, ",");
    int col = 0;
    
    while (token != NULL && col < table->column_count) {
        strcpy(table->data[table->row_count][col++], token);
        token = strtok(NULL, ",");
    }
    
    table->row_count++;
}

void print_table(Database *db, const char *table_name) {
    Table *table = NULL;
    for (int i = 0; i < db->table_count; i++) {
        if (strcmp(db->tables[i].name, table_name) == 0) {
            table = &db->tables[i];
            break;
        }
    }
    
    if (table == NULL) {
        printf("Table non trouvée.\n");
        return;
    }
    
    for (int i = 0; i < table->column_count; i++) {
        printf("%s\t", table->columns[i]);
    }
    printf("\n");
    
    for (int i = 0; i < table->row_count; i++) {
        for (int j = 0; j < table->column_count; j++) {
            printf("%s\t", table->data[i][j]);
        }
        printf("\n");
    }
}

void save_db(Database *db, const char *filename) {
    FILE *file = fopen(filename, "wb");  // Ouvrir le fichier en mode écriture binaire
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s pour la sauvegarde.\n", filename);
        return;
    }

    // Écrire le nombre de tables dans le fichier
    fwrite(&db->table_count, sizeof(int), 1, file);

    // Écrire chaque table dans le fichier
    for (int i = 0; i < db->table_count; i++) {
        Table *table = &db->tables[i];

        // Écrire le nom de la table
        fwrite(table->name, sizeof(char), 50, file);

        // Écrire le nombre de colonnes
        fwrite(&table->column_count, sizeof(int), 1, file);

        // Écrire les noms des colonnes
        for (int j = 0; j < table->column_count; j++) {
            fwrite(table->columns[j], sizeof(char), 50, file);
        }

        // Écrire le nombre de lignes
        fwrite(&table->row_count, sizeof(int), 1, file);

        // Écrire les données de chaque ligne
        for (int j = 0; j < table->row_count; j++) {
            for (int k = 0; k < table->column_count; k++) {
                fwrite(table->data[j][k], sizeof(char), 50, file);
            }
        }
    }

    fclose(file);
    printf("Base de données sauvegardée dans %s.\n", filename);
}