#ifndef SHARED_H
#define SHARED_H
#include "master_levels.h"
#include "master_modules.h"
#include "master_status_events.h"

void select(FILE *db, int type);
void insert(FILE *db, int type);
void delete (FILE *db, int type);
void update(FILE *db, int type);
void bin_search(FILE *db, int type);

#endif