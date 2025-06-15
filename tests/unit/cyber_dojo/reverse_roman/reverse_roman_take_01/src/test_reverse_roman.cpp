#include <gtest/gtest.h>
#include <cstring>

extern "C" {
#include "../../../../projects/cyber_dojo/reverse_roman/reverse_roman_take_01/src/reverse_roman.h"
}

using namespace ::testing;

class ReverseRomanTest : public Test {
protected:
    void SetUp() override {
        // No setup code needed
    }
};

// Test FromRoman conversion
TEST_F(ReverseRomanTest, FromRoman) {
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
