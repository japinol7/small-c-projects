#include "game_of_life.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* app_name = "Game of Life";
    printf("Start app %s\n", app_name);

    const char* grid_pattern[] = {
        "........",
        "....*...",
        "...**...",
        ".....*.."
    };

    // Create game from pattern
    GameOfLife* game = game_of_life_new_from_grid(4, 8, grid_pattern);
    if (!game) {
        printf("Error: Failed to create game\n");
        printf("End app %s\n", app_name);
        return 1;
    }

    // Set cell representation
    const int result = game_of_life_set_cell_representation(
        game, "*", ".", "");
    if (result != 0) {
        printf("Error: Failed to set cell representation\n");
        game_of_life_free(game);
        printf("End app %s\n", app_name);
        return 1;
    }

    // Run several generations
    const int generations_to_run = 4;
    for (int i = 0; i < generations_to_run; ++i) {
        printf("\nGeneration %d\n", i + 1);

        // Get and print the current state
        char* state = game_of_life_to_string(game);
        if (state) {
            printf("%s", state);
            free(state);
        }

        // Calculate next generation
        game_of_life_calc_next_generation(game);
    }

    // Free resources
    game_of_life_free(game);

    printf("End app %s\n", app_name);
    return 0;
}
