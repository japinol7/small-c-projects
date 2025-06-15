#ifndef FIZZBUZZ_PLUS_H
#define FIZZBUZZ_PLUS_H

#include <stdlib.h>

/**
 * Converts a number to its FizzBuzz string representation
 * @param n The number to convert
 * @param buffer The buffer to store the result
 * @param buffer_size The size of the buffer
 * @return The buffer containing the result
 */
char* fizzbuzz(int n, char* buffer, size_t buffer_size);

/**
 * Generates FizzBuzz strings for numbers from 1 to n
 * @param n The upper limit
 * @param result Array of char pointers to store the results
 * @return The array of FizzBuzz strings
 */
char** fizzbuzz_range(int n, char** result);

/**
 * Frees memory allocated for the result of fizzbuzz_range
 * @param result The array of strings to free
 * @param count The number of items in the array
 */
void free_fizzbuzz_range(char** result, int count);

#endif /* FIZZBUZZ_PLUS_H */
