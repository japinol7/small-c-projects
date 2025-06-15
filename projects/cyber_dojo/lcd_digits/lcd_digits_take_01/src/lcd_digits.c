#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcd_digits.h"
#include "lcd_digit_cell.h"

// Initialize a new LcdDigitsError
static void lcd_digits_error_init(LcdDigitsError* error, const char* message) {
    if (error) {
        strncpy(error->message, message, sizeof(error->message) - 1);
        error->message[sizeof(error->message) - 1] = '\0';
    }
}

// Initialize a new LcdDigits instance
LcdDigits lcd_digits_new() {
    LcdDigits lcd = {0};
    return lcd;
}

// Generate single digit LCD representation
static int generate_single_digit(
    const int digit, char* buffer, const size_t buffer_size
) {
    snprintf(buffer, buffer_size, NUM_TO_LCD_DIGIT_MAPPING[digit], "\n", "\n", "\n");
    return 0;
}

// Helper function to generate multiple digits
static int generate_multiple_digits(int num, const char* separator, char* output_str, size_t output_size) {
    char num_str[32]; // Buffer for number string
    snprintf(num_str, sizeof(num_str), "%d", num);
    const size_t num_len = strlen(num_str);

    // Allocate memory for each part of the digits
    char** digits_top = (char**)malloc(num_len * sizeof(char*));
    char** digits_mid = (char**)malloc(num_len * sizeof(char*));
    char** digits_bottom = (char**)malloc(num_len * sizeof(char*));

    if (!digits_top || !digits_mid || !digits_bottom) {
        free(digits_top);
        free(digits_mid);
        free(digits_bottom);
        return -1;
    }

    // Allocate memory for each digit part
    for (size_t i = 0; i < num_len; ++i) {
        digits_top[i] = (char*)malloc(32);
        digits_mid[i] = (char*)malloc(32);
        digits_bottom[i] = (char*)malloc(32);

        if (!digits_top[i] || !digits_mid[i] || !digits_bottom[i]) {
            // Clean up on allocation failure
            for (size_t j = 0; j <= i; ++j) {
                free(digits_top[j]);
                free(digits_mid[j]);
                free(digits_bottom[j]);
            }
            free(digits_top);
            free(digits_mid);
            free(digits_bottom);
            return -1;
        }
    }

    // Generate each part of each digit
    for (size_t i = 0; i < num_len; ++i) {
        const int digit = num_str[i] - '0';
        const char* cur_separator = (i < num_len - 1) ? separator : "\n";

        const char* digit_template = NUM_TO_LCD_DIGIT_MAPPING[digit];

        // Create the parts with the correct separator
        snprintf(digits_top[i], 32, "%.3s%s", digit_template, cur_separator);
        snprintf(digits_mid[i], 32, "%.3s%s", digit_template + 5, cur_separator);
        snprintf(digits_bottom[i], 32, "%.3s%s", digit_template + 10, cur_separator);
    }

    // Combine all parts into the output string
    output_str[0] = '\0';
    for (size_t i = 0; i < num_len; ++i) {
        strncat(output_str, digits_top[i], output_size - strlen(output_str) - 1);
    }
    for (size_t i = 0; i < num_len; ++i) {
        strncat(output_str, digits_mid[i], output_size - strlen(output_str) - 1);
    }
    for (size_t i = 0; i < num_len; ++i) {
        strncat(output_str, digits_bottom[i], output_size - strlen(output_str) - 1);
    }

    // Clean up allocated memory
    for (size_t i = 0; i < num_len; ++i) {
        free(digits_top[i]);
        free(digits_mid[i]);
        free(digits_bottom[i]);
    }
    free(digits_top);
    free(digits_mid);
    free(digits_bottom);

    return 0;
}

// Generate creates an LCD representation of a number
int lcd_digits_generate(const int num, char* output_str, const size_t output_size,
                        LcdDigitsError* error, const char* separator) {
    // Use default separator if none provided
    const char* sep = separator ? separator : SEPARATOR;

    if (num < 0) {
        lcd_digits_error_init(error, "Number must be non-negative");
        return -1;
    }

    // Handle the single digit case
    if (num <= 9) {
        return generate_single_digit(num, output_str, output_size);
    }

    // Handle the multi-digit case
    if (generate_multiple_digits(num, sep, output_str, output_size) != 0) {
        lcd_digits_error_init(error, "Failed to generate multiple digits");
        return -1;
    }

    return 0;
}
