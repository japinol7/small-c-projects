#include "print_diamond.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* appName = "Print Diamond";
    printf("Start app %s\n", appName);

    // Examples of diamond patterns
    const char* letters[] = {"A", "B", "C", "D", "E"};
    const int numLetters = 5;

    for (int i = 0; i < numLetters; ++i) {
        printf("\nDiamond for letter %s:\n", letters[i]);
        Diamond* diamond = newDiamond(letters[i]);

        char* diamondStr = diamondToString(diamond);
        printf("%s\n", diamondStr);

        free(diamondStr);
        freeDiamond(diamond);
    }

    printf("\nEnd app %s\n", appName);
    return 0;
}
