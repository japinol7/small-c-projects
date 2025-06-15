#include <gtest/gtest.h>
#include <cstring>

extern "C" {
#include "../../../../projects/cyber_dojo/roman_numerals/roman_numerals_take_01/src/roman_numerals.h"
}

using namespace ::testing;

class RomanNumeralsTest : public Test {
protected:
    // Buffer for Roman numeral strings
    char roman_buffer[20]{};

    void SetUp() override {
        // Initialize buffer before each test
        memset(roman_buffer, 0, sizeof(roman_buffer));
    }
};

// Test ToRoman conversion
TEST_F(RomanNumeralsTest, ToRoman) {
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
