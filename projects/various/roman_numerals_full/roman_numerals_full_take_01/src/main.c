#include "roman_numerals_full.h"
#include <stdio.h>

int main() {
    char buffer[20];
    int result;
    const char* app_name = "Roman Numerals Full";

    printf("Start app: %s\n", app_name);

    // Examples of number to Roman numeral conversion
    int nums[] = {1, 4, 9, 14, 42, 73, 99, 2023};
    const int nums_count = 8;

    printf("\nConverting numbers to Roman numerals:\n");
    for (int i = 0; i < nums_count; ++i) {
        if (to_roman(nums[i], buffer, sizeof(buffer)) == 0) {
            printf("%d -> %s\n", nums[i], buffer);
        }
        else {
            printf("Error converting %d\n", nums[i]);
        }
    }

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
