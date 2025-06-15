#include "filename_range.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

// Characters to exclude from the left (directory separators)
static bool is_char_to_exclude_left(char ch) {
    return ch == '\\' || ch == '/';
}

// Words to keep in the filename (test-related words)
static const char* words_to_keep[] = {
    "tests", "test", "spec", "step",
    NULL // sentinel
};

// Separator characters
static bool is_separator(char ch) {
    return ch == '-' || ch == '_' || ch == '.';
}

/**
 * Adjusts the right mark if the word to keep is found to the right of the left mark
 */
static int keep_word_on_the_right(const char* text, const char* word_to_keep, int left_mark, int right_mark) {
    const char* found = strstr(text, word_to_keep);
    if (found != NULL) {
        const int word_idx = found - text;
        if (0 < word_idx && word_idx < right_mark) {
            right_mark = word_idx;
            if (right_mark > 0 && is_separator(text[right_mark - 1])) {
                right_mark--;
            }
        }
    }
    return right_mark;
}

/**
 * Adjusts the left mark if the word to keep is found to the left of the right mark
 */
static int keep_word_on_the_left(const char* text, const char* word_to_keep, int left_mark) {
    const char* found = strstr(text, word_to_keep);
    if (found != NULL) {
        const int word_idx = found - text;
        if (word_idx >= left_mark) {
            left_mark = word_idx + strlen(word_to_keep);
            if (left_mark < (int)strlen(text) && is_separator(text[left_mark])) {
                left_mark++;
            }
        }
    }
    return left_mark;
}

int filename_range(const char* filename, int range[2]) {
    if (filename == NULL || *filename == '\0') {
        return 0; // Empty result for empty input
    }

    // Create a lowercase copy of the filename for case-insensitive operations
    const size_t name_len = strlen(filename);
    char* name = (char*)malloc(name_len + 1);
    if (name == NULL) {
        return 0; // Memory allocation failure
    }

    for (size_t i = 0; i < name_len; ++i) {
        name[i] = tolower(filename[i]);
    }
    name[name_len] = '\0';

    // Remove chars from the left to the last char to exclude
    int left_mark = 0;
    for (int i = name_len - 1; i >= 0; i--) {
        if (is_char_to_exclude_left(name[i])) {
            left_mark = i + 1;
            break;
        }
    }

    // Remove chars from the right of the first dot char
    int right_mark = name_len;
    for (size_t i = 0; i < name_len; ++i) {
        if (name[i] == '.') {
            right_mark = i;
            break;
        }
    }

    // Remove words to keep on the right and their separators
    const char* name_tp = name + left_mark;
    int relative_right_mark = right_mark - left_mark;
    for (int i = 0; words_to_keep[i] != NULL; ++i) {
        relative_right_mark = keep_word_on_the_right(
            name_tp, words_to_keep[i], 0, relative_right_mark);
    }
    right_mark = left_mark + relative_right_mark;

    // Remove words to keep on the left and their separators
    char name_tp_left[name_len + 1];
    strncpy(name_tp_left, name, right_mark);
    name_tp_left[right_mark] = '\0';

    for (int i = 0; words_to_keep[i] != NULL; ++i) {
        left_mark = keep_word_on_the_left(
            name_tp_left, words_to_keep[i], left_mark);
    }

    free(name);
    range[0] = left_mark;
    range[1] = right_mark;

    // Return size of range array
    return 2;
}
