#include <gtest/gtest.h>

extern "C" {
#include "../../../../projects/cyber_dojo/fizzbuzz_plus/fizzbuzz_plus_take_01/src/fizzbuzz_plus.h"
#include "../../../../projects/cyber_dojo/fizzbuzz_plus/fizzbuzz_plus_take_01/src/utils/utils.h"
}

using namespace ::testing;

class FizzbuzzPlusTest : public TestWithParam<std::tuple<int, const char*>> {
protected:
    char buffer[100]{};

    void SetUp() override {
        memset(buffer, 0, sizeof(buffer));
    }
};

TEST_P(FizzbuzzPlusTest, SingleNumber) {
    auto [input, expected] = GetParam();
    fizzbuzz(input, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, expected)
            << "Fizzbuzz(" << input << ") = "
            << buffer << ", want " << expected;
}

INSTANTIATE_TEST_SUITE_P(FizzbuzzSingle, FizzbuzzPlusTest,
    Values(
        std::make_tuple(1, "1"),
        std::make_tuple(2, "2"),
        std::make_tuple(3, "Fizz"),
        std::make_tuple(4, "4"),
        std::make_tuple(5, "Buzz"),
        std::make_tuple(6, "Fizz"),
        std::make_tuple(10, "Buzz"),
        std::make_tuple(12, "Fizz"),
        std::make_tuple(13, "Fizz"),
        std::make_tuple(15, "FizzBuzz"),
        std::make_tuple(52, "Buzz")
    )
);

class FizzbuzzRangeTest : public TestWithParam<std::tuple<int, const char*>> {
protected:
    char buffer[4096]{};

    void SetUp() override {
        memset(buffer, 0, sizeof(buffer));
    }
};

TEST_P(FizzbuzzRangeTest, Range) {
    auto [input, expected] = GetParam();
    
    char** result = static_cast<char**>(malloc(input * sizeof(char*)));
    ASSERT_NE(result, nullptr);

    fizzbuzz_range(input, result);
    string_join(result, input, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, expected)
            << "string_join(fizzbuzz_range(" << input << ")) = "
            << buffer << ", want " << expected;

    free_fizzbuzz_range(result, input);
    free(result);
}

INSTANTIATE_TEST_SUITE_P(FizzbuzzRange, FizzbuzzRangeTest,
    Values(
        std::make_tuple(1, "1"),
        std::make_tuple(2, "1\n2"),
        std::make_tuple(15,
            "1\n2\nFizz\n4\nBuzz\nFizz\n7\n8\nFizz\nBuzz\n11\nFizz\nFizz\n14\nFizzBuzz")
    )
);

TEST(FizzbuzzRangeTest, RangeUntilOneHundred) {
    constexpr int n = 100;
    char** result = static_cast<char**>(malloc(n * sizeof(char*)));
    ASSERT_NE(result, nullptr);

    fizzbuzz_range(n, result);

    char expected[4096] = "";
    strcat(expected, "1\n2\nFizz\n4\nBuzz\nFizz\n7\n8\nFizz\nBuzz\n11\nFizz\nFizz\n14\n");
    strcat(expected, "FizzBuzz\n16\n17\nFizz\n19\nBuzz\nFizz\n22\nFizz\nFizz\nBuzz\n26\n");
    strcat(expected, "Fizz\n28\n29\nFizzBuzz\nFizz\nFizz\nFizz\nFizz\nFizzBuzz\nFizz\n");
    strcat(expected, "Fizz\nFizz\nFizz\nBuzz\n41\nFizz\nFizz\n44\nFizzBuzz\n46\n47\n");
    strcat(expected, "Fizz\n49\nBuzz\nFizzBuzz\nBuzz\nFizzBuzz\nFizzBuzz\nBuzz\nBuzz\n");
    strcat(expected, "FizzBuzz\nBuzz\nBuzz\nFizzBuzz\n61\n62\nFizz\n64\n");
    strcat(expected, "Buzz\nFizz\n67\n68\nFizz\nBuzz\n71\nFizz\nFizz\n74\nFizzBuzz\n76\n");
    strcat(expected, "77\nFizz\n79\nBuzz\nFizz\n82\nFizz\nFizz\nBuzz\n86\nFizz\n88\n89\n");
    strcat(expected, "FizzBuzz\n91\n92\nFizz\n94\nBuzz\nFizz\n97\n98\nFizz\nBuzz");

    char longBuffer[4096];
    string_join(result, n, longBuffer, sizeof(longBuffer));

    EXPECT_STREQ(longBuffer, expected) << "FizzbuzzRange(100) produced incorrect result";

    free_fizzbuzz_range(result, n);
    free(result);
}
