#ifndef ISBN_H
#define ISBN_H

#include <stdlib.h>

/**
 * Validates if a given string is a valid ISBN-13 or ISBN-10 code.
 *
 * @param isbn The ISBN string to validate
 * @param result Buffer to store the result string ("true" or "false")
 * @param result_size Size of the result buffer
 * @return Pointer to the result buffer or NULL if error
 */
char* validate_isbn(const char* isbn, char* result, size_t result_size);

#endif /* ISBN_H */
