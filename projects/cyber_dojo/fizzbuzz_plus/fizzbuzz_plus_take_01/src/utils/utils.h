#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

/**
 * Converts an array of strings to a newline-separated string
 * @param items The array of strings
 * @param count The number of items in the array
 * @param buffer The buffer to store the result
 * @param buffer_size The size of the buffer
 * @return The buffer containing the result
 */
char* string_join(char** items, int count, char* buffer, size_t buffer_size);

#endif /* UTILS_H */
