#include "mine_field.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static const char EMPTY = '.';
static const char MINE = '*';

static int min(const int a, const int b) {
    return a < b ? a : b;
}

static int max(const int a, int b) {
    return a > b ? a : b;
}

// Create a new mine field from a board string
MineField* mine_field_new(const char *board) {
    if (!board) return NULL;

    MineField *mineField = (MineField*)malloc(sizeof(MineField));
    if (!mineField) return NULL;

    // Parse dimensions from the first line
    if (sscanf(board, "%d %d", &mineField->nRows, &mineField->nColumns) != 2) {
        free(mineField);
        return NULL;
    }

    // Allocate memory for the board
    mineField->board = (char**)malloc(mineField->nRows * sizeof(char*));
    if (!mineField->board) {
        free(mineField);
        return NULL;
    }

    // Find the first newline character to skip the dimensions line
    const char *boardStart = strchr(board, '\n');
    if (!boardStart) {
        free(mineField->board);
        free(mineField);
        return NULL;
    }
    boardStart++; // Skip the newline character

    // Parse the board
    for (int i = 0; i < mineField->nRows; i++) {
        mineField->board[i] = (char*)malloc((mineField->nColumns + 1) * sizeof(char));
        if (!mineField->board[i]) {
            // Free previously allocated memory on failure
            for (int j = 0; j < i; j++) {
                free(mineField->board[j]);
            }
            free(mineField->board);
            free(mineField);
            return NULL;
        }

        // Copy row data from input
        for (int j = 0; j < mineField->nColumns; j++) {
            if (boardStart[j] == '\0' || boardStart[j] == '\n') break;
            mineField->board[i][j] = boardStart[j];
        }
        mineField->board[i][mineField->nColumns] = '\0';

        // Move to the next line
        boardStart = strchr(boardStart, '\n');
        if (boardStart) boardStart++; // Skip the newline
        else if (i < mineField->nRows - 1) {
            // If we run out of lines but expected more
            for (int j = 0; j <= i; j++) {
                free(mineField->board[j]);
            }
            free(mineField->board);
            free(mineField);
            return NULL;
        }
    }

    return mineField;
}

// Free resources used by a mine field
void mine_field_free(MineField *mineField) {
    if (!mineField) return;

    if (mineField->board) {
        for (int i = 0; i < mineField->nRows; i++) {
            free(mineField->board[i]);
        }
        free(mineField->board);
    }

    free(mineField);
}

// Count the number of mine neighbors for a given cell
static int count_neighbours(
    const MineField *mineField, const int nRow, const int nColumn
) {
    int count = 0;

    for (int x = max(nColumn - 1, 0); x < min(nColumn + 2, mineField->nColumns); x++) {
        for (int y = max(nRow - 1, 0); y < min(nRow + 2, mineField->nRows); y++) {
            // Skip the cell itself and count only if it's a mine
            if ((x != nColumn || y != nRow) && mineField->board[y][x] == MINE) {
                count++;
            }
        }
    }

    return count;
}

// Calculate the hint field based on the minefield
char* mine_field_resolve(const MineField *mineField) {
    if (!mineField) return NULL;

    // Create a result array for the hint field
    char **result = (char**)malloc(mineField->nRows * sizeof(char*));
    if (!result) return NULL;

    for (int i = 0; i < mineField->nRows; i++) {
        result[i] = (char*)malloc((mineField->nColumns + 1) * sizeof(char));
        if (!result[i]) {
            // Free previously allocated memory on failure
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
    }

    // Calculate the hint field
    for (int nRow = 0; nRow < mineField->nRows; nRow++) {
        for (int nColumn = 0; nColumn < mineField->nColumns; nColumn++) {
            if (mineField->board[nRow][nColumn] == MINE) {
                result[nRow][nColumn] = MINE;
            } else {
                result[nRow][nColumn] = '0' + count_neighbours(mineField, nRow, nColumn);
            }
        }
        result[nRow][mineField->nColumns] = '\0';
    }

    // Join the result into a string
    const int resultSize = mineField->nRows
              * (mineField->nColumns + 1); // +1 for newlines
    char *resultStr = (char*)malloc(resultSize + 1); // +1 for null terminator
    if (!resultStr) {
        for (int i = 0; i < mineField->nRows; i++) {
            free(result[i]);
        }
        free(result);
        return NULL;
    }

    resultStr[0] = '\0';
    for (int i = 0; i < mineField->nRows; i++) {
        strcat(resultStr, result[i]);
        if (i < mineField->nRows - 1) {
            strcat(resultStr, "\n");
        }

        free(result[i]);
    }
    free(result);

    return resultStr;
}
