#include <gtest/gtest.h>

extern "C" {
#include "../../../../projects/cyber_dojo/mine_field/mine_field_take_01/src/mine_field.h"
}

class MineFieldTest : public ::testing::Test {
protected:
    void SetUp() override {
        // No setup needed
    }

    void TearDown() override {
        // No teardown needed
    }
};

TEST_F(MineFieldTest, TestResolve1) {
    const char* board = "3 4\n"
        "*...\n"
        "..*. \n"
        "....";
    const char* expected = ""
        "*211\n"
        "12*1\n"
        "0111";

    MineField* mf = mine_field_new(board);
    ASSERT_NE(mf, nullptr) << "Failed to create mine field";

    char* result = mine_field_resolve(mf);
    ASSERT_NE(result, nullptr) << "Failed to resolve mine field";

    EXPECT_STREQ(result, expected);

    // Cleanup
    free(result);
    mine_field_free(mf);
}

TEST_F(MineFieldTest, TestResolve2) {
    const char* board = "5 4\n"
        "*...\n"
        "..*. \n"
        "...*\n"
        "....\n"
        ".*.. ";
    const char* expected = ""
        "*211\n"
        "12*2\n"
        "012*\n"
        "1121\n"
        "1*10";

    MineField* mf = mine_field_new(board);
    ASSERT_NE(mf, nullptr) << "Failed to create mine field";

    char* result = mine_field_resolve(mf);
    ASSERT_NE(result, nullptr) << "Failed to resolve mine field";

    EXPECT_STREQ(result, expected);

    // Cleanup
    free(result);
    mine_field_free(mf);
}

TEST_F(MineFieldTest, TestInvalidInput) {
    const char* invalidBoard = "invalid";

    MineField* mf = mine_field_new(invalidBoard);
    EXPECT_EQ(mf, nullptr) << "Should return NULL for invalid input";
}

TEST_F(MineFieldTest, TestNullInput) {
    MineField* mf = mine_field_new(nullptr);
    EXPECT_EQ(mf, nullptr) << "Should return NULL for null input";
}

TEST_F(MineFieldTest, TestFreeNull) {
    mine_field_free(nullptr);
    SUCCEED();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
