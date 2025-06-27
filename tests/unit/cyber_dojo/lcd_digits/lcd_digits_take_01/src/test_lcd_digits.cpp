#include <gtest/gtest.h>
#include <cstring>

extern "C" {
#include "../../../../projects/cyber_dojo/lcd_digits/lcd_digits_take_01/src/lcd_digits.h"
#include "../../../../projects/cyber_dojo/lcd_digits/lcd_digits_take_01/src/lcd_digit_cell.h"
}

// Chars used to display test LCD digits and the separator strings
constexpr char TEST_CELL_H = '_';
constexpr char TEST_CELL_V = '|';
constexpr char TEST_CELL_O = '.';
const char* TEST_SEPARATOR = " ";
const char* TEST_SEPARATOR_BIG = "     ";

// LCD digit representations
const char* DIGITS_REPR_0 = ""
    "._."
    "\n|.|"
    "\n|_|"
    "\n";

const char* DIGITS_REPR_1 = ""
    "..."
    "\n..|"
    "\n..|"
    "\n";

const char* DIGITS_REPR_2 = ""
    "._."
    "\n._|"
    "\n|_."
    "\n";

const char* DIGITS_REPR_3 = ""
    "._."
    "\n._|"
    "\n._|"
    "\n";

const char* DIGITS_REPR_4 = ""
    "..."
    "\n|_|"
    "\n..|"
    "\n";

const char* DIGITS_REPR_5 = ""
    "._."
    "\n|_."
    "\n._|"
    "\n";

const char* DIGITS_REPR_6 = ""
    "._."
    "\n|_."
    "\n|_|"
    "\n";

const char* DIGITS_REPR_7 = ""
    "._."
    "\n..|"
    "\n..|"
    "\n";

const char* DIGITS_REPR_8 = ""
    "._."
    "\n|_|"
    "\n|_|"
    "\n";

const char* DIGITS_REPR_9 = ""
    "._."
    "\n|_|"
    "\n..|"
    "\n";

const char* DIGITS_REPR_1234567890 = ""
    "... ._. ._. ... ._. ._. ._. ._. ._. ._."
    "\n..| ._| ._| |_| |_. |_. ..| |_| |_| |.|"
    "\n..| |_. ._| ..| ._| |_| ..| |_| ..| |_|"
    "\n";

const char* DIGITS_REPR_1234567890_SEPARATOR_BIG = ""
    "...     ._.     ._.     ...     ._.     ._.     ._.     ._.     ._.     ._."
    "\n..|     ._|     ._|     |_|     |_.     |_.     ..|     |_|     |_|     |.|"
    "\n..|     |_.     ._|     ..|     ._|     |_|     ..|     |_|     ..|     |_|"
    "\n";

const char* DIGITS_REPR_910 = ""
    "._. ... ._."
    "\n|_| ..| |.|"
    "\n..| ..| |_|"
    "\n";

class LcdDigitsTest : public testing::Test {
protected:
    LcdDigits lcd{};
    char result[4096]{};
    LcdDigitsError error{};

    void SetUp() override {
        lcd = lcd_digits_new();
        memset(result, 0, sizeof(result));
    }

    // Replace LCD cell chars with test chars
    static std::string replaceLCDDigitCells(const std::string& input) {
        std::string output = input;
        for (size_t i = 0; i < output.length(); ++i) {
            if (output[i] == CELL_H) output[i] = TEST_CELL_H;
            else if (output[i] == CELL_V) output[i] = TEST_CELL_V;
            else if (output[i] == CELL_O) output[i] = TEST_CELL_O;
        }
        return output;
    }

    // Replace separators with test separators
    static std::string replaceLCDDigitSeparators(
        const std::string& input,
        const std::string& separator,
        const std::string& testSeparator
    ) {
        std::string output = input;
        size_t pos = 0;
        while ((pos = output.find(separator, pos)) != std::string::npos) {
            output.replace(pos, separator.length(), testSeparator);
            pos += testSeparator.length();
        }
        return output;
    }
};

// Test single digits 0-9
TEST_F(LcdDigitsTest, SingleDigits) {
    struct TestCase {
        int input;
        const char* expected;
    };

    TestCase tests[] = {
        {0, DIGITS_REPR_0},
        {1, DIGITS_REPR_1},
        {2, DIGITS_REPR_2},
        {3, DIGITS_REPR_3},
        {4, DIGITS_REPR_4},
        {5, DIGITS_REPR_5},
        {6, DIGITS_REPR_6},
        {7, DIGITS_REPR_7},
        {8, DIGITS_REPR_8},
        {9, DIGITS_REPR_9}
    };

    for (const auto& [input, expected] : tests) {
        ASSERT_EQ(0, lcd_digits_generate(
                input, result, sizeof(result), &error, nullptr));

        std::string processed = replaceLCDDigitCells(result);
        processed = replaceLCDDigitSeparators(
            processed, SEPARATOR, TEST_SEPARATOR);

        EXPECT_STREQ(expected, processed.c_str());
    }
}

// Test multiple digits
TEST_F(LcdDigitsTest, AllDigits) {
    ASSERT_EQ(0, lcd_digits_generate(
            1234567890, result, sizeof(result), &error, nullptr));

    std::string processed = replaceLCDDigitCells(result);
    processed = replaceLCDDigitSeparators(
        processed, SEPARATOR, TEST_SEPARATOR);

    EXPECT_STREQ(DIGITS_REPR_1234567890, processed.c_str());
}

// Test 910 specifically
TEST_F(LcdDigitsTest, Digits910) {
    ASSERT_EQ(0, lcd_digits_generate(
            910, result, sizeof(result), &error, nullptr));

    std::string processed = replaceLCDDigitCells(result);
    processed = replaceLCDDigitSeparators(
        processed, SEPARATOR, TEST_SEPARATOR);

    EXPECT_STREQ(DIGITS_REPR_910, processed.c_str());
}

// Test custom separator
TEST_F(LcdDigitsTest, CustomSeparator) {
    const char* separator = "    ";

    ASSERT_EQ(0, lcd_digits_generate(
            1234567890, result, sizeof(result), &error, separator));

    std::string processed = replaceLCDDigitCells(result);
    processed = replaceLCDDigitSeparators(
        processed, separator, TEST_SEPARATOR_BIG);

    EXPECT_STREQ(DIGITS_REPR_1234567890_SEPARATOR_BIG, processed.c_str());
}

// Test negative number error
TEST_F(LcdDigitsTest, NegativeNumberError) {
    EXPECT_EQ(-1, lcd_digits_generate(
            -1, result, sizeof(result), &error, nullptr));
    EXPECT_STREQ("Number must be non-negative", error.message);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
