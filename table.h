#ifndef TABLE_H
#define TABLE_H

#include "database.h"

void add_column(Table *table, const char *column_name);
void delete_column(Table *table, const char *column_name);

#endif