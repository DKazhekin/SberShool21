#include "master_modules.h"

#include <string.h>

void select_modules(FILE *db, int id) {
    if (id == 0) {
        fseek(db, 0, SEEK_END);
        int file_size = ftell(db);
        fseek(db, 0, SEEK_SET);

        id = file_size / sizeof(MODULES);
    }
    for (int i = 0; i < id; i++) {
        MODULES data = read_records_modules(db, i);
        printf("%d %s %d %d %d", data.module_id, data.module_name, data.module_memory_level,
               data.module_cell_on_curr_memory_level, data.del_flag);
        if (i < id - 1) {
            printf("\n");
        }
    }
}

void delete_modules(FILE *db, int id) {
    FILE *new_file = fopen("tmp.bin", "wb");

    fseek(db, 0, SEEK_END);
    int file_size = ftell(db);
    fseek(db, 0, SEEK_SET);

    int count_structs = file_size / sizeof(MODULES);

    for (int i = 0; i < count_structs; i++) {
        MODULES buffer = read_records_modules(db, i);
        if (buffer.module_id != id) {
            fwrite(&buffer, sizeof(MODULES), 1, new_file);
        }
    }

    fclose(new_file);
    remove("../materials/master_modules.db");
    rename("tmp.bin", "../materials/master_modules.db");
}

void insert_modules(FILE *db, MODULES data) {
    fseek(db, 0, SEEK_END);
    fwrite(&data, sizeof(MODULES), 1, db);
    fseek(db, 0, SEEK_SET);
}

void update_modules(FILE *db, int id, MODULES data) {
    int offset = id * sizeof(MODULES);
    fseek(db, offset, SEEK_SET);
    fwrite(&data, sizeof(MODULES), 1, db);
    fflush(db);
    rewind(db);
}

void check(char *file_path) {
    FILE *db = fopen(file_path, "r");
    int count_modules = 0;
    char module_name[30];

    fseek(db, 0, SEEK_END);
    int file_size = ftell(db);
    fseek(db, 0, SEEK_SET);

    int count_structs = file_size / sizeof(MODULES);

    for (int i = 0; i < count_structs; i++) {
        MODULES buffer = read_records_modules(db, i);
        if (buffer.module_memory_level == 1 && buffer.module_cell_on_curr_memory_level == 1) {
            count_modules++;
            strcpy(module_name, buffer.module_name);
        }
    }
    if (count_modules > 1 || strcmp(module_name, "Main module") != 0) {
        printf("NO");
    } else {
        printf("YES");
    }
}

MODULES get_note_modules(void) {
    MODULES note;
    scanf("%d %30s %d %d %d", &note.module_id, note.module_name, &note.module_memory_level,
          &note.module_cell_on_curr_memory_level, &note.del_flag);
    return note;
}

MODULES read_records_modules(FILE *file, int index) {
    int offset = index * sizeof(MODULES);
    fseek(file, offset, SEEK_SET);
    MODULES record;
    fread(&record, sizeof(MODULES), 1, file);
    rewind(file);
    return record;
}

MODULES bin_search_modules(FILE *db, int target_index) {
    int left = 0;

    fseek(db, 0, SEEK_END);
    int file_size = ftell(db);
    fseek(db, 0, SEEK_SET);

    int right = file_size / sizeof(MODULES);

    while (left <= right) {
        int mid = left + (right - left) / 2;

        MODULES tmp = read_records_modules(db, mid);
        if (tmp.module_id == target_index) {
            return tmp;
        } else if (tmp.module_id < target_index) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    MODULES empty;
    empty.module_id = -1;
    strcpy(empty.module_name, "123");
    empty.module_cell_on_curr_memory_level = 0;
    empty.module_memory_level = 0;
    empty.del_flag = 0;
    return empty;
}
