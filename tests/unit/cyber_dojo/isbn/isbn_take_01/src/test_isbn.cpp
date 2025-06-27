#include <gtest/gtest.h>

extern "C" {
#include "../../../../projects/cyber_dojo/isbn/isbn_take_01/src/isbn.h"
}

struct IsbnTestCase {
    std::string input;
    std::string expected;
    
    static std::string GetTestName(
        const testing::TestParamInfo<IsbnTestCase>& info
    ) {
        // Replace invalid characters with underscores
        std::string name = info.param.input;
        std::replace(name.begin(), name.end(), ' ', '_');
        std::replace(name.begin(), name.end(), '-', '_');
        std::replace(name.begin(), name.end(), '*', '_');
        return std::to_string(info.index) + "_" + "ISBN_" + name;
    }
};

class IsbnValidationTest : public testing::TestWithParam<IsbnTestCase> {
protected:
    char result[10] = {};

    void SetUp() override {
        memset(result, 0, sizeof(result));
    }
};

TEST_P(IsbnValidationTest, ValidateISBN) {
    const auto& [input, expected] = GetParam();
    validate_isbn(input.c_str(), result, sizeof(result));
    EXPECT_STREQ(result, expected.c_str())
        << "validate_isbn(\"" << input << "\") = \""
        << result << "\", want \"" << expected << "\"";
}

INSTANTIATE_TEST_SUITE_P(
    ISBN13Tests,
    IsbnValidationTest,
    testing::Values(
        IsbnTestCase{"9780470059029", "true"},
        IsbnTestCase{"978 0 471 48648 0", "true"},
        IsbnTestCase{"978-0596809485", "true"},
        IsbnTestCase{"978-0-13-149505-0", "true"},
        IsbnTestCase{"978-0-262-13472-9", "true"},
        IsbnTestCase{"978-0-262-13472-1", "false"},
        IsbnTestCase{"978-0-262-13472-2", "false"},
        IsbnTestCase{"978 0 A 471 48648 0", "false"},
        IsbnTestCase{"978 0 * 471 48648 0", "false"},
        IsbnTestCase{"978-0-262-13472-X", "false"},
        IsbnTestCase{"978-13472-2", "false"},
        IsbnTestCase{"978-0-A62-13472-1", "false"}
    ),
    IsbnTestCase::GetTestName
);

INSTANTIATE_TEST_SUITE_P(
    ISBN10Tests,
    IsbnValidationTest,
    testing::Values(
        IsbnTestCase{"0471958697", "true"},
        IsbnTestCase{"0 471 60695 2", "true"},
        IsbnTestCase{"0-470-84525-2", "true"},
        IsbnTestCase{"0-321-14653-0", "true"},
        IsbnTestCase{"0-8044-2957-X", "true"},
        IsbnTestCase{"0-9752298-0-X", "true"},
        IsbnTestCase{"0-8044-2957-D", "false"},
        IsbnTestCase{"0-470-84525-3", "false"},
        IsbnTestCase{"0-4A0-84525-2", "false"},
        IsbnTestCase{"0-470-*4525-2", "false"},
        IsbnTestCase{"0-470-8425-2", "false"}
    ),
    IsbnTestCase::GetTestName
);

class IsbnEdgeCasesTest : public testing::Test {
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

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
