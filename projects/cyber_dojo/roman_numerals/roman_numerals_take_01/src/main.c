#include "roman_numerals.h"
#include <stdio.h>

int main() {
    char buffer[20];
    const char* app_name = "Roman Numerals";

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

    printf("\nEnd app: %s\n", app_name);
    return 0;
}
