#include <gtest/gtest.h>
#include <cstring>

extern "C" {
#include "../../../../projects/cyber_dojo/roman_numerals/roman_numerals_take_01/src/roman_numerals.h"
}

struct RomanTestCase {
    int num;
    const char* expected;
    bool has_error;

    static std::string GetTestName(
        const testing::TestParamInfo<RomanTestCase>& info
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
        return "Number_" + name + "_Roman_" + info.param.expected;
    }
};

class RomanNumeralsTest : public testing::TestWithParam<RomanTestCase> {
protected:
    char roman_buffer[20]{};

    void SetUp() override {
        memset(roman_buffer, 0, sizeof(roman_buffer));
    }
};

TEST_P(RomanNumeralsTest, ToRoman) {
    const auto& [num, expected, has_error] = GetParam();
    const int result = to_roman(num, roman_buffer, sizeof(roman_buffer));

    if (has_error) {
        EXPECT_EQ(-1, result) << "to_roman(" << num << ") should return error";
    }
    else {
        EXPECT_EQ(0, result) << "to_roman(" << num << ") should succeed";
        EXPECT_STREQ(expected, roman_buffer)
            << "to_roman(" << num << ") = " << roman_buffer
            << ", expected " << expected;
    }
}

INSTANTIATE_TEST_SUITE_P(
    RomanNumeralsTests,
    RomanNumeralsTest,
    testing::Values(
        RomanTestCase{1, "I", false},
        RomanTestCase{2, "II", false},
        RomanTestCase{3, "III", false},
        RomanTestCase{4, "IV", false},
        RomanTestCase{5, "V", false},
        RomanTestCase{9, "IX", false},
        RomanTestCase{10, "X", false},
        RomanTestCase{40, "XL", false},
        RomanTestCase{50, "L", false},
        RomanTestCase{73, "LXXIII", false},
        RomanTestCase{90, "XC", false},
        RomanTestCase{93, "XCIII", false},
        RomanTestCase{100, "C", false},
        RomanTestCase{400, "CD", false},
        RomanTestCase{500, "D", false},
        RomanTestCase{900, "CM", false},
        RomanTestCase{1000, "M", false},
        RomanTestCase{1984, "MCMLXXXIV", false},
        RomanTestCase{2023, "MMXXIII", false},
        RomanTestCase{3999, "MMMCMXCIX", false},
        RomanTestCase{0, "", true}, // Error case
        RomanTestCase{4000, "", true}, // Error case
        RomanTestCase{-1, "", true} // Error case
    ),
    RomanTestCase::GetTestName
);

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
