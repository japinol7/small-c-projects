#include <stdio.h>
#include <stdlib.h>
#include "fizzbuzz.h"
#include "utils/utils.h"

int main() {
    const char* appName = "Fizzbuzz";
    printf("Start app %s\n", appName);

    const int n = 15;
    char** result = (char**)malloc(n * sizeof(char*));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    fizzbuzz_range(n, result);

    // Buffer to hold the joined string
    char buffer[1024];
    string_join(result, n, buffer, sizeof(buffer));

    printf("%s\n", buffer);

    // Free allocated memory
    free_fizzbuzz_range(result, n);
    free(result);

    printf("\nEnd app %s\n", appName);
    return 0;
}
