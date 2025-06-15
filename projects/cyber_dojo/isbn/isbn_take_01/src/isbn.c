#include "isbn.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// We represent the char X as -1
#define X_CHAR_INT_VALUE -1

// Validates if a given string is a valid ISBN-13 code
static const char* validate_isbn13(const int* isbn_digits, const int isbn_dc) {
    // Multiply each digit alternately by 1 or 3 and sum the results
    int check_digit = 0;
    for (int i = 0; i < 12; ++i) {
        if ((i + 1) % 2 == 0) {
            check_digit += isbn_digits[i] * 3;
        }
        else {
            check_digit += isbn_digits[i];
        }
    }
    check_digit %= 10;
    check_digit = (10 - check_digit) % 10;

    if (check_digit != isbn_dc) {
        return "false";
    }
    return "true";
}

// Validates if a given string is a valid ISBN-10 code
static const char* validate_isbn10(const int* isbn_digits, int isbn_dc) {
    if (isbn_dc == X_CHAR_INT_VALUE) {
        isbn_dc = 10;
    }

    // Multiply each digit by its position number and sum the results
    int check_digit = 0;
    for (int i = 0; i < 9; ++i) {
        check_digit += isbn_digits[i] * (i + 1);
    }
    check_digit %= 11;

    if (check_digit != isbn_dc) {
        return "false";
    }
    return "true";
}

char* validate_isbn(const char* isbn, char* result, const size_t result_size) {
    if (isbn == NULL || result == NULL || result_size == 0) {
        return NULL;
    }

    if (strlen(isbn) == 0) {
        strncpy(result, "false", result_size - 1);
        result[result_size - 1] = '\0';
        return result;
    }

    // Check if all chars except the last one are numeric, '-', or space
    for (size_t i = 0; i < strlen(isbn) - 1; ++i) {
        char ch = isbn[i];
        if (!isdigit((unsigned char)ch) && ch != '-' && ch != ' ') {
            strncpy(result, "false", result_size - 1);
            result[result_size - 1] = '\0';
            return result;
        }
    }

    // Extract digits for validation.
    // If the char is an X, extract it according to X_CHAR_INT_VALUE
    // Max 13 digits for ISBN-13
    int* isbn_nums = (int*)malloc(13 * sizeof(int));
    if (isbn_nums == NULL) {
        return NULL;
    }

    int isbn_len = 0;
    for (size_t i = 0; i < strlen(isbn) && isbn_len < 13; ++i) {
        if (isdigit((unsigned char)isbn[i])) {
            isbn_nums[isbn_len++] = isbn[i] - '0';
        }
        else if (isbn[i] == 'X' || isbn[i] == 'x') {
            isbn_nums[isbn_len++] = X_CHAR_INT_VALUE;
        }
    }

    const char* validation_result = "false";
    if (isbn_len == 13) {
        validation_result = validate_isbn13(
            isbn_nums, isbn_nums[isbn_len - 1]);
    }
    else if (isbn_len == 10) {
        validation_result = validate_isbn10(
            isbn_nums, isbn_nums[isbn_len - 1]);
    }

    free(isbn_nums);
    strncpy(result, validation_result, result_size - 1);
    result[result_size - 1] = '\0';
    return result;
}
