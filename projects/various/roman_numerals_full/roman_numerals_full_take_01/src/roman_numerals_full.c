#include "roman_numerals_full.h"
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

// From Roman conversion
int from_roman(const char* roman, int* result) {
    if (roman == NULL || result == NULL || roman[0] == '\0') {
        return -1; // Error: invalid input
    }

    // Map for Roman numeral symbols to values
    const struct {
        char symbol;
        int value;
    } roman_values[] = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}
    };
    const int num_symbols = 7;

    int total = 0;
    int prev_value = 0;

    // Process from right to left
    for (int i = strlen(roman) - 1; i >= 0; i--) {
        const char ch = roman[i];
        int value = 0;
        int found = 0;

        // Find the value for this symbol
        for (int j = 0; j < num_symbols; ++j) {
            if (roman_values[j].symbol == ch) {
                value = roman_values[j].value;
                found = 1;
                break;
            }
        }

        if (!found) {
            return -1; // Error: invalid Roman numeral character
        }

        // Add or subtract based on position
        if (value >= prev_value) {
            total += value;
        } else {
            total -= value;
        }
        prev_value = value;
    }

    // Check if the result is within the valid range for Roman numerals
    if (total <= 0 || total > 3999) {
        // Error: number out of range
        return -1;
    }

    *result = total;
    return 0; // Success
}
