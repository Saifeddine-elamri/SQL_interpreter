#include <stdio.h>
#include <string.h>
#include "database.h"

void print_help() {
    printf("Commandes disponibles:\n");
    printf("  CREATE TABLE <nom_table> <colonnes>\n");
    printf("  INSERT INTO <nom_table> VALUES <valeurs>\n");
    printf("  SELECT * FROM <nom_table>\n");
    printf("  SAVE <nom_fichier>\n");  // Ajout de cette ligne
    printf("  EXIT\n");
}

int main() {
    Database db;
    init_db(&db);
    
    char command[100];
    printf("Bienvenue dans la base de données simple. Tapez 'HELP' pour voir les commandes.\n");
    
    while (1) {
        printf("> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;  // Supprimer le saut de ligne
        
        if (strcmp(command, "EXIT") == 0) {
            break;
        } else if (strcmp(command, "HELP") == 0) {
            print_help();
        } else if (strncmp(command, "CREATE TABLE", 12) == 0) {
            char table_name[50], columns[100];
            sscanf(command, "CREATE TABLE %s %[^\n]", table_name, columns);
            create_table(&db, table_name, columns);
        } else if (strncmp(command, "INSERT INTO", 11) == 0) {
            char table_name[50], values[100];
            sscanf(command, "INSERT INTO %s VALUES %[^\n]", table_name, values);
            insert_row(&db, table_name, values);
        } else if (strncmp(command, "SELECT * FROM", 13) == 0) {
            char table_name[50];
            sscanf(command, "SELECT * FROM %s", table_name);
            print_table(&db, table_name);
        } else if (strncmp(command, "SAVE", 4) == 0) {
            char filename[100];
            sscanf(command, "SAVE %s", filename);
            save_db(&db, filename);
        } else {
            printf("Commande non reconnue. Tapez 'HELP' pour voir les commandes disponibles.\n");
        }
    }
    
    close_db(&db);
    return 0;
}