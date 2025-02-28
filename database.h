#ifndef DATABASE_H
#define DATABASE_H

typedef struct {
    char name[50];
    char columns[10][50];
    int column_count;
    char data[100][10][50];
    int row_count;
} Table;

typedef struct {
    Table tables[10];
    int table_count;
} Database;

void init_db(Database *db);
void close_db(Database *db);
void create_table(Database *db, const char *table_name, const char *columns);
void insert_row(Database *db, const char *table_name, const char *row_data);
void print_table(Database *db, const char *table_name);
void save_db(Database *db, const char *filename);  // Ajout de cette ligne


#endif