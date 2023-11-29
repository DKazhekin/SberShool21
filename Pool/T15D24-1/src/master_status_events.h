#ifndef MASTER_STATUS_EVENTS_H
#define MASTER_STATUS_EVENTS_H
#include <stdio.h>

typedef struct status_events_data {
    int event_id;
    int module_id;
    int new_module_status;
    char change_date[11];
    char change_time[9];
} STATUS_EVENTS;

void select_status_events(FILE *db, int id);
void delete_status_events(FILE *db, int id);
void insert_status_events(FILE *db, STATUS_EVENTS data);
void update_status_events(FILE *db, int id, STATUS_EVENTS data);
STATUS_EVENTS get_note_status_events(void);
STATUS_EVENTS read_records_status_events(FILE *file, int index);
STATUS_EVENTS bin_search_status_events(FILE *db, int target_index);

#endif