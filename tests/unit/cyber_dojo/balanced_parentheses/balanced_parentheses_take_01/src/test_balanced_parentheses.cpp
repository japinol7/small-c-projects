#include <gtest/gtest.h>

extern "C" {
#include "../../../../projects/cyber_dojo/balanced_parentheses/balanced_parentheses_take_01/src/balanced_parentheses.h"
}

class BalancedParenthesesTest : public testing::Test {
protected:
    void SetUp() override {
    }
};

TEST_F(BalancedParenthesesTest, EmptyString) {
    EXPECT_TRUE(are_parentheses_balanced(""));
}

TEST_F(BalancedParenthesesTest, SimpleParentheses) {
    EXPECT_TRUE(are_parentheses_balanced("()"));
}

TEST_F(BalancedParenthesesTest, SimpleBraces) {
    EXPECT_TRUE(are_parentheses_balanced("{}"));
}

TEST_F(BalancedParenthesesTest, NestedBracesAndParentheses) {
    EXPECT_TRUE(are_parentheses_balanced("{()}"));
}

TEST_F(BalancedParenthesesTest, ComplexNested) {
    EXPECT_TRUE(are_parentheses_balanced("{[()]}"));
}

TEST_F(BalancedParenthesesTest, AlternativeNesting) {
    EXPECT_TRUE(are_parentheses_balanced("[({})]"));
}

TEST_F(BalancedParenthesesTest, MultiplePairs) {
    EXPECT_TRUE(are_parentheses_balanced("{}([])"));
}

TEST_F(BalancedParenthesesTest, ComplexValid) {
    EXPECT_TRUE(are_parentheses_balanced("{()}[[{}]]"));
}

TEST_F(BalancedParenthesesTest, UnbalancedClose) {
    EXPECT_FALSE(are_parentheses_balanced("[]]"));
}

TEST_F(BalancedParenthesesTest, IncorrectlyNested) {
    EXPECT_FALSE(are_parentheses_balanced("{{})(}"));
}

TEST_F(BalancedParenthesesTest, Mismatched) {
    EXPECT_FALSE(are_parentheses_balanced("({)}"));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
