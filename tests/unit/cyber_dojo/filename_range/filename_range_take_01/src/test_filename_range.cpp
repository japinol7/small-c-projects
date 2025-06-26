#include <gtest/gtest.h>

extern "C" {
#include "../../../../projects/cyber_dojo/filename_range/filename_range_take_01/src/filename_range.h"
}

using namespace ::testing;

class FilenameRangeTest : public TestWithParam<std::tuple<std::string, int, int>> {
protected:
    int result[2] = {-1, -1};

    void SetUp() override {
        result[0] = -1;
        result[1] = -1;
    }
};

TEST_P(FilenameRangeTest, FilenameRangeCase) {
    const auto& [filename, expected_start, expected_end] = GetParam();

    const int range_size = filename_range(filename.c_str(), result);

    if (filename.empty()) {
        EXPECT_EQ(range_size, 0) << "For empty filename '" << filename << "'";
    } else {
        EXPECT_EQ(range_size, 2) << "For filename '" << filename << "'";
        EXPECT_EQ(result[0], expected_start)
                << "Start index mismatch for '" << filename << "'";
        EXPECT_EQ(result[1], expected_end)
                << "End index mismatch for '" << filename << "'";
    }
}

INSTANTIATE_TEST_SUITE_P(FilenameRangeCases, FilenameRangeTest,
    Values(
        // Regular test cases
        std::make_tuple("src/Hiker_spec.re", 4, 9),
        std::make_tuple("test/hiker_test.exs", 5, 10),
        std::make_tuple("wibble/test/hiker_spec.rb", 12, 17),
        std::make_tuple("hiker_steps.rb", 0, 5),
        std::make_tuple("hiker_spec.rb", 0, 5),
        std::make_tuple("test_hiker.rb", 5, 10),
        std::make_tuple("test_hiker.py", 5, 10),
        std::make_tuple("test_hiker.sh", 5, 10),
        std::make_tuple("tests_hiker.sh", 6, 11),
        std::make_tuple("test_hiker.coffee", 5, 10),
        std::make_tuple("hiker_spec.coffee", 0, 5),
        std::make_tuple("hikerTest.chpl", 0, 5),
        std::make_tuple("hiker.tests.c", 0, 5),
        std::make_tuple("hiker_tests.c", 0, 5),
        std::make_tuple("hiker_test.c", 0, 5),
        std::make_tuple("hiker_Test.c", 0, 5),
        std::make_tuple("HikerTests.cpp", 0, 5),
        std::make_tuple("hikerTests.cpp", 0, 5),
        std::make_tuple("HikerTest.cs", 0, 5),
        std::make_tuple("HikerTest.java", 0, 5),
        std::make_tuple("DiamondTest.kt", 0, 7),
        std::make_tuple("HikerTest.php", 0, 5),
        std::make_tuple("hikerTest.js", 0, 5),
        std::make_tuple("hiker-test.js", 0, 5),
        std::make_tuple("hiker-spec.js", 0, 5),
        std::make_tuple("hiker.test.js", 0, 5),
        std::make_tuple("hiker.tests.ts", 0, 5),
        std::make_tuple("hiker_tests.erl", 0, 5),
        std::make_tuple("hiker_test.clj", 0, 5),
        std::make_tuple("fizzBuzz_test.d", 0, 8),
        std::make_tuple("hiker_test.go", 0, 5),
        std::make_tuple("hiker.tests.R", 0, 5),
        std::make_tuple("hikertests.swift", 0, 5),
        std::make_tuple("HikerSpec.groovy", 0, 5),
        std::make_tuple("hikerSpec.feature", 0, 5),
        std::make_tuple("hiker.feature", 0, 5),
        std::make_tuple("hiker.fun", 0, 5),
        std::make_tuple("hiker.t", 0, 5),
        std::make_tuple("hiker.plt", 0, 5),
        std::make_tuple("prj/src/Hiker_bike_spec.re.bak", 8, 18),
        std::make_tuple("src\\Hiker_spec.re", 4, 9),
        std::make_tuple("hiker", 0, 5),
        std::make_tuple("", 0, 0)  // Empty filename case
    )
);

// Test empty filename
TEST_F(FilenameRangeTest, EmptyFilename) {
    int result[2] = {-1, -1};
    int range_size = filename_range("", result);
    EXPECT_EQ(range_size, 0) << "For empty filename";
}

// Test NULL filename
TEST_F(FilenameRangeTest, NullFilename) {
    int result[2] = {-1, -1};
    const int range_size = filename_range(nullptr, result);
    EXPECT_EQ(range_size, 0) << "For NULL filename";
}

// Individual tests for specific cases
TEST_F(FilenameRangeTest, RegularFilename) {
    int result[2] = {-1, -1};
    filename_range("hiker.cpp", result);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 5);
}

TEST_F(FilenameRangeTest, TestFilename) {
    int result[2] = {-1, -1};
    filename_range("test_hiker.rb", result);
    EXPECT_EQ(result[0], 5);
    EXPECT_EQ(result[1], 10);
}

TEST_F(FilenameRangeTest, PathWithTestFilename) {
    int result[2] = {-1, -1};
    filename_range("wibble/test/hiker_spec.rb", result);
    EXPECT_EQ(result[0], 12);
    EXPECT_EQ(result[1], 17);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
