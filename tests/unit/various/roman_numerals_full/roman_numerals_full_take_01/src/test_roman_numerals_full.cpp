#include <gtest/gtest.h>
#include <cstring>

extern "C" {
#include "../../../../projects/various/roman_numerals_full/roman_numerals_full_take_01/src/roman_numerals_full.h"
}

using namespace ::testing;

class RomanNumeralsFullTest : public Test {
protected:
    // Buffer for Roman numeral strings
    char roman_buffer[20]{};

    void SetUp() override {
        // Initialize buffer before each test
        memset(roman_buffer, 0, sizeof(roman_buffer));
    }
};

// Test ToRoman conversion
TEST_F(RomanNumeralsFullTest, ToRoman) {
    struct TestCase {
        int num;
        const char* expected;
        bool has_error;
    };

    TestCase test_cases[] = {
        {1, "I", false},
        {2, "II", false},
        {3, "III", false},
        {4, "IV", false},
        {5, "V", false},
        {9, "IX", false},
        {10, "X", false},
        {40, "XL", false},
        {50, "L", false},
        {73, "LXXIII", false},
        {90, "XC", false},
        {93, "XCIII", false},
        {100, "C", false},
        {400, "CD", false},
        {500, "D", false},
        {900, "CM", false},
        {1000, "M", false},
        {1984, "MCMLXXXIV", false},
        {2023, "MMXXIII", false},
        {3999, "MMMCMXCIX", false},
        {0, "", true}, // Error case
        {4000, "", true}, // Error case
        {-1, "", true} // Error case
    };

    for (const auto& [num, expected, has_error] : test_cases) {
        int result = to_roman(num, roman_buffer, sizeof(roman_buffer));

        if (has_error) {
            EXPECT_EQ(-1, result) << "to_roman(" << num << ") should return error";
        }
        else {
            EXPECT_EQ(0, result) << "to_roman(" << num << ") should succeed";
            EXPECT_STREQ(expected, roman_buffer)
                << "to_roman(" << num << ") = " << roman_buffer
                << ", expected " << expected;
        }

        // Reset buffer for next test
        memset(roman_buffer, 0, sizeof(roman_buffer));
    }
}

// Test FromRoman conversion
TEST_F(RomanNumeralsFullTest, FromRoman) {
    struct TestCase {
        const char* roman;
        int expected;
        bool has_error;
    };

    TestCase test_cases[] = {
        {"I", 1, false},
        {"II", 2, false},
        {"III", 3, false},
        {"IV", 4, false},
        {"V", 5, false},
        {"IX", 9, false},
        {"X", 10, false},
        {"XL", 40, false},
        {"L", 50, false},
        {"LXXIII", 73, false},
        {"XC", 90, false},
        {"XCIII", 93, false},
        {"C", 100, false},
        {"CD", 400, false},
        {"D", 500, false},
        {"CM", 900, false},
        {"M", 1000, false},
        {"MCMLXXXIV", 1984, false},
        {"MMXXIII", 2023, false},
        {"MMMCMXCIX", 3999, false},
        {"", 0, true}, // Error case
        {"MMMM", 0, true}, // Error case (4000)
        {"ABC", 0, true}, // Error case (invalid chars)
        {"MMMCMXCIY", 0, true} // Error case (invalid char Y)
    };

    for (const auto& [roman, expected, has_error] : test_cases) {
        int num = 0;
        int result = from_roman(roman, &num);

        if (has_error) {
            EXPECT_EQ(-1, result) << "from_roman(" << roman << ") should return error";
        }
        else {
            EXPECT_EQ(0, result) << "from_roman(" << roman << ") should succeed";
            EXPECT_EQ(expected, num)
                << "from_roman(" << roman << ") = " << num
                << ", expected " << expected;
        }
    }
}

// Test round-trip conversion
TEST_F(RomanNumeralsFullTest, RoundTrip) {
    // Test every 100 numbers to keep test runtime reasonable
    for (int i = 1; i <= 3999; i += 100) {
        int result_num = 0;

        // Convert int to Roman
        int result1 = to_roman(i, roman_buffer, sizeof(roman_buffer));
        ASSERT_EQ(0, result1) << "to_roman(" << i << ") failed";

        // Convert Roman back to int
        int result2 = from_roman(roman_buffer, &result_num);
        ASSERT_EQ(0, result2) << "from_roman(" << roman_buffer << ") failed";

        // Verify the round trip conversion
        EXPECT_EQ(i, result_num)
                << "Round trip failed: " << i << " -> "
                << roman_buffer << " -> " << result_num;

        // Reset buffer for next test
        memset(roman_buffer, 0, sizeof(roman_buffer));
    }
}
