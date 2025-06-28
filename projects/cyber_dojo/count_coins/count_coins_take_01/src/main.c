#include "count_coins.h"
#include <stdio.h>

int main() {
    const char* app_name = "Count coins";
    printf("Start app %s\n", app_name);

    const int result = count_coins_changes(100);

    printf("How many ways are there to make change for a dollar\n");
    printf("using these common coins? (1 dollar = 100 cents)\n");
    printf("Result: %d\n", result);

    printf("End app %s\n", app_name);

    return 0;
}
