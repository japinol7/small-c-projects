#include <gtest/gtest.h>
#include <cstring>

extern "C" {
#include "../../../../projects/cyber_dojo/isbn/isbn_take_01/src/isbn.h"
}

using namespace ::testing;

class IsbnTest : public Test {
protected:
    char result[10] = {};

    void SetUp() override {
        memset(result, 0, sizeof(result));
    }
};

TEST_F(IsbnTest, ValidateISBN13) {
    struct TestCase {
        const char* input_isbn;
        const char* expected;
    };

    TestCase tests[] = {
        {"9780470059029", "true"},
        {"978 0 471 48648 0", "true"},
        {"978-0596809485", "true"},
        {"978-0-13-149505-0", "true"},
        {"978-0-262-13472-9", "true"},
        {"978-0-262-13472-1", "false"},
        {"978-0-262-13472-2", "false"},
        {"978 0 A 471 48648 0", "false"},
        {"978 0 * 471 48648 0", "false"},
        {"978-0-262-13472-X", "false"},
        {"978-13472-2", "false"},
        {"978-0-A62-13472-1", "false"},
    };

    for (const auto& [input_isbn, expected] : tests) {
        validate_isbn(input_isbn, result, sizeof(result));
        EXPECT_STREQ(result, expected)
            << "validate_isbn(\"" << input_isbn << "\") = \""
            << result << "\", want \"" << expected << "\"";
    }
}

TEST_F(IsbnTest, ValidateISBN10) {
    struct TestCase {
        const char* input_isbn;
        const char* expected;
    };

    TestCase tests[] = {
        {"0471958697", "true"},
        {"0 471 60695 2", "true"},
        {"0-470-84525-2", "true"},
        {"0-321-14653-0", "true"},
        {"0-8044-2957-X", "true"},
        {"0-9752298-0-X", "true"},
        {"0-8044-2957-D", "false"},
        {"0-470-84525-3", "false"},
        {"0-4A0-84525-2", "false"},
        {"0-470-*4525-2", "false"},
        {"0-470-8425-2", "false"},
    };

    for (const auto& test : tests) {
        validate_isbn(test.input_isbn, result, sizeof(result));
        EXPECT_STREQ(result, test.expected) 
            << "validate_isbn(\"" << test.input_isbn << "\") = \"" 
            << result << "\", want \"" << test.expected << "\"";
    }
}

TEST_F(IsbnTest, EdgeCases) {
    // Empty string
    validate_isbn("", result, sizeof(result));
    EXPECT_STREQ(result, "false");

    // NULL input
    EXPECT_EQ(validate_isbn(nullptr, result, sizeof(result)), nullptr);

    // NULL result buffer
    EXPECT_EQ(validate_isbn("9780470059029", nullptr, 10), nullptr);

    // Zero result buffer size
    EXPECT_EQ(validate_isbn("9780470059029", result, 0), nullptr);
}
