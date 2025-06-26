#include <gtest/gtest.h>
#include <cstring>

extern "C" {
#include "../../../../projects/cyber_dojo/print_diamond/print_diamond_take_01/src/print_diamond.h"
}

using namespace ::testing;

class PrintDiamondTest : public Test {
protected:
    void SetUp() override {
        // No setup needed
    }
};

// Test cases for empty or invalid input
class PrintDiamondEmptyInvalidTest : public TestWithParam<std::tuple<
    const char*, const char*>>
{
protected:
    void SetUp() override {
        // No setup needed
    }
};

TEST_P(PrintDiamondEmptyInvalidTest, EmptyOrInvalidInput) {
    auto [input, expected] = GetParam();

    // Create diamond
    Diamond* diamond = newDiamond(input);
    ASSERT_NE(diamond, nullptr);

    // Convert to string
    char* result = diamondToString(diamond);
    ASSERT_NE(result, nullptr);

    // Check the result
    EXPECT_STREQ(result, expected)
        << "For input: '" << input << "'";

    // Clean up
    free(result);
    freeDiamond(diamond);
}

INSTANTIATE_TEST_SUITE_P(PrintDiamondEmptyInvalid, PrintDiamondEmptyInvalidTest,
    Values(
        std::make_tuple("", ""),
        std::make_tuple(" ", ""),
        std::make_tuple("ñ", ""),
        std::make_tuple("FG", "")
    )
);

// Test case for letter A
TEST_F(PrintDiamondTest, LetterA) {
    const char* expected = "A";

    // Create diamond
    Diamond* diamond = newDiamond("A");
    ASSERT_NE(diamond, nullptr);

    // Convert to string
    char* result = diamondToString(diamond);
    ASSERT_NE(result, nullptr);

    // Check the result
    EXPECT_STREQ(result, expected);

    // Clean up
    free(result);
    freeDiamond(diamond);
}

// Test case for letter B
TEST_F(PrintDiamondTest, LetterB) {
    const char* expected = " A \n"
        "B B\n"
        " A ";

    // Create diamond
    Diamond* diamond = newDiamond("B");
    ASSERT_NE(diamond, nullptr);

    // Convert to string
    char* result = diamondToString(diamond);
    ASSERT_NE(result, nullptr);

    // Check the result
    EXPECT_STREQ(result, expected);

    // Clean up
    free(result);
    freeDiamond(diamond);
}

// Test case for letter C
TEST_F(PrintDiamondTest, LetterC) {
    const char* expected = "  A  \n"
        " B B \n"
        "C   C\n"
        " B B \n"
        "  A  ";

    // Create diamond
    Diamond* diamond = newDiamond("C");
    ASSERT_NE(diamond, nullptr);

    // Convert to string
    char* result = diamondToString(diamond);
    ASSERT_NE(result, nullptr);

    // Check the result
    EXPECT_STREQ(result, expected);

    // Clean up
    free(result);
    freeDiamond(diamond);
}

// Test case for letter D
TEST_F(PrintDiamondTest, LetterD) {
    const char* expected = "   A   \n"
        "  B B  \n"
        " C   C \n"
        "D     D\n"
        " C   C \n"
        "  B B  \n"
        "   A   ";

    // Create diamond
    Diamond* diamond = newDiamond("D");
    ASSERT_NE(diamond, nullptr);

    // Convert to string
    char* result = diamondToString(diamond);
    ASSERT_NE(result, nullptr);

    // Check the result
    EXPECT_STREQ(result, expected);

    // Clean up
    free(result);
    freeDiamond(diamond);
}

// Test case for letter F
TEST_F(PrintDiamondTest, LetterF) {
    const char* expected = "     A     \n"
        "    B B    \n"
        "   C   C   \n"
        "  D     D  \n"
        " E       E \n"
        "F         F\n"
        " E       E \n"
        "  D     D  \n"
        "   C   C   \n"
        "    B B    \n"
        "     A     ";

    // Create diamond
    Diamond* diamond = newDiamond("F");
    ASSERT_NE(diamond, nullptr);

    // Convert to string
    char* result = diamondToString(diamond);
    ASSERT_NE(result, nullptr);

    // Check the result
    EXPECT_STREQ(result, expected);

    // Clean up
    free(result);
    freeDiamond(diamond);
}

// Test case for letter E with output
TEST_F(PrintDiamondTest, LetterEWithOutput) {
    const char* expected = "    A    \n"
        "   B B   \n"
        "  C   C  \n"
        " D     D \n"
        "E       E\n"
        " D     D \n"
        "  C   C  \n"
        "   B B   \n"
        "    A    ";

    // Create diamond
    Diamond* diamond = newDiamond("E");
    ASSERT_NE(diamond, nullptr);

    // Convert to string
    char* result = diamondToString(diamond);
    ASSERT_NE(result, nullptr);

    // Check the result
    EXPECT_STREQ(result, expected);

    // Print output for visual inspection
    printf("\nOutput:\n%s\n", result);

    // Clean up
    free(result);
    freeDiamond(diamond);
}
