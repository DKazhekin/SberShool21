#include "master_levels.h"

void select_levels(FILE *db, int id) {
    if (id == 0) {
        fseek(db, 0, SEEK_END);
        int file_size = ftell(db);
        fseek(db, 0, SEEK_SET);

        id = file_size / sizeof(LEVELS);
    }
    for (int i = 0; i < id; i++) {
        LEVELS data = read_records_level(db, i);
        printf("%d %d %d", data.memory_level, data.count_memory_cells, data.protection_flag);
        if (i < id - 1) {
            printf("\n");
        }
    }
}

void delete_levels(FILE *db, int id) {
    FILE *new_file = fopen("tmp.bin", "wb");

    fseek(db, 0, SEEK_END);
    int file_size = ftell(db);
    fseek(db, 0, SEEK_SET);

    int count_structs = file_size / sizeof(LEVELS);

    for (int i = 0; i < count_structs; i++) {
        LEVELS buffer = read_records_level(db, i);
        if (buffer.memory_level != id) {
            fwrite(&buffer, sizeof(LEVELS), 1, new_file);
        }
    }

    fclose(new_file);
    remove("../materials/master_levels.db");
    rename("tmp.bin", "../materials/master_levels.db");
}

void insert_levels(FILE *db, LEVELS data) {
    fseek(db, 0, SEEK_END);
    fwrite(&data, sizeof(LEVELS), 1, db);
    fseek(db, 0, SEEK_SET);
}

void update_levels(FILE *db, int id, LEVELS data) {
    int offset = id * sizeof(LEVELS);
    fseek(db, offset, SEEK_SET);
    fwrite(&data, sizeof(LEVELS), 1, db);
    fflush(db);
    rewind(db);
}

LEVELS get_note_levels(void) {
    LEVELS note;
    scanf("%d %d %d", &note.memory_level, &note.count_memory_cells, &note.protection_flag);
    return note;
}

LEVELS read_records_level(FILE *file, int index) {
    int offset = index * sizeof(LEVELS);
    fseek(file, offset, SEEK_SET);
    LEVELS record;
    fread(&record, sizeof(LEVELS), 1, file);
    rewind(file);
    return record;
}

LEVELS bin_search_levels(FILE *db, int target_index) {
    int left = 0;

    fseek(db, 0, SEEK_END);
    int file_size = ftell(db);
    fseek(db, 0, SEEK_SET);

    int right = file_size / sizeof(LEVELS);

    while (left <= right) {
        int mid = left + (right - left) / 2;

        LEVELS tmp = read_records_level(db, mid);
        if (tmp.memory_level == target_index) {
            return tmp;
        } else if (tmp.memory_level < target_index) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    LEVELS empty;
    empty.memory_level = -1;
    empty.protection_flag = 0;
    empty.count_memory_cells = 0;
    return empty;
}