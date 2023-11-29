#ifndef MASTER_LEVELS_H
#define MASTER_LEVELS_H
#include <stdio.h>

typedef struct levels_data {
    int memory_level;
    int count_memory_cells;
    int protection_flag;
} LEVELS;

void select_levels(FILE *db, int id);
void delete_levels(FILE *db, int id);
void insert_levels(FILE *db, LEVELS data);
void update_levels(FILE *db, int id, LEVELS data);
LEVELS get_note_levels(void);
LEVELS read_records_level(FILE *file, int index);
LEVELS bin_search_levels(FILE *db, int target_index);
#endif
