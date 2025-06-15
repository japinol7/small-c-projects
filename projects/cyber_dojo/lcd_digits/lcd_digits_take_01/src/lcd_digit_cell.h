#ifndef LCD_DIGIT_CELL_H
#define LCD_DIGIT_CELL_H

// Chars used to display LCD digits and the separator string
#define CELL_H '_' // Horizontal segment
#define CELL_V '|' // Vertical segment
#define CELL_O '.' // Off segment
#define SEPARATOR " "

// Digit templates for each number with placeholders for separators
extern const char* const DIGITS_0;
extern const char* const DIGITS_1;
extern const char* const DIGITS_2;
extern const char* const DIGITS_3;
extern const char* const DIGITS_4;
extern const char* const DIGITS_5;
extern const char* const DIGITS_6;
extern const char* const DIGITS_7;
extern const char* const DIGITS_8;
extern const char* const DIGITS_9;

// NumToLcdDigitMapping maps integer digits to their LCD representation
extern const char* const NUM_TO_LCD_DIGIT_MAPPING[10];

#endif // LCD_DIGIT_CELL_H
