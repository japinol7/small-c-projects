#include <gtest/gtest.h>

extern "C" {
#include "../../../../projects/cyber_dojo/leap_year/leap_year_take_01/src/leap_year.h"
}

using namespace ::testing;

class LeapYearTest : public TestWithParam<std::tuple<int, bool>> {
protected:
    void SetUp() override {
        // No setup needed
    }
};

TEST_P(LeapYearTest, SingleYear) {
    auto [year, expected] = GetParam();
    const bool result = IsLeapYear(year) != 0;
    EXPECT_EQ(result, expected) << "IsLeapYear(" << year << ") = "
        << (result ? "true" : "false") << "; want "
        << (expected ? "true" : "false");
}

INSTANTIATE_TEST_SUITE_P(LeapYearTests, LeapYearTest,
    Values(
        std::make_tuple(2001, false),
        std::make_tuple(1996, true),
        std::make_tuple(1900, false),
        std::make_tuple(2000, true),
        std::make_tuple(2023, false),
        std::make_tuple(2024, true),
        std::make_tuple(0, false)
    )
);
