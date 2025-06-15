#include "game_of_life.h"
#include <stdlib.h>
#include <string.h>

// Create a new game with an empty grid
GameOfLife* game_of_life_new(const int rows_n, const int cols_n) {
    // Allocate game structure
    GameOfLife* game = (GameOfLife*)malloc(sizeof(GameOfLife));
    if (!game) return NULL;

    // Initialize game properties
    game->rows_n = rows_n;
    game->cols_n = cols_n;
    game->is_initial_generation = true;

    // Set default cell representations
    game->cell_alive = strdup(CELL_ALIVE_DEFAULT);
    game->cell_empty = strdup(CELL_EMPTY_DEFAULT);
    game->separator = strdup(SEPARATOR_DEFAULT);

    // Allocate the grid
    game->grid = (int**)malloc(rows_n * sizeof(int*));
    if (!game->grid) {
        free(game->cell_alive);
        free(game->cell_empty);
        free(game->separator);
        free(game);
        return NULL;
    }

    // Allocate initial pattern
    game->initial_pattern = (char**)malloc(rows_n * sizeof(char*));
    if (!game->initial_pattern) {
        free(game->grid);
        free(game->cell_alive);
        free(game->cell_empty);
        free(game->separator);
        free(game);
        return NULL;
    }

    // Initialize grid and pattern
    for (int i = 0; i < rows_n; ++i) {
        // Allocate row for grid
        game->grid[i] = (int*)calloc(cols_n, sizeof(int));
        if (!game->grid[i]) {
            for (int j = 0; j < i; ++j) {
                free(game->grid[j]);
                free(game->initial_pattern[j]);
            }
            free(game->grid);
            free(game->initial_pattern);
            free(game->cell_alive);
            free(game->cell_empty);
            free(game->separator);
            free(game);
            return NULL;
        }

        // Create empty pattern string
        game->initial_pattern[i] = (char*)malloc((cols_n + 1) * sizeof(char));
        if (!game->initial_pattern[i]) {
            for (int j = 0; j < i; ++j) {
                free(game->grid[j]);
                free(game->initial_pattern[j]);
            }
            free(game->grid[i]);
            free(game->grid);
            free(game->initial_pattern);
            free(game->cell_alive);
            free(game->cell_empty);
            free(game->separator);
            free(game);
            return NULL;
        }

        // Fill with empty cells
        for (int j = 0; j < cols_n; ++j) {
            game->initial_pattern[i][j] = CELL_EMPTY_DEFAULT[0];
        }
        game->initial_pattern[i][cols_n] = '\0';
    }

    return game;
}

// Create a new game from a string grid representation
GameOfLife* game_of_life_new_from_grid(
    const int height, const int width, const char** grid_str
) {
    // Create a new game
    GameOfLife* game = game_of_life_new(height, width);
    if (!game) return NULL;

    // Copy the initial pattern
    for (int i = 0; i < height; ++i) {
        strncpy(game->initial_pattern[i], grid_str[i], width);
        game->initial_pattern[i][width] = '\0';

        // Set grid based on pattern
        for (int j = 0; j < width && grid_str[i][j] != '\0'; ++j) {
            if (grid_str[i][j] == CELL_ALIVE_DEFAULT[0]) {
                game->grid[i][j] = 1;
            }
        }
    }

    return game;
}

// Set custom cell representation
int game_of_life_set_cell_representation(
    GameOfLife* game, const char* alive, const char* empty, const char* separator
) {
    if (!game->is_initial_generation) {
        // Error: cell representation can only be set in the initial generation
        return -1;
    }

    if (strlen(alive) > 1 || strlen(empty) > 1) {
        // Error: cell representation must be a single character
        return -1;
    }

    // Free previous representations
    free(game->cell_alive);
    free(game->cell_empty);
    free(game->separator);

    // Set new representations
    game->cell_alive = strdup(alive);
    game->cell_empty = strdup(empty);
    game->separator = strdup(separator);

    // Recreate grid using custom cell representation
    for (int i = 0; i < game->rows_n; ++i) {
        for (int j = 0; j < game->cols_n; ++j) {
            if (game->initial_pattern[i][j] == alive[0]) {
                game->grid[i][j] = 1;
            }
            else {
                game->grid[i][j] = 0;
            }
        }
    }

    return 0; // Success
}

// Set the state of a cell
void game_of_life_set_cell(
    const GameOfLife* game, const int x, const int y, const int state
) {
    if (x >= 0 && x < game->cols_n && y >= 0 && y < game->rows_n) {
        game->grid[y][x] = state;
    }
}

// Get the state of a cell
int game_of_life_get_cell(const GameOfLife* game, const int x, const int y) {
    if (x >= 0 && x < game->cols_n && y >= 0 && y < game->rows_n) {
        return game->grid[y][x];
    }
    // Out of bounds cells are considered dead
    return 0;
}

// Count the number of live neighbors for a cell
int game_of_life_count_neighbors(const GameOfLife* game, const int x, const int y) {
    int count = 0;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue; // Skip the cell itself

            int nx = x + j;
            int ny = y + i;

            if (nx >= 0 && nx < game->cols_n && ny >= 0 && ny < game->rows_n) {
                count += game->grid[ny][nx];
            }
        }
    }

    return count;
}

// Calculate the next generation
void game_of_life_calc_next_generation(GameOfLife* game) {
    // Create a new grid for the next generation
    int** new_grid = (int**)malloc(game->rows_n * sizeof(int*));
    for (int i = 0; i < game->rows_n; ++i) {
        new_grid[i] = (int*)calloc(game->cols_n, sizeof(int));
    }

    // Apply Game of Life rules
    for (int y = 0; y < game->rows_n; ++y) {
        for (int x = 0; x < game->cols_n; ++x) {
            int neighbors = game_of_life_count_neighbors(game, x, y);

            if (game->grid[y][x] == 1) {
                // Cell is alive
                if (neighbors < 2 || neighbors > 3) {
                    // Cell dies by isolation or by overpopulation
                    new_grid[y][x] = 0;
                }
                else {
                    // Cell survives
                    new_grid[y][x] = 1;
                }
            }
            else {
                // Cell is dead
                if (neighbors == 3) {
                    // Cell becomes alive
                    new_grid[y][x] = 1;
                }
                else {
                    // Cell stays dead
                    new_grid[y][x] = 0;
                }
            }
        }
    }

    // Free the old grid and replace with the new one
    for (int i = 0; i < game->rows_n; ++i) {
        free(game->grid[i]);
    }
    free(game->grid);
    game->grid = new_grid;

    // Mark that we're no longer in the initial generation
    game->is_initial_generation = false;
}

// Generate a string representation of the current grid state
char* game_of_life_to_string(const GameOfLife* game) {
    // Calculate the required buffer size
    int sep_len = strlen(game->separator);
    int cell_size = 1 + sep_len; // Each cell is one character plus the separator
    int row_size = game->cols_n * cell_size + 1; // +1 for newline
    int total_size = game->rows_n * row_size + 1; // +1 for null terminator

    // Allocate the buffer
    char* result = (char*)malloc(total_size * sizeof(char));
    if (!result) return NULL;

    // Fill the buffer
    int pos = 0;
    for (int y = 0; y < game->rows_n; ++y) {
        for (int x = 0; x < game->cols_n; ++x) {
            if (game->grid[y][x] == 1) {
                strcpy(result + pos, game->cell_alive);
                pos += strlen(game->cell_alive);
            }
            else {
                strcpy(result + pos, game->cell_empty);
                pos += strlen(game->cell_empty);
            }

            strcpy(result + pos, game->separator);
            pos += sep_len;
        }
        result[pos++] = '\n';
    }
    result[pos] = '\0';

    return result;
}

// Free all resources allocated for the game
void game_of_life_free(GameOfLife* game) {
    if (!game) return;

    // Free the grid
    for (int i = 0; i < game->rows_n; ++i) {
        free(game->grid[i]);
    }
    free(game->grid);

    // Free the initial pattern
    for (int i = 0; i < game->rows_n; ++i) {
        free(game->initial_pattern[i]);
    }
    free(game->initial_pattern);

    // Free string representations
    free(game->cell_alive);
    free(game->cell_empty);
    free(game->separator);

    // Free the game structure itself
    free(game);
}
