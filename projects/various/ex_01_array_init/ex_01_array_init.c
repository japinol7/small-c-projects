// Requires c99 or c17
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    const double items[3] = {
        [0] = 1.5,
        [1] = .02,
        [2] = 5.E+18,
    };
    const unsigned int items_len = 3;

    // Calculate items squares
    for (size_t i = 0; i < items_len; ++i) {
        printf("element %zu is %g, \t"
               "its square is %g\n",
               i,
               items[i],
               items[i] * items[i]
        );
    }
    return EXIT_SUCCESS;
}
