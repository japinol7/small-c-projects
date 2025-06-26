#include <gtest/gtest.h>
#include <cstring>

extern "C" {
#include "../../../../projects/cyber_dojo/isbn/isbn_take_01/src/isbn.h"
}

using namespace ::testing;

class IsbnTestBase : public TestWithParam<std::tuple<const char*, const char*>> {
protected:
    char result[10] = {};

    void SetUp() override {
        memset(result, 0, sizeof(result));
    }
};

class IsbnTest13 : public IsbnTestBase {};
class IsbnTest10 : public IsbnTestBase {};

TEST_P(IsbnTest13, ValidateISBN) {
    auto [input_isbn, expected] = GetParam();
    validate_isbn(input_isbn, result, sizeof(result));
    EXPECT_STREQ(result, expected)
        << "validate_isbn(\"" << input_isbn << "\") = \""
        << result << "\", want \"" << expected << "\"";
}

TEST_P(IsbnTest10, ValidateISBN) {
    auto [input_isbn, expected] = GetParam();
    validate_isbn(input_isbn, result, sizeof(result));
    EXPECT_STREQ(result, expected)
        << "validate_isbn(\"" << input_isbn << "\") = \""
        << result << "\", want \"" << expected << "\"";
}

INSTANTIATE_TEST_SUITE_P(ISBN13Tests, IsbnTest13,
    Values(
        std::make_tuple("9780470059029", "true"),
        std::make_tuple("978 0 471 48648 0", "true"),
        std::make_tuple("978-0596809485", "true"),
        std::make_tuple("978-0-13-149505-0", "true"),
        std::make_tuple("978-0-262-13472-9", "true"),
        std::make_tuple("978-0-262-13472-1", "false"),
        std::make_tuple("978-0-262-13472-2", "false"),
        std::make_tuple("978 0 A 471 48648 0", "false"),
        std::make_tuple("978 0 * 471 48648 0", "false"),
        std::make_tuple("978-0-262-13472-X", "false"),
        std::make_tuple("978-13472-2", "false"),
        std::make_tuple("978-0-A62-13472-1", "false")
    )
);

INSTANTIATE_TEST_SUITE_P(ISBN10Tests, IsbnTest10,
    Values(
        std::make_tuple("0471958697", "true"),
        std::make_tuple("0 471 60695 2", "true"),
        std::make_tuple("0-470-84525-2", "true"),
        std::make_tuple("0-321-14653-0", "true"),
        std::make_tuple("0-8044-2957-X", "true"),
        std::make_tuple("0-9752298-0-X", "true"),
        std::make_tuple("0-8044-2957-D", "false"),
        std::make_tuple("0-470-84525-3", "false"),
        std::make_tuple("0-4A0-84525-2", "false"),
        std::make_tuple("0-470-*4525-2", "false"),
        std::make_tuple("0-470-8425-2", "false")
    )
);

class IsbnEdgeCasesTest : public Test {
protected:
    char result[10] = {};

    void SetUp() override {
        memset(result, 0, sizeof(result));
    }
};

TEST_F(IsbnEdgeCasesTest, EmptyString) {
    validate_isbn("", result, sizeof(result));
    EXPECT_STREQ(result, "false");
}

TEST_F(IsbnEdgeCasesTest, NullInput) {
    EXPECT_EQ(validate_isbn(nullptr, result, sizeof(result)), nullptr);
}

TEST_F(IsbnEdgeCasesTest, NullResultBuffer) {
    EXPECT_EQ(validate_isbn("9780470059029", nullptr, 10), nullptr);
}

TEST_F(IsbnEdgeCasesTest, ZeroResultBufferSize) {
    EXPECT_EQ(validate_isbn("9780470059029", result, 0), nullptr);
}
