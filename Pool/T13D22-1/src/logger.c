#include "logger.h"

#include "time.h"

FILE *log_init(char *filename) {
    FILE *file = fopen(filename, "w");
    return file;
}
int logcat(FILE *log_file, char *message, char *log_level) {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    return fprintf(log_file, "%s %d:%d:%d : %s", log_level, timeinfo->tm_hour, timeinfo->tm_min,
                   timeinfo->tm_sec, message);
}
int log_close(FILE *log_file) { return fclose(log_file); }