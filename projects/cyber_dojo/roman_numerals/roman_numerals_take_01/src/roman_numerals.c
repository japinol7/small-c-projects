#include "roman_numerals.h"
#include <string.h>

// To Roman conversion
int to_roman(int num, char* result, const int buffer_size) {
    // Check if num is within valid range
    if (num <= 0 || num > 3999 || buffer_size <= 0) {
        return -1; // Error: number out of range or buffer too small
    }

    // Define Roman numeral symbols and their values
    const int values[] = {
        1000, 900, 500, 400, 100, 90, 50,
        40, 10, 9, 5, 4, 1
    };
    const char* numerals[] = {
        "M", "CM", "D", "CD", "C", "XC", "L",
        "XL", "X", "IX", "V", "IV", "I"
    };
    const int num_elements = 13;

    // Clear the result buffer
    result[0] = '\0';
    int pos = 0;

    // Build Roman numeral
    for (int i = 0; i < num_elements; ++i) {
        while (num >= values[i]) {
            // Check buffer size to prevent overflow
            if (pos + strlen(numerals[i]) >= buffer_size) {
                return -1; // Buffer too small
            }

            // Append the numeral
            strcpy(result + pos, numerals[i]);
            pos += strlen(numerals[i]);
            num -= values[i];
        }
    }

    return 0; // Success
}
