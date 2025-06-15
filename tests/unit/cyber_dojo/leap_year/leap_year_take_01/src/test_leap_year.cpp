#include <gtest/gtest.h>

extern "C" {
#include "../../../../projects/cyber_dojo/leap_year/leap_year_take_01/src/leap_year.h"
}

using namespace ::testing;

class LeapYearTest : public Test {
protected:
    void SetUp() override {
        // No setup code needed
    }
};

TEST_F(LeapYearTest, TestIsLeapYear) {
    // Define test cases
    struct TestCase {
        int year;
        bool expected;
    };

    TestCase tests[] = {
        {2001, false},
        {1996, true},
        {1900, false},
        {2000, true},
        {2023, false},
        {2024, true},
        {0, false}
    };

    // Run tests
    for (const auto& [year, expected] : tests) {
        bool result = IsLeapYear(year) != 0;
        EXPECT_EQ(
            result, expected) << "IsLeapYear(" << year << ") = "
                << (result ? "true" : "false") << "; want "
                << (expected ? "true" : "false");
    }
}
