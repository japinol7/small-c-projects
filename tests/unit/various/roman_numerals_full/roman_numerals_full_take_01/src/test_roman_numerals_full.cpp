#include <gtest/gtest.h>
#include <cstring>

extern "C" {
#include "../../../../projects/various/roman_numerals_full/roman_numerals_full_take_01/src/roman_numerals_full.h"
}

struct ToRomanTestCase {
    int num;
    const char* expected;
    bool has_error;

    static std::string GetTestName(
        const testing::TestParamInfo<ToRomanTestCase>& info
    ) {
        if (info.param.expected == "") {
            // Replace invalid characters with underscores
            std::string name = std::to_string(info.param.num);
            std::replace(name.begin(), name.end(), '-', '_');
            return "Input_Error_" + name;
        }
        // Replace invalid characters with underscores
        std::string name = std::to_string(info.param.num);
        std::replace(name.begin(), name.end(), '-', '_');
        return "Number_" + name + "_Expected_" + info.param.expected;
    }
};

struct FromRomanTestCase {
    const char* roman;
    int expected;
    bool has_error;

    static std::string GetTestName(
        const testing::TestParamInfo<FromRomanTestCase>& info
    ) {
        if (info.param.expected == 0) {
            return std::string("Input_Error_") + info.param.roman;
        }
        return std::string("Roman_") + info.param.roman
               + std::string("_Expected_")
               + std::to_string(info.param.expected);;
    }
};

// Parameterized test class for ToRoman conversion
class ToRomanTest : public testing::TestWithParam<
    ToRomanTestCase> {
protected:
    char roman_buffer[20]{};

    void SetUp() override {
        memset(roman_buffer, 0, sizeof(roman_buffer));
    }
};

TEST_P(ToRomanTest, ConvertToRoman) {
    const auto& [num, expected, has_error] = GetParam();
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

INSTANTIATE_TEST_SUITE_P(
    RomanNumerals,
    ToRomanTest,
    testing::Values(
        ToRomanTestCase{1, "I", false},
        ToRomanTestCase{2, "II", false},
        ToRomanTestCase{3, "III", false},
        ToRomanTestCase{4, "IV", false},
        ToRomanTestCase{5, "V", false},
        ToRomanTestCase{9, "IX", false},
        ToRomanTestCase{10, "X", false},
        ToRomanTestCase{40, "XL", false},
        ToRomanTestCase{50, "L", false},
        ToRomanTestCase{73, "LXXIII", false},
        ToRomanTestCase{90, "XC", false},
        ToRomanTestCase{93, "XCIII", false},
        ToRomanTestCase{100, "C", false},
        ToRomanTestCase{400, "CD", false},
        ToRomanTestCase{500, "D", false},
        ToRomanTestCase{900, "CM", false},
        ToRomanTestCase{1000, "M", false},
        ToRomanTestCase{1984, "MCMLXXXIV", false},
        ToRomanTestCase{2023, "MMXXIII", false},
        ToRomanTestCase{3999, "MMMCMXCIX", false},
        ToRomanTestCase{0, "", true}, // Error case
        ToRomanTestCase{4000, "", true}, // Error case
        ToRomanTestCase{-1, "", true} // Error case
    ),
    ToRomanTestCase::GetTestName
);

// Parameterized test class for FromRoman conversion
class FromRomanTest : public testing::TestWithParam<
    FromRomanTestCase> {
protected:
    int num{};
};

TEST_P(FromRomanTest, ConvertFromRoman) {
    const auto& [roman, expected, has_error] = GetParam();
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

INSTANTIATE_TEST_SUITE_P(
    RomanNumerals,
    FromRomanTest,
    testing::Values(
        // Valid cases - single numerals
        FromRomanTestCase{"I", 1, false},
        FromRomanTestCase{"V", 5, false},
        FromRomanTestCase{"X", 10, false},
        FromRomanTestCase{"L", 50, false},
        FromRomanTestCase{"C", 100, false},
        FromRomanTestCase{"D", 500, false},
        FromRomanTestCase{"M", 1000, false},

        // Valid cases - common combinations
        FromRomanTestCase{"II", 2, false},
        FromRomanTestCase{"III", 3, false},
        FromRomanTestCase{"IV", 4, false},
        FromRomanTestCase{"IX", 9, false},
        FromRomanTestCase{"XL", 40, false},
        FromRomanTestCase{"LXXIII", 73, false},
        FromRomanTestCase{"XC", 90, false},
        FromRomanTestCase{"XCIII", 93, false},
        FromRomanTestCase{"CD", 400, false},
        FromRomanTestCase{"CM", 900, false},

        // Valid cases - large numbers
        FromRomanTestCase{"MCMLXXXIV", 1984, false},
        FromRomanTestCase{"MMXXIII", 2023, false},
        FromRomanTestCase{"MMMCMXCIX", 3999, false},

        // Error cases
        FromRomanTestCase{"", 0, true},
        FromRomanTestCase{"MMMM", 0, true}, // Error case (4000)
        FromRomanTestCase{"ABC", 0, true}, // Invalid chars
        FromRomanTestCase{"MMMCMXCIY", 0, true} // Invalid char Y
    ),
    FromRomanTestCase::GetTestName
);

// Round-trip test class
class RoundTripTest : public testing::Test {
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

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
