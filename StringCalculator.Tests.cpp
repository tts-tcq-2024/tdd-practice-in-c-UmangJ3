#include <gtest/gtest.h>
#include "StringCalculator.h"

TEST(StringCalculatorAddTests, ExpectZeroForEmptyInput) {
    int expectedresult = 0;
    const char* input = "";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, ExpectSumForSingleNumber) {
    int expectedresult = 1;
    const char* input = "1";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, ExpectSumForTwoNumbers) {
    int expectedresult = 3;
    const char* input = "1,2";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, ExpectSumWithNewlineDelimiter) {
    int expectedresult = 6;
    const char* input = "1\n2,3";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, ExpectSumWithCustomDelimiter) {
    int expectedresult = 3;
    const char* input = "//;\n1;2";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, ThrowExceptionForNegativeNumbers) {
    const char* input = "1,-2,3";
    EXPECT_THROW({
        try {
            add(input);
        } catch (const std::runtime_error& e) {
            EXPECT_STREQ("negatives not allowed: -2", e.what());
            throw;
        }
    }, std::runtime_error);
}

TEST(StringCalculatorAddTests, IgnoreNumbersGreaterThan1000) {
    int expectedresult = 2;
    const char* input = "2,1001";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, ExpectSumWithLongCustomDelimiter) {
    int expectedresult = 6;
    const char* input = "//[***]\n1***2***3";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}
