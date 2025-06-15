#include "filename_range.h"
#include <stdio.h>
#include <string.h>

int main() {
    const char* app_name = "Filename Range";
    printf("Start app %s\n", app_name);

    const char* filename = "wibble/test/hiker_spec.rb";
    int name_range[2];
    const int result = filename_range(filename, name_range);

    if (result == 2) {
        // Create a buffer to hold the extracted substring
        const size_t len = name_range[1] - name_range[0];
        char wanted_name[len + 1];
        strncpy(wanted_name, filename + name_range[0], len);
        wanted_name[len] = '\0';

        printf("%s -> [%d, %d] -> %s\n", filename,
               name_range[0], name_range[1], wanted_name);
    }
    else {
        printf("%s -> Invalid range\n", filename);
    }

    printf("End app %s\n", app_name);
    return 0;
}
