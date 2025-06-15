#include "print_diamond.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

// Helper function prototypes
static int isInputValid(char letter);
static char* centerString(const char* str, int width);
static void addLinesUntilMiddleOfDiamond(
    const Diamond* diamond, int width, int lenToStartLetter
);
static void createDiamondPattern(Diamond* diamond);

// Create a new diamond pattern for the given letter
Diamond* newDiamond(const char* letter) {
    Diamond* diamond = (Diamond*)malloc(sizeof(Diamond));
    if (!diamond) {
        return NULL;
    }

    // Initialize diamond
    diamond->letter = 0;
    diamond->pattern = NULL;
    diamond->patternSize = 0;

    // Validate input
    if (!letter || letter[0] == '\0' || letter[1] != '\0') {
        return diamond;
    }

    // Convert to uppercase
    diamond->letter = toupper(letter[0]);

    if (!isInputValid(diamond->letter)) {
        return diamond;
    }

    // Special case for 'A'
    if (diamond->letter == START_LETTER) {
        diamond->patternSize = 1;
        diamond->pattern = (char**)malloc(sizeof(char*));
        if (!diamond->pattern) {
            freeDiamond(diamond);
            return NULL;
        }

        diamond->pattern[0] = strdup("A");
        if (!diamond->pattern[0]) {
            freeDiamond(diamond);
            return NULL;
        }

        return diamond;
    }

    // Create diamond pattern
    createDiamondPattern(diamond);
    return diamond;
}

// Check if the input letter is valid for creating a diamond
static int isInputValid(const char letter) {
    if (letter == 0 || letter < 'A' || letter > 'Z') {
        return 0;
    }
    return 1;
}

// Centers a string within a given width
static char* centerString(const char* str, const int width) {
    const int strLen = strlen(str);
    if (strLen >= width) {
        return strdup(str);
    }

    const int leftPadding = (width - strLen) / 2;
    const int rightPadding = width - strLen - leftPadding;

    char* centered = (char*)malloc(width + 1);
    if (!centered) {
        return NULL;
    }

    // Add left padding
    int pos = 0;
    for (int i = 0; i < leftPadding; ++i) {
        centered[pos++] = ' ';
    }

    // Add the string
    strcpy(centered + pos, str);
    pos += strLen;

    // Add right padding
    for (int i = 0; i < rightPadding; ++i) {
        centered[pos++] = ' ';
    }

    centered[pos] = '\0';
    return centered;
}

// Add lines to the diamond pattern from A to the specified letter
static void addLinesUntilMiddleOfDiamond(
    const Diamond* diamond, const int width, const int lenToStartLetter
) {
    // Add the first line with just 'A'
    const char aStr[2] = {START_LETTER, '\0'};
    diamond->pattern[0] = centerString(aStr, width);

    // Add lines from 'B' to the specified letter
    for (int i = 1; i <= lenToStartLetter; ++i) {
        const char ch = START_LETTER + i;
        const int spaces = 2 * i - 1;

        // Create line: char + spaces + char
        char* line = (char*)malloc(width + 1);
        if (!line) {
            return;
        }

        // Format the line with a character at each end and spaces between
        sprintf(line, "%c%*s%c", ch, spaces, "", ch);

        // Center the line
        diamond->pattern[i] = centerString(line, width);
        free(line);
    }
}

// Create the diamond pattern
static void createDiamondPattern(Diamond* diamond) {
    const int lenToStartLetter = diamond->letter - START_LETTER;
    const int width = 2 * lenToStartLetter + 1;

    // Calculate the total number of lines in the diamond
    diamond->patternSize = 2 * lenToStartLetter + 1;

    // Allocate memory for the pattern
    diamond->pattern = (char**)malloc(diamond->patternSize * sizeof(char*));
    if (!diamond->pattern) {
        diamond->patternSize = 0;
        return;
    }

    // Initialize all pointers to NULL
    for (int i = 0; i < diamond->patternSize; ++i) {
        diamond->pattern[i] = NULL;
    }

    // Add lines until the middle of the diamond
    addLinesUntilMiddleOfDiamond(diamond, width, lenToStartLetter);

    // Add mirrored lines to complete the diamond
    for (int i = 0; i < lenToStartLetter; ++i) {
        diamond->pattern[diamond->patternSize - 1 - i] = strdup(diamond->pattern[i]);
    }
}

// Convert diamond to string representation
char* diamondToString(const Diamond* diamond) {
    if (!diamond || !diamond->pattern || diamond->patternSize <= 0) {
        return strdup("");
    }

    // Calculate the total length needed for the string
    size_t totalLength = 0;
    for (int i = 0; i < diamond->patternSize; ++i) {
        totalLength += strlen(diamond->pattern[i]);
    }

    // Add space for newlines and null terminator
    totalLength += diamond->patternSize; 

    char* result = (char*)malloc(totalLength);
    if (!result) {
        return NULL;
    }

    // Build the string
    result[0] = '\0';
    for (int i = 0; i < diamond->patternSize; ++i) {
        strcat(result, diamond->pattern[i]);
        if (i < diamond->patternSize - 1) {
            strcat(result, "\n");
        }
    }

    return result;
}

// Free all resources associated with a Diamond
void freeDiamond(Diamond* diamond) {
    if (!diamond) {
        return;
    }

    if (diamond->pattern) {
        for (int i = 0; i < diamond->patternSize; ++i) {
            free(diamond->pattern[i]);
        }
        free(diamond->pattern);
    }

    free(diamond);
}
