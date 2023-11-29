#include "master_status_events.h"

#include <string.h>

void select_status_events(FILE *db, int id) {
    if (id == 0) {
        fseek(db, 0, SEEK_END);
        int file_size = ftell(db);
        fseek(db, 0, SEEK_SET);

        id = file_size / sizeof(STATUS_EVENTS);
    }
    for (int i = 0; i < id; i++) {
        STATUS_EVENTS data = read_records_status_events(db, i);
        printf("%d %d %d %s %s", data.event_id, data.module_id, data.new_module_status, data.change_date,
               data.change_time);
        if (i < id - 1) {
            printf("\n");
        }
    }
}

void delete_status_events(FILE *db, int id) {
    FILE *new_file = fopen("tmp.bin", "wb");

    fseek(db, 0, SEEK_END);
    int file_size = ftell(db);
    fseek(db, 0, SEEK_SET);

    int count_structs = file_size / sizeof(STATUS_EVENTS);

    for (int i = 0; i < count_structs; i++) {
        STATUS_EVENTS buffer = read_records_status_events(db, i);
        if (buffer.event_id != id) {
            fwrite(&buffer, sizeof(STATUS_EVENTS), 1, new_file);
        }
    }

    fclose(new_file);
    remove("../materials/master_status_events.db");
    rename("tmp.bin", "../materials/master_status_events.db");
}

void insert_status_events(FILE *db, STATUS_EVENTS data) {
    fseek(db, 0, SEEK_END);
    fwrite(&data, sizeof(STATUS_EVENTS), 1, db);
    fseek(db, 0, SEEK_SET);
}
void update_status_events(FILE *db, int id, STATUS_EVENTS data) {
    int offset = id * sizeof(STATUS_EVENTS);
    fseek(db, offset, SEEK_SET);
    fwrite(&data, sizeof(STATUS_EVENTS), 1, db);
    fflush(db);
    rewind(db);
}

STATUS_EVENTS get_note_status_events(void) {
    STATUS_EVENTS note;
    scanf("%d %d %d %10s %8s", &note.event_id, &note.module_id, &note.new_module_status, note.change_date,
          note.change_time);
    return note;
}

STATUS_EVENTS read_records_status_events(FILE *file, int index) {
    int offset = index * sizeof(STATUS_EVENTS);
    fseek(file, offset, SEEK_SET);
    STATUS_EVENTS record;
    fread(&record, sizeof(STATUS_EVENTS), 1, file);
    rewind(file);
    return record;
}

STATUS_EVENTS bin_search_status_events(FILE *db, int target_index) {
    int left = 0;

    fseek(db, 0, SEEK_END);
    int file_size = ftell(db);
    fseek(db, 0, SEEK_SET);

    int right = file_size / sizeof(STATUS_EVENTS);

    while (left <= right) {
        int mid = left + (right - left) / 2;

        STATUS_EVENTS tmp = read_records_status_events(db, mid);
        if (tmp.event_id == target_index) {
            return tmp;
        } else if (tmp.event_id < target_index) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    STATUS_EVENTS empty;
    empty.event_id = -1;
    empty.module_id = 0;
    empty.new_module_status = 0;
    strcpy(empty.change_time, "123");
    strcpy(empty.change_date, "123");
    return empty;
}
