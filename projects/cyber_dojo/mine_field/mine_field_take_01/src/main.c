#include "mine_field.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* app_name = "Mine Field";
    printf("Start app %s\n", app_name);

    // Example usage
    const char* board = "3 4\n"
        "*...\n"
        "..*. \n"
        "....";

    MineField *mf = mine_field_new(board);
    if (!mf) {
        printf("Error: Failed to create mine field\n");
        printf("End app %s\n", app_name);
        return 1;
    }

    char *result = mine_field_resolve(mf);
    if (!result) {
        printf("Error: Failed to resolve mine field\n");
        mine_field_free(mf);
        printf("End app %s\n", app_name);
        return 1;
    }

    printf("Input:\n%s\n\nOutput:\n%s\n", board, result);

    // Free resources
    free(result);
    mine_field_free(mf);

    printf("End app %s\n", app_name);
    return 0;
}
