#include <stdio.h>

#include "documentation_module.h"
#include "print_module.h"

int main() {
    print_log(print, Module_load_success_message);
    int *availability_mask = check_available_documentation_module(validate, Documents_count, Documents);
    const char *documents[] = {Documents};
    for (int i = 0; i < Documents_count; i++) {
        if (i < Documents_count - 1) {
            availability_mask[i] ? printf("%-15s : available\n", documents[i])
                                 : printf("%-15s : unavailable\n", documents[i]);
        } else {
            availability_mask[i] ? printf("%-15s : available", documents[i])
                                 : printf("%-15s : unavailable", documents[i]);
        }
    }
    free(availability_mask);
    return 0;
}
