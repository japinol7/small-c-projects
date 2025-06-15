// lcd_digits.h
#ifndef LCD_DIGITS_H
#define LCD_DIGITS_H

// LcdDigitsError represents an error in LCD digits generation
typedef struct {
    char message[256];
} LcdDigitsError;

// LcdDigits generates LCD-style digit representations
typedef struct {
    int placeholder; // Empty struct placeholder
} LcdDigits;

// Initialize a new LcdDigits instance
LcdDigits lcd_digits_new();

// Generate creates an LCD representation of a number
// Returns 0 on success, fills output_str with the result
// Returns -1 on error, fills error with the error message
int lcd_digits_generate(int num, char* output_str, size_t output_size,
                        LcdDigitsError* error, const char* separator);

#endif // LCD_DIGITS_H
