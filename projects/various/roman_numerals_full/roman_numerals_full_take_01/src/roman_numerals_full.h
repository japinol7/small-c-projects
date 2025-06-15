#ifndef ROMAN_NUMERALS_FULL_H
#define ROMAN_NUMERALS_FULL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Converts an integer to a Roman numeral string
 * 
 * @param num The integer to convert (must be between 1 and 3999 inclusive)
 * @param result Buffer to store the resulting Roman numeral string
 * @param buffer_size Size of the result buffer
 * @return 0 on success, -1 on error
 */
int to_roman(int num, char* result, int buffer_size);

/**
 * Converts a Roman numeral string to an integer
 * 
 * @param roman The Roman numeral string to convert
 * @param result Pointer to store the resulting integer value
 * @return 0 on success, -1 on error
 */
int from_roman(const char* roman, int* result);

#ifdef __cplusplus
}
#endif

#endif // ROMAN_NUMERALS_FULL_H
