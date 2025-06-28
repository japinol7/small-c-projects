#include <gtest/gtest.h>

extern "C" {
#include "../../../../projects/cyber_dojo/count_coins/count_coins_take_01/src/count_coins.h"
}

// Test case structure for parameterized tests
struct CountCoinsTestCase {
    int input;
    int expected;

    static std::string GetTestName(
        const testing::TestParamInfo<CountCoinsTestCase>& info
    ) {
        return "Amount_" + std::to_string(info.param.input) +
               "_Expected_" + std::to_string(info.param.expected);
    }
};

// Parameterized test class
class CountCoinsParameterizedTest : public testing::TestWithParam<
    CountCoinsTestCase> {
};

// Single parameterized test that runs for each test case
TEST_P(CountCoinsParameterizedTest, ChangeCalculation) {
    const auto& [input, expected] = GetParam();
    const int result = count_coins_changes(input);

    EXPECT_EQ(expected, result)
        << "count_coins_changes(&cc, " << input << ") = "
        << result << ", expected " << expected;
}

// Instantiate the test suite with all test cases
INSTANTIATE_TEST_SUITE_P(
    CountCoinsTests,
    CountCoinsParameterizedTest,
    testing::Values(
        CountCoinsTestCase{0, 0},
        CountCoinsTestCase{15, 6},
        CountCoinsTestCase{20, 9},
        CountCoinsTestCase{25, 13},
        CountCoinsTestCase{30, 18},
        CountCoinsTestCase{53, 49},
        CountCoinsTestCase{100, 242}
    ),
    CountCoinsTestCase::GetTestName
);

// Special test for 100 cents with additional output
TEST(CountCoinsSpecialTest, Changes100Cents) {
    const int result = count_coins_changes(100);
    constexpr int expected = 242;

    EXPECT_EQ(expected, result);

    // Print output for visual inspection
    std::cout << "Output: " << std::endl;
    std::cout << "How many ways are there to make change for a dollar " << std::endl;
    std::cout << "using these common coins? (1 dollar = 100 cents) " << std::endl;
    std::cout << "Result: " << result << std::endl;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
