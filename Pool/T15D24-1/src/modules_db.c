#include <stdio.h>

#include "shared.h"
#define EXIT 0

void greetings(int *mode);
void db_choice(int *db);
void action(int mode, int db);
FILE *open_file(int db);

int main() {
    int mode, db;
    greetings(&mode);
    if ((mode != EXIT && mode >= 1 && mode <= 4) || mode == 6) {
        db_choice(&db);
        action(mode, db);
    } else if (mode == 5) {
        check("../materials/master_modules.db");
    } else {
        printf("n/a");
    }
    return 0;
}

void greetings(int *mode) {
    printf("Please choose one operation: \n");
    printf("\t0. EXIT\n");
    printf("\t1. SELECT\n");
    printf("\t2. INSERT\n");
    printf("\t3. UPDATE\n");
    printf("\t4. DELETE\n");
    printf("\t5. Does main module handle in the first cell of the first level ?\n");
    printf("\t6. Binary search of module by index\n");
    scanf("%d", mode);
}

void db_choice(int *db) {
    printf("Please choose a table: \n");
    printf("\t1. Modules \n");
    printf("\t2. Levels \n");
    printf("\t3. Status events \n");
    scanf("%d", db);
}

void action(int mode, int db_type) {
    FILE *file = open_file(db_type);
    if (mode == 1) {
        select(file, db_type);
    } else if (mode == 2) {
        insert(file, db_type);
    } else if (mode == 3) {
        update(file, db_type);
    } else if (mode == 4) {
        delete (file, db_type);
    } else if (mode == 6) {
        bin_search(file, db_type);
    }
    fclose(file);
}

FILE *open_file(int db) {
    FILE *file = NULL;
    if (db == 1) {
        file = fopen("../materials/master_modules.db", "rb+");
    } else if (db == 2) {
        file = fopen("../materials/master_levels.db", "rb+");
    } else {
        file = fopen("../materials/master_status_events.db", "rb+");
    }
    return file;
}