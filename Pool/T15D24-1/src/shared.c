#include "shared.h"

void select(FILE *db, int type) {
    int id;
    printf("Insert the number of records to output or '0' to output all: ");
    scanf("%d", &id);
    if (type == 1) {
        select_modules(db, id);
    } else if (type == 2) {
        select_levels(db, id);
    } else {
        select_status_events(db, id);
    }
}

void insert(FILE *db, int type) {
    printf("Insert the data to put in table: \n");
    if (type == 1) {
        MODULES data = get_note_modules();
        insert_modules(db, data);
    } else if (type == 2) {
        LEVELS data = get_note_levels();
        insert_levels(db, data);
    } else {
        STATUS_EVENTS data = get_note_status_events();
        insert_status_events(db, data);
    }
}

void delete (FILE *db, int type) {
    int id;
    printf("Insert the index of deleting line: ");
    scanf("%d", &id);
    if (type == 1) {
        delete_modules(db, id);
    } else if (type == 2) {
        delete_levels(db, id);
    } else {
        delete_status_events(db, id);
    }
}

void update(FILE *db, int type) {
    int id;
    printf("Insert the index of line which you want to update: ");
    scanf("%d", &id);
    printf("Insert the data you want to refresh: \n");
    if (type == 1) {
        MODULES data = get_note_modules();
        update_modules(db, id, data);
    } else if (type == 2) {
        LEVELS data = get_note_levels();
        update_levels(db, id, data);
    } else {
        STATUS_EVENTS data = get_note_status_events();
        update_status_events(db, id, data);
    }
}

void bin_search(FILE *db, int type) {
    int index;
    printf("Insert the index, which object you want to find: ");
    scanf("%d", &index);
    if (type == 1) {
        MODULES found = bin_search_modules(db, index);
        if (found.module_id == -1) {
            printf("There is no such module !");
        } else {
            printf("This is your module: ");
            printf("%d %s %d %d %d", found.module_id, found.module_name, found.module_memory_level,
                   found.module_cell_on_curr_memory_level, found.del_flag);
        }
    } else if (type == 2) {
        LEVELS found = bin_search_levels(db, index);
        if (found.memory_level == -1) {
            printf("There is no such module !");
        } else {
            printf("This is your module: ");
            printf("%d %d %d", found.memory_level, found.count_memory_cells, found.protection_flag);
        }
    } else {
        STATUS_EVENTS found = bin_search_status_events(db, index);
        if (found.event_id == -1) {
            printf("There is no such module !");
        } else {
            printf("This is your module: ");
            printf("%d %d %d %s %s", found.event_id, found.module_id, found.new_module_status,
                   found.change_date, found.change_time);
        }
    }
}