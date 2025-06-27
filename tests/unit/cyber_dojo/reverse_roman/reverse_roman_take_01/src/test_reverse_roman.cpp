#include <gtest/gtest.h>
#include <cstring>

extern "C" {
#include "../../../../projects/cyber_dojo/reverse_roman/reverse_roman_take_01/src/reverse_roman.h"
}

struct RomanConversionTestCase {
    std::string roman;
    int expected;
    bool has_error;

    static std::string GetTestName(
        const testing::TestParamInfo<RomanConversionTestCase>& info
    ) {
        if (info.param.expected == 0) {
            return "Input_Error_" + info.param.roman;
        }
        return info.param.roman + "_Expected_"
               + std::to_string(info.param.expected);
    }
};

class ReverseRomanTest : public testing::TestWithParam<
    RomanConversionTestCase> {
protected:
    int num{};
};

TEST_P(ReverseRomanTest, FromRoman) {
    const auto& [roman, expected, has_error] = GetParam();
    const int result = from_roman(roman.c_str(), &num);

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
    ReverseRomanTests,
    ReverseRomanTest,
    testing::Values(
        // Valid cases - single numerals
        RomanConversionTestCase{"I", 1, false},
        RomanConversionTestCase{"V", 5, false},
        RomanConversionTestCase{"X", 10, false},
        RomanConversionTestCase{"L", 50, false},
        RomanConversionTestCase{"C", 100, false},
        RomanConversionTestCase{"D", 500, false},
        RomanConversionTestCase{"M", 1000, false},

        // Valid cases - common combinations
        RomanConversionTestCase{"II", 2, false},
        RomanConversionTestCase{"III", 3, false},
        RomanConversionTestCase{"IV", 4, false},
        RomanConversionTestCase{"IX", 9, false},
        RomanConversionTestCase{"XL", 40, false},
        RomanConversionTestCase{"LXXIII", 73, false},
        RomanConversionTestCase{"XC", 90, false},
        RomanConversionTestCase{"XCIII", 93, false},
        RomanConversionTestCase{"CD", 400, false},
        RomanConversionTestCase{"CM", 900, false},

        // Valid cases - large numbers
        RomanConversionTestCase{"MCMLXXXIV", 1984, false},
        RomanConversionTestCase{"MMXXIII", 2023, false},
        RomanConversionTestCase{"MMMCMXCIX", 3999, false},

        // Error cases
        RomanConversionTestCase{"", 0, true},
        RomanConversionTestCase{"MMMM", 0, true}, // Error case (4000)
        RomanConversionTestCase{"ABC", 0, true}, // Invalid chars
        RomanConversionTestCase{"MMMCMXCIY", 0, true} // Invalid char Y
    ),
    RomanConversionTestCase::GetTestName
);

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
