#include "reverse_roman.h"
#include <stdio.h>

int main() {
    int result;
    const char* app_name = "Reverse Roman";

    printf("Start app: %s\n", app_name);

    // Examples of Roman numeral to number conversion
    const char* roman_nums[] = {
        "I", "IV", "IX", "XIV", "XLII", "LXXIII", "XCIX", "MMXXIII"
    };
    const int roman_count = 8;

    printf("\nConverting Roman numerals to numbers:\n");
    for (int i = 0; i < roman_count; ++i) {
        if (from_roman(roman_nums[i], &result) == 0) {
            printf("%s -> %d\n", roman_nums[i], result);
        }
        else {
            printf("Error converting %s\n", roman_nums[i]);
        }
    }

    printf("\nEnd app: %s\n", app_name);
    return 0;
}
