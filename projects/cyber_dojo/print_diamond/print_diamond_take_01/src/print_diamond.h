#ifndef PRINT_DIAMOND_H
#define PRINT_DIAMOND_H

#ifdef __cplusplus
extern "C" {
#endif

// Constants
#define START_LETTER 'A'
#define SEPARATOR " "

// Diamond structure represents a letter diamond pattern
typedef struct {
    char letter;
    char** pattern;
    int patternSize;
} Diamond;

// Create a new diamond pattern for the given letter
// Returns a Diamond structure that must be freed with freeDiamond
Diamond* newDiamond(const char* letter);

// Convert diamond to string representation
// The returned string must be freed by the caller
char* diamondToString(const Diamond* diamond);

// Free all resources associated with a Diamond
void freeDiamond(Diamond* diamond);

#ifdef __cplusplus
}
#endif

#endif // PRINT_DIAMOND_H
