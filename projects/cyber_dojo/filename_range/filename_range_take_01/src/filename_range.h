#ifndef FILENAME_RANGE_H
#define FILENAME_RANGE_H

#include <stdbool.h>
#include <stdlib.h>

/**
 * Calculates the range of characters in a filename that should be selected
 * when renaming the file, excluding directory paths, extensions, and special
 * test-related words.
 *
 * @param filename The filename to analyze
 * @param range An array to store the start and end indices [start, end]
 * @return The number of elements in the range (2 for success, 0 for empty input)
 */
int filename_range(const char* filename, int range[2]);

#endif /* FILENAME_RANGE_H */
