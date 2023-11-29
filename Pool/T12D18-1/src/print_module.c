#include "print_module.h"

#include <stdio.h>
#include <time.h>

void print(char *message) {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    printf("%s %d:%d:%d %s", Log_prefix, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, message);
}

void print_log(void (*print)(char *), char *message) { print(message); }
