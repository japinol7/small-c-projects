#include "reverse_roman.h"
#include <string.h>

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
