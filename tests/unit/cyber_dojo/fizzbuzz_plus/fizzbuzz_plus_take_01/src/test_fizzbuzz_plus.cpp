#include <gtest/gtest.h>

extern "C" {
#include "../../../../projects/cyber_dojo/fizzbuzz_plus/fizzbuzz_plus_take_01/src/fizzbuzz_plus.h"
#include "../../../../projects/cyber_dojo/fizzbuzz_plus/fizzbuzz_plus_take_01/src/utils/utils.h"
}

using namespace ::testing;

class FizzbuzzPlusTest : public Test {
protected:
    char buffer[100]{};

    void SetUp() override {
        memset(buffer, 0, sizeof(buffer));
    }
};

TEST_F(FizzbuzzPlusTest, SingleNumbers) {
    struct TestCase {
        int input;
        const char* expected;
    };

    TestCase tests[] = {
        {1, "1"},
        {2, "2"},
        {3, "Fizz"},
        {4, "4"},
        {5, "Buzz"},
        {6, "Fizz"},
        {10, "Buzz"},
        {12, "Fizz"},
        {13, "Fizz"},
        {15, "FizzBuzz"},
        {52, "Buzz"}
    };

    for (const auto& test : tests) {
        fizzbuzz(test.input, buffer, sizeof(buffer));
        EXPECT_STREQ(buffer, test.expected) << "Fizzbuzz(" << test.input << ") = "
                                           << buffer << ", want " << test.expected;
    }
}

TEST_F(FizzbuzzPlusTest, Range) {
    struct TestCase {
        int input;
        const char* expected;
    };

    TestCase tests[] = {
        {1, "1"},
        {2, "1\n2"},
        {15, "1\n2\nFizz\n4\nBuzz\nFizz\n7\n8\nFizz\nBuzz\n11\nFizz\nFizz\n14\nFizzBuzz"}
    };

    for (const auto& test : tests) {
        char** result = (char**)malloc(test.input * sizeof(char*));
        ASSERT_NE(result, nullptr);

        fizzbuzz_range(test.input, result);
        string_join(result, test.input, buffer, sizeof(buffer));

        EXPECT_STREQ(buffer, test.expected) << "string_join(fizzbuzz_range(" << test.input << ")) = "
                                            << buffer << ", want " << test.expected;

        free_fizzbuzz_range(result, test.input);
        free(result);
    }
}

TEST_F(FizzbuzzPlusTest, RangeUntilOneHundred) {
    const int n = 100;
    char** result = (char**)malloc(n * sizeof(char*));
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
