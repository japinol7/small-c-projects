#include <stdio.h>
#include "lcd_digits.h"

int main() {
    const char* appName = "LCD Digits";
    printf("Start app %s\n", appName);

    const int inputNumber = 1234567890;
    LcdDigits lcd = lcd_digits_new();
    // Large enough buffer for result
    char result[4096];
    LcdDigitsError error;

    const int ret = lcd_digits_generate(
        inputNumber, result, sizeof(result), &error, NULL);

    if (ret != 0) {
        printf("Error: %s\n", error.message);
    } else {
        printf("LCD Digits for %d\n%s\n", inputNumber, result);
    }

    printf("End app %s\n", appName);
    return 0;
}
