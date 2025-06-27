#include <gtest/gtest.h>

extern "C" {
#include "../../../../projects/cyber_dojo/filename_range/filename_range_take_01/src/filename_range.h"
}

struct FilenameTestCase {
    std::string filename;
    std::pair<int, int> expected_range;

    FilenameTestCase(std::string f, std::pair<int, int> r)
        : filename(std::move(f)), expected_range(std::move(r)) {
    }

    static std::string GetTestName(
        const testing::TestParamInfo<FilenameTestCase>& info
    ) {
        if (info.param.filename.empty()) {
            return std::to_string(info.index) + "_" + "Empty";
        }
        // Replace potentially problematic characters in the filename
        std::string name = info.param.filename;
        std::replace(name.begin(), name.end(), '/', '_');
        std::replace(name.begin(), name.end(), '\\', '_');
        std::replace(name.begin(), name.end(), '.', '_');
        std::replace(name.begin(), name.end(), '-', '_');
        std::replace(name.begin(), name.end(), ' ', '_');
        return std::to_string(info.index) + "_" + name;
    }
};

class FilenameRangeTest : public testing::TestWithParam<FilenameTestCase> {
protected:
    int result[2] = {-1, -1};

    void SetUp() override {
        result[0] = -1;
        result[1] = -1;
    }
};

TEST_P(FilenameRangeTest, FilenameRangeCase) {
    const auto& param = GetParam();

    const int range_size = filename_range(param.filename.c_str(), result);

    if (param.filename.empty()) {
        EXPECT_EQ(range_size, 0) << "For empty filename '" << param.filename << "'";
    } else {
        EXPECT_EQ(range_size, 2) << "For filename '" << param.filename << "'";
        EXPECT_EQ(result[0], param.expected_range.first)
                << "Start index mismatch for '" << param.filename << "'";
        EXPECT_EQ(result[1], param.expected_range.second)
                << "End index mismatch for '" << param.filename << "'";
    }
}

INSTANTIATE_TEST_SUITE_P(
    FilenameTests,
    FilenameRangeTest,
    testing::Values(
        FilenameTestCase{"src/Hiker_spec.re", {4, 9}},
        FilenameTestCase{"test/hiker_test.exs", {5, 10}},
        FilenameTestCase{"wibble/test/hiker_spec.rb", {12, 17}},
        FilenameTestCase{"hiker_steps.rb", {0, 5}},
        FilenameTestCase{"hiker_spec.rb", {0, 5}},
        FilenameTestCase{"test_hiker.rb", {5, 10}},
        FilenameTestCase{"test_hiker.py", {5, 10}},
        FilenameTestCase{"test_hiker.sh", {5, 10}},
        FilenameTestCase{"tests_hiker.sh", {6, 11}},
        FilenameTestCase{"test_hiker.coffee", {5, 10}},
        FilenameTestCase{"hiker_spec.coffee", {0, 5}},
        FilenameTestCase{"hikerTest.chpl", {0, 5}},
        FilenameTestCase{"hiker.tests.c", {0, 5}},
        FilenameTestCase{"hiker_tests.c", {0, 5}},
        FilenameTestCase{"hiker_test.c", {0, 5}},
        FilenameTestCase{"hiker_Test.c", {0, 5}},
        FilenameTestCase{"HikerTests.cpp", {0, 5}},
        FilenameTestCase{"hikerTests.cpp", {0, 5}},
        FilenameTestCase{"HikerTest.cs", {0, 5}},
        FilenameTestCase{"HikerTest.java", {0, 5}},
        FilenameTestCase{"DiamondTest.kt", {0, 7}},
        FilenameTestCase{"HikerTest.php", {0, 5}},
        FilenameTestCase{"hikerTest.js", {0, 5}},
        FilenameTestCase{"hiker-test.js", {0, 5}},
        FilenameTestCase{"hiker-spec.js", {0, 5}},
        FilenameTestCase{"hiker.test.js", {0, 5}},
        FilenameTestCase{"hiker.tests.ts", {0, 5}},
        FilenameTestCase{"hiker_tests.erl", {0, 5}},
        FilenameTestCase{"hiker_test.clj", {0, 5}},
        FilenameTestCase{"fizzBuzz_test.d", {0, 8}},
        FilenameTestCase{"hiker_test.go", {0, 5}},
        FilenameTestCase{"hiker.tests.R", {0, 5}},
        FilenameTestCase{"hikertests.swift", {0, 5}},
        FilenameTestCase{"HikerSpec.groovy", {0, 5}},
        FilenameTestCase{"hikerSpec.feature", {0, 5}},
        FilenameTestCase{"hiker.feature", {0, 5}},
        FilenameTestCase{"hiker.fun", {0, 5}},
        FilenameTestCase{"hiker.t", {0, 5}},
        FilenameTestCase{"hiker.plt", {0, 5}},
        FilenameTestCase{"prj/src/Hiker_bike_spec.re.bak", {8, 18}},
        FilenameTestCase{"src\\Hiker_spec.re", {4, 9}},
        FilenameTestCase{"hiker", {0, 5}},
        FilenameTestCase{"", {}}
    ),
    FilenameTestCase::GetTestName
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

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
