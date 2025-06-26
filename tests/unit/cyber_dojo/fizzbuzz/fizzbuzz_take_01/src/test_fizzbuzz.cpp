#include <gtest/gtest.h>

extern "C" {
#include "../../../../projects/cyber_dojo/fizzbuzz/fizzbuzz_take_01/src/fizzbuzz.h"
#include "../../../../projects/cyber_dojo/fizzbuzz/fizzbuzz_take_01/src/utils/utils.h"
}

using namespace ::testing;

class FizzbuzzSingleTest : public TestWithParam<std::tuple<int, const char*>> {
protected:
    char buffer[100]{};

    void SetUp() override {
        memset(buffer, 0, sizeof(buffer));
    }
};

TEST_P(FizzbuzzSingleTest, SingleNumber) {
    auto [input, expected] = GetParam();
    fizzbuzz(input, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, expected)
            << "Fizzbuzz(" << input << ") = "
            << buffer << ", want " << expected;
}

INSTANTIATE_TEST_SUITE_P(FizzbuzzSingle, FizzbuzzSingleTest,
    Values(
        std::make_tuple(1, "1"),
        std::make_tuple(2, "2"),
        std::make_tuple(3, "Fizz"),
        std::make_tuple(4, "4"),
        std::make_tuple(5, "Buzz"),
        std::make_tuple(6, "Fizz"),
        std::make_tuple(10, "Buzz"),
        std::make_tuple(13, "13"),
        std::make_tuple(15, "FizzBuzz"),
        std::make_tuple(52, "52")
    )
);

class FizzbuzzRangeTest : public TestWithParam<std::tuple<int, const char*>> {
protected:
    char buffer[100]{};

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
            "1\n2\nFizz\n4\nBuzz\nFizz\n7\n8\nFizz\nBuzz\n11\nFizz\n13\n14\nFizzBuzz")
    )
);

TEST(FizzbuzzRangeHundredTest, RangeUntilOneHundred) {
    const int n = 100;
    char** result = static_cast<char**>(malloc(n * sizeof(char*)));
    ASSERT_NE(result, nullptr);

    fizzbuzz_range(n, result);

    char expected[4096] = "";
    strcat(expected, "1\n2\nFizz\n4\nBuzz\nFizz\n7\n8\nFizz\nBuzz\n11\nFizz\n13\n14\n");
    strcat(expected, "FizzBuzz\n16\n17\nFizz\n19\nBuzz\nFizz\n22\n23\nFizz\nBuzz\n26\n");
    strcat(expected, "Fizz\n28\n29\nFizzBuzz\n31\n32\nFizz\n34\nBuzz\nFizz\n37\n38\nFizz\n");
    strcat(expected, "Buzz\n41\nFizz\n43\n44\nFizzBuzz\n46\n47\nFizz\n49\nBuzz\nFizz\n");
    strcat(expected, "52\n53\nFizz\nBuzz\n56\nFizz\n58\n59\nFizzBuzz\n61\n62\nFizz\n64\n");
    strcat(expected, "Buzz\nFizz\n67\n68\nFizz\nBuzz\n71\nFizz\n73\n74\nFizzBuzz\n76\n");
    strcat(expected, "77\nFizz\n79\nBuzz\nFizz\n82\n83\nFizz\nBuzz\n86\nFizz\n88\n89\n");
    strcat(expected, "FizzBuzz\n91\n92\nFizz\n94\nBuzz\nFizz\n97\n98\nFizz\nBuzz");

    char longBuffer[4096];
    string_join(result, n, longBuffer, sizeof(longBuffer));

    EXPECT_STREQ(longBuffer, expected) << "FizzbuzzRange(100) produced incorrect result";

    free_fizzbuzz_range(result, n);
    free(result);
}
