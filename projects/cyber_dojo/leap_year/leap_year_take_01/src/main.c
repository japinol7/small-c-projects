#include <stdio.h>
#include "leap_year.h"

int main() {
    const char* appName = "Leap Year";
    printf("Start app: %s\n", appName);

    const int exampleYears[] = {
        2001, 1996, 1900, 2000, 2023, 2024
    };
    const int exampleYearsLen = sizeof(exampleYears) / sizeof(exampleYears[0]);

    for (int i = 0; i < exampleYearsLen; ++i) {
        const int year = exampleYears[i];
        const int result = IsLeapYear(year);
        printf("Is %d a leap year: %s\n",
            year, result ? "true" : "false");
    }

    printf("End app: %s\n", appName);
    return 0;
}
