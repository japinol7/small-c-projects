#include <gtest/gtest.h>

extern "C" {
#include "../../../../projects/cyber_dojo/game_of_life/game_of_life_take_01/src/game_of_life.h"
}

using namespace ::testing;

class GameOfLifeTest : public Test {
protected:
    char buffer[100]{};

    void SetUp() override {
        memset(buffer, 0, sizeof(buffer));
    }
};


// Test initialization of game
TEST_F(GameOfLifeTest, Init) {
    GameOfLife* game = game_of_life_new(5, 5);

    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x < 5; ++x) {
            EXPECT_EQ(0, game_of_life_get_cell(game, x, y))
                << "Expected cell (" << x << "," << y << ") to be 0";
        }
    }

    game_of_life_free(game);
}

// Test setting and getting cell state
TEST_F(GameOfLifeTest, SetAndGetCell) {
    GameOfLife* game = game_of_life_new(5, 5);

    game_of_life_set_cell(game, 1, 2, 1);
    EXPECT_EQ(1, game_of_life_get_cell(game, 1, 2))
        << "Expected cell (1,2) to be 1";

    game_of_life_free(game);
}

// Test counting neighbors
TEST_F(GameOfLifeTest, CountNeighbors) {
    GameOfLife* game = game_of_life_new(5, 5);

    game_of_life_set_cell(game, 1, 1, 1);
    game_of_life_set_cell(game, 2, 1, 1);
    game_of_life_set_cell(game, 1, 2, 1);

    int neighbors1 = game_of_life_count_neighbors(game, 1, 1);
    EXPECT_EQ(2, neighbors1)
        << "Expected cell (1,1) to have 2 neighbors, got " << neighbors1;

    int neighbors2 = game_of_life_count_neighbors(game, 2, 2);
    EXPECT_EQ(3, neighbors2)
        << "Expected cell (2,2) to have 3 neighbors, got " << neighbors2;

    game_of_life_free(game);
}

// Test cell dying from underpopulation
TEST_F(GameOfLifeTest, StepUnderpopulation) {
    GameOfLife* game = game_of_life_new(5, 5);

    game_of_life_set_cell(game, 1, 1, 1);

    game_of_life_calc_next_generation(game);
    game_of_life_set_cell_representation(game, "*", ".", "");

    EXPECT_EQ(0, game_of_life_get_cell(game, 1, 1))
        << "Expected cell (1,1) to die from underpopulation";

    game_of_life_free(game);
}

// Test cell dying from overpopulation
TEST_F(GameOfLifeTest, StepOverpopulation) {
    GameOfLife* game = game_of_life_new(5, 5);

    game_of_life_set_cell(game, 1, 1, 1);
    game_of_life_set_cell(game, 0, 0, 1);
    game_of_life_set_cell(game, 0, 1, 1);
    game_of_life_set_cell(game, 0, 2, 1);
    game_of_life_set_cell(game, 1, 0, 1);

    game_of_life_calc_next_generation(game);
    game_of_life_set_cell_representation(game, "*", ".", "");

    EXPECT_EQ(0, game_of_life_get_cell(game, 1, 1))
        << "Expected cell (1,1) to die from overpopulation";

    game_of_life_free(game);
}

// Test cell reproduction
TEST_F(GameOfLifeTest, StepReproduction) {
    const char* input[] = {
        "**...",
        "*....",
        ".....",
        ".....",
        "....."
    };

    GameOfLife* game = game_of_life_new_from_grid(5, 5, input);
    game_of_life_set_cell_representation(game, "*", ".", "");

    game_of_life_calc_next_generation(game);

    EXPECT_EQ(1, game_of_life_get_cell(game, 1, 1))
        << "Expected cell (1,1) to become alive from reproduction";

    game_of_life_free(game);
}

// Test next generation calculation from grid pattern 1
TEST_F(GameOfLifeTest, NextGenerationFromGrid1) {
    const char* input[] = {
        "........",
        "....*...",
        "...**...",
        ".....*.."
    };

    const char* expected[] = {
        "........",
        "...**...",
        "...***..",
        "....*..."
    };

    GameOfLife* game = game_of_life_new_from_grid(4, 8, input);
    game_of_life_set_cell_representation(game, "*", ".", "");

    game_of_life_calc_next_generation(game);

    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 8; ++x) {
            int expected_state = (expected[y][x] == '*') ? 1 : 0;
            EXPECT_EQ(expected_state, game_of_life_get_cell(game, x, y))
                << "At position (" << x << "," << y << "): expected " << expected_state
                << ", got " << game_of_life_get_cell(game, x, y);
        }
    }

    game_of_life_free(game);
}

// Test next generation calculation from grid pattern 2
TEST_F(GameOfLifeTest, NextGenerationFromGrid2) {
    const char* input[] = {
        "........",
        "...**...",
        ".*****..",
        "........",
        "........"
    };

    const char* expected[] = {
        "........",
        ".....*..",
        "..*..*..",
        "..***...",
        "........"
    };

    GameOfLife* game = game_of_life_new_from_grid(5, 8, input);
    game_of_life_set_cell_representation(game, "*", ".", "");

    game_of_life_calc_next_generation(game);

    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 8; ++x) {
            int expected_state = (y < strlen(expected[y]) && expected[y][x] == '*') ? 1 : 0;
            EXPECT_EQ(expected_state, game_of_life_get_cell(game, x, y))
                << "At position (" << x << "," << y << "): expected " << expected_state
                << ", got " << game_of_life_get_cell(game, x, y);
        }
    }

    game_of_life_free(game);
}

// Test with custom cell representation
TEST_F(GameOfLifeTest, NextGenerationFromGridCustomCellRepr) {
    const char* input[] = {
        "--------",
        "---@@---",
        "-@@@@@--",
        "--------",
        "--------"
    };

    const char* expected[] = {
        "--------",
        "-----@--",
        "--@--@--",
        "--@@@---",
        "--------"
    };

    GameOfLife* game = game_of_life_new_from_grid(5, 8, input);
    game_of_life_set_cell_representation(game, "@", "-", " ");

    game_of_life_calc_next_generation(game);

    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 8; ++x) {
            int expected_state = (y < strlen(expected[y]) && expected[y][x] == '@') ? 1 : 0;
            EXPECT_EQ(expected_state, game_of_life_get_cell(game, x, y))
                << "At position (" << x << "," << y << "): expected " << expected_state
                << ", got " << game_of_life_get_cell(game, x, y);
        }
    }

    game_of_life_free(game);
}

// Test overpopulation with custom cell representation
TEST_F(GameOfLifeTest, StepOverpopulationCustomCellRepr) {
    GameOfLife* game = game_of_life_new(5, 5);

    game_of_life_set_cell(game, 1, 1, 1);
    game_of_life_set_cell(game, 0, 0, 1);
    game_of_life_set_cell(game, 0, 1, 1);
    game_of_life_set_cell(game, 0, 2, 1);
    game_of_life_set_cell(game, 1, 0, 1);

    game_of_life_calc_next_generation(game);
    game_of_life_set_cell_representation(game, "@", "-", " ");

    EXPECT_EQ(0, game_of_life_get_cell(game, 1, 1))
        << "Expected cell (1,1) to die from overpopulation";

    game_of_life_free(game);
}
