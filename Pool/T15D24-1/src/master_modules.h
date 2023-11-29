#ifndef MASTER_MODULES_H
#define MASTER_MODULES_H
#include <stdio.h>

typedef struct module_data {
    int module_id;
    char module_name[30];
    int module_memory_level;
    int module_cell_on_curr_memory_level;
    int del_flag;
} MODULES;

void select_modules(FILE *db, int id);
void delete_modules(FILE *db, int id);
void insert_modules(FILE *db, MODULES data);
void update_modules(FILE *db, int id, MODULES data);
void check(char *file_path);
MODULES bin_search_modules(FILE *db, int target_index);
MODULES get_note_modules(void);
MODULES read_records_modules(FILE *file, int index);

#endif