#include "lcd_digit_cell.h"

// Digit templates for each number with placeholders for separators
const char* const DIGITS_0 = "._.%s|.|%s|_|%s";
const char* const DIGITS_1 = "...%s..|%s..|%s";
const char* const DIGITS_2 = "._.%s._|%s|_.%s";
const char* const DIGITS_3 = "._.%s._|%s._|%s";
const char* const DIGITS_4 = "...%s|_|%s..|%s";
const char* const DIGITS_5 = "._.%s|_.%s._|%s";
const char* const DIGITS_6 = "._.%s|_.%s|_|%s";
const char* const DIGITS_7 = "._.%s..|%s..|%s";
const char* const DIGITS_8 = "._.%s|_|%s|_|%s";
const char* const DIGITS_9 = "._.%s|_|%s..|%s";

// NumToLcdDigitMapping maps integer digits to their LCD representation
const char* const NUM_TO_LCD_DIGIT_MAPPING[10] = {
    DIGITS_0,
    DIGITS_1,
    DIGITS_2,
    DIGITS_3,
    DIGITS_4,
    DIGITS_5,
    DIGITS_6,
    DIGITS_7,
    DIGITS_8,
    DIGITS_9
};
