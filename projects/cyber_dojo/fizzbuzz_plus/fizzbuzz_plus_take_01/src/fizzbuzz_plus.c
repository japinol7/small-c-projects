#include "fizzbuzz_plus.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int contains_digit(int number, int digit) {
    while (number > 0) {
        if (number % 10 == digit) {
            return 1;
        }
        number /= 10;
    }
    return 0;
}

char* fizzbuzz(const int n, char* buffer, const size_t buffer_size) {
    if (buffer == NULL || buffer_size == 0) {
        return NULL;
    }

    // Init to an empty string
    buffer[0] = '\0';

    if (n % 3 == 0 || contains_digit(n, 3)) {
        strncat(buffer, "Fizz", buffer_size - 1);
    }

    if (n % 5 == 0 || contains_digit(n, 5)) {
        strncat(buffer, "Buzz", buffer_size - 1);
    }

    if (buffer[0] == '\0') {
        snprintf(buffer, buffer_size, "%d", n);
    }

    return buffer;
}

char** fizzbuzz_range(const int n, char** result) {
    if (n <= 0 || result == NULL) {
        return NULL;
    }

    for (int i = 1; i <= n; ++i) {
        // Allocate memory for each string
        result[i - 1] = (char*)malloc(20 * sizeof(char));
        if (result[i - 1] == NULL) {
            // Handle allocation failure by freeing previous allocations
            for (int j = 0; j < i - 1; ++j) {
                free(result[j]);
            }
            return NULL;
        }

        fizzbuzz(i, result[i - 1], 20);
    }

    return result;
}

void free_fizzbuzz_range(char** result, const int count) {
    if (result == NULL) {
        return;
    }

    for (int i = 0; i < count; ++i) {
        free(result[i]);
    }
}
