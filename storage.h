#ifndef STORAGE_H
#define STORAGE_H

#include "database.h"

void savee_db(Database *db, const char *filename);
void load_db(Database *db, const char *filename);

#endif