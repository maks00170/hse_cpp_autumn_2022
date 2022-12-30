#include <iostream>
#include <gtest/gtest.h>

#include "big.hpp"

class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};

TEST(TestBigInt, test1)
{
    BigInt a = BigInt(123);
    BigInt b = BigInt(1);
    BigInt c = BigInt(10000);
    BigInt d = BigInt(99);
    std::cout << to_string(a + b);
    ASSERT_EQ(to_string( a + b ), "124");
    ASSERT_EQ(to_string( a * b ), "123");
    ASSERT_EQ(to_string( a - b), "122");
    ASSERT_EQ( a == b , 0);
    ASSERT_EQ(a != b , 1);
    ASSERT_EQ(to_string( b - a), "-122");
    ASSERT_EQ(to_string( c * b), "10000");
    std::cout << to_string(a + b);
}


TEST(TestBigInt, test2)
{
    BigInt a = BigInt("100");
    BigInt a_copy = a;

    ASSERT_EQ(a==a_copy, 1);

    BigInt b = BigInt("101");

    ASSERT_EQ(a < a_copy, 0);
    ASSERT_EQ(a <= a_copy, 1);
    ASSERT_EQ(a == a, 1);
    ASSERT_EQ(-a > b, 0);
    ASSERT_EQ(-a == a, 0);
}


TEST(TestBigInt, test3)
{
    BigInt a = BigInt(100);
    BigInt b = 10 + 10;
    BigInt c = 10 * 2;

    BigInt d = a ;
    BigInt e = a * d;
    BigInt f = e * a;

    ASSERT_EQ(to_string(a), "100");
    ASSERT_EQ(to_string(b), "20");
    ASSERT_EQ(to_string(d), "100");
    ASSERT_EQ(to_string(e), "10000");
    ASSERT_EQ(to_string(f), "1000000");
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}