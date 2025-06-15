#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <stdbool.h>

// Default cell representation characters
#define CELL_ALIVE_DEFAULT "*"
#define CELL_EMPTY_DEFAULT "."
#define SEPARATOR_DEFAULT ""

// GameOfLife structure to represent the game state
typedef struct {
    int rows_n;
    int cols_n;
    int** grid;
    char** initial_pattern;
    bool is_initial_generation;
    char* cell_alive;
    char* cell_empty;
    char* separator;
} GameOfLife;

// Create a new game with empty grid
GameOfLife* game_of_life_new(int rows_n, int cols_n);

// Create a new game from a string grid representation
GameOfLife* game_of_life_new_from_grid(int height, int width, const char** grid_str);

// Set custom cell representation
int game_of_life_set_cell_representation(GameOfLife* game, const char* alive, const char* empty, const char* separator);

// Set the state of a cell
void game_of_life_set_cell(const GameOfLife* game, int x, int y, int state);

// Get the state of a cell
int game_of_life_get_cell(const GameOfLife* game, int x, int y);

// Count the number of live neighbors for a cell
int game_of_life_count_neighbors(const GameOfLife* game, int x, int y);

// Calculate the next generation
void game_of_life_calc_next_generation(GameOfLife* game);

// Generate a string representation of the current grid state
char* game_of_life_to_string(const GameOfLife* game);

// Free all resources allocated for the game
void game_of_life_free(GameOfLife* game);

#endif // GAME_OF_LIFE_H
