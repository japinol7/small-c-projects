#include <gtest/gtest.h>
#include <cstring>

extern "C" {
#include "../../../../projects/various/roman_numerals_full/roman_numerals_full_take_01/src/roman_numerals_full.h"
}

using namespace ::testing;

// Parameterized test class for ToRoman conversion
class ToRomanTest : public TestWithParam<std::tuple<int, const char*, bool>> {
protected:
    char roman_buffer[20]{};

    void SetUp() override {
        memset(roman_buffer, 0, sizeof(roman_buffer));
    }
};

TEST_P(ToRomanTest, ConvertToRoman) {
    auto [num, expected, has_error] = GetParam();
    const int result = to_roman(num, roman_buffer, sizeof(roman_buffer));

    if (has_error) {
        EXPECT_EQ(-1, result) << "to_roman(" << num << ") should return error";
    } else {
        EXPECT_EQ(0, result) << "to_roman(" << num << ") should succeed";
        EXPECT_STREQ(expected, roman_buffer)
            << "to_roman(" << num << ") = " << roman_buffer
            << ", expected " << expected;
    }
}

INSTANTIATE_TEST_SUITE_P(ToRomanCases, ToRomanTest,
    Values(
        std::make_tuple(1, "I", false),
        std::make_tuple(2, "II", false),
        std::make_tuple(3, "III", false),
        std::make_tuple(4, "IV", false),
        std::make_tuple(5, "V", false),
        std::make_tuple(9, "IX", false),
        std::make_tuple(10, "X", false),
        std::make_tuple(40, "XL", false),
        std::make_tuple(50, "L", false),
        std::make_tuple(73, "LXXIII", false),
        std::make_tuple(90, "XC", false),
        std::make_tuple(93, "XCIII", false),
        std::make_tuple(100, "C", false),
        std::make_tuple(400, "CD", false),
        std::make_tuple(500, "D", false),
        std::make_tuple(900, "CM", false),
        std::make_tuple(1000, "M", false),
        std::make_tuple(1984, "MCMLXXXIV", false),
        std::make_tuple(2023, "MMXXIII", false),
        std::make_tuple(3999, "MMMCMXCIX", false),
        std::make_tuple(0, "", true), // Error case
        std::make_tuple(4000, "", true), // Error case
        std::make_tuple(-1, "", true) // Error case
    )
);

// Parameterized test class for FromRoman conversion
class FromRomanTest : public TestWithParam<std::tuple<const char*, int, bool>> {
protected:
    int num{};
};

TEST_P(FromRomanTest, ConvertFromRoman) {
    auto [roman, expected, has_error] = GetParam();
    const int result = from_roman(roman, &num);

    if (has_error) {
        EXPECT_EQ(-1, result)
            << "from_roman(" << roman << ") should return error";
    } else {
        EXPECT_EQ(0, result) << "from_roman(" << roman << ") should succeed";
        EXPECT_EQ(expected, num)
            << "from_roman(" << roman << ") = " << num
            << ", expected " << expected;
    }
}

INSTANTIATE_TEST_SUITE_P(FromRomanCases, FromRomanTest,
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
        std::make_tuple("", 0, true), // Error case
        std::make_tuple("MMMM", 0, true), // Error case (4000)
        std::make_tuple("ABC", 0, true), // Error case (invalid chars)
        std::make_tuple("MMMCMXCIY", 0, true) // Error case (invalid char Y)
    )
);

// Round-trip test class
class RoundTripTest : public Test {
protected:
    char roman_buffer[20]{};

    void SetUp() override {
        memset(roman_buffer, 0, sizeof(roman_buffer));
    }
};

TEST_F(RoundTripTest, RoundTrip) {
    for (int i = 1; i <= 3999; i += 100) {
        int result_num = 0;

        int result1 = to_roman(i, roman_buffer, sizeof(roman_buffer));
        ASSERT_EQ(0, result1) << "to_roman(" << i << ") failed";

        int result2 = from_roman(roman_buffer, &result_num);
        ASSERT_EQ(0, result2) << "from_roman(" << roman_buffer << ") failed";

        EXPECT_EQ(i, result_num)
                << "Round trip failed: " << i << " -> "
                << roman_buffer << " -> " << result_num;

        memset(roman_buffer, 0, sizeof(roman_buffer));
    }
}