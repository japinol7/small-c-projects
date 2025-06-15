#ifndef ROMAN_NUMERALS_H
#define ROMAN_NUMERALS_H

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

#ifdef __cplusplus
}
#endif

#endif // ROMAN_NUMERALS_H
