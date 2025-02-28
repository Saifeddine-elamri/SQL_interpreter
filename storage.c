#include "storage.h"
#include <stdio.h>
#include <stdlib.h>

void savee_db(Database *db, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    
    fwrite(db, sizeof(Database), 1, file);
    fclose(file);
}

void load_db(Database *db, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    
    fread(db, sizeof(Database), 1, file);
    fclose(file);
}