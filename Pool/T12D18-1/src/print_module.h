#ifndef PRINT_MODULE_H
#define PRINT_MODULE_H
#define Module_load_success_message "Output stream module load: success\n"
#define Log_prefix "[LOG]"

void print_log(void (*print)(char *), char *message);
void print(char *message);

#endif
