#include <iostream>
#include <gtest/gtest.h>

#include "token_split.hpp"

class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};

TEST(Test_split, test_function)
{
    std::string test_str = "pomen-romen  barabek skushal 200  chelovek";
    
    auto Trans1 = [](std::string & str) {
        for (size_t i = 0; i < str.length(); ++i) {
            if (str[i] == 'a')
                str[i] = 'o';
        }
    };
    auto Trans2 = [](std::string & str) {
        for (size_t i = 0; i < str.length(); ++i) {
            if (i % 2 == 0)
                str[i] = ' ';
        }
    };
    auto Trans3 = [](std::string & str) {
        for (size_t i = 0; i < str.length(); ++i) {
            str[i] = 'x';
        }
    };
    auto Trans4 = [](std::string & str) {   
        str = "1";
    };

    TokenSplit splitter;
    std::string str = " x x x x x , x x x x   x x x , 1  ";
    splitter.setStartCallback(Trans1);
    splitter.setDigitTokenCallback(Trans4);
    splitter.setStringTokenCallback(Trans3);
    splitter.setEndCallback(Trans2);
    splitter.parse(test_str);
    std::string gotten = splitter.split_text;

    ASSERT_EQ( gotten, str);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}