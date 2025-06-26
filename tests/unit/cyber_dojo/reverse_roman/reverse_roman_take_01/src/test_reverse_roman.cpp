#include <gtest/gtest.h>
#include <cstring>

extern "C" {
#include "../../../../projects/cyber_dojo/reverse_roman/reverse_roman_take_01/src/reverse_roman.h"
}

using namespace ::testing;

class ReverseRomanTest : public TestWithParam<std::tuple<const char*, int, bool>> {
protected:
    void SetUp() override {
        // No setup needed
    }
};

TEST_P(ReverseRomanTest, FromRoman) {
    const auto& [roman, expected, has_error] = GetParam();
    
    int num = 0;
    const int result = from_roman(roman, &num);

    if (has_error) {
        EXPECT_EQ(-1, result)
            << "from_roman(" << roman << ") should return error";
    }
    else {
        EXPECT_EQ(0, result) << "from_roman(" << roman << ") should succeed";
        EXPECT_EQ(expected, num)
            << "from_roman(" << roman << ") = " << num
            << ", expected " << expected;
    }
}

INSTANTIATE_TEST_SUITE_P(
    ReverseRomanTests,
    ReverseRomanTest,
    Values(
        std::make_tuple("I", 1, false),
        std::make_tuple("II", 2, false),
        std::make_tuple("III", 3, false),
        std::make_tuple("IV", 4, false),
        std::make_tuple("V", 5, false),
        std::make_tuple("IX", 9, false),
        std::make_tuple("X", 10, false),
        std::make_tuple("XL", 40, false),
        std::make_tuple("L", 50, false),
        std::make_tuple("LXXIII", 73, false),
        std::make_tuple("XC", 90, false),
        std::make_tuple("XCIII", 93, false),
        std::make_tuple("C", 100, false),
        std::make_tuple("CD", 400, false),
        std::make_tuple("D", 500, false),
        std::make_tuple("CM", 900, false),
        std::make_tuple("M", 1000, false),
        std::make_tuple("MCMLXXXIV", 1984, false),
        std::make_tuple("MMXXIII", 2023, false),
        std::make_tuple("MMMCMXCIX", 3999, false),
        std::make_tuple("", 0, true),
        std::make_tuple("MMMM", 0, true),
        std::make_tuple("ABC", 0, true),
        std::make_tuple("MMMCMXCIY", 0, true)
    )
);
