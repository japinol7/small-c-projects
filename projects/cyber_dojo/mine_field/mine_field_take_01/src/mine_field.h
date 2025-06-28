#ifndef MINE_FIELD_H
#define MINE_FIELD_H

// MineField structure representing a field with mines
typedef struct {
    int nRows;
    int nColumns;
    char **board;
} MineField;

// Create a new mine field from a board string
// Format: "nRows nColumns\n<board rows>"
// Returns NULL if allocation fails
MineField* mine_field_new(const char *board);

// Free resources used by a mine field
void mine_field_free(MineField *mineField);

// Calculate the hint field based on the minefield
// Returns a newly allocated string that must be freed by the caller
// Returns NULL if allocation fails
char* mine_field_resolve(const MineField *mineField);

#endif // MINE_FIELD_H
