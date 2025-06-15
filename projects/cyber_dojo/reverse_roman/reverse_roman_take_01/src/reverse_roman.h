#ifndef REVERSE_ROMAN_H
#define REVERSE_ROMAN_H

#ifdef __cplusplus
extern "C" {
#endif

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

#endif // REVERSE_ROMAN_H
