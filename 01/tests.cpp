#include <iostream>
#include <gtest/gtest.h>

#include "allocator.hpp"

class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};

// Тест успешно пройдёт.
TEST(TestAlloc, makeAllocator)
{
    Allocator al;
    al.makeAllocator( 15 ); // выделяем 15 байт

    {
        char *res = al.alloc( 7 );  // забираем 7 байт
        ASSERT_TRUE( res != nullptr );
    }

    {
        char *res = al.alloc( 8 );  // забираем 8 байт
        ASSERT_TRUE( res != nullptr );
    }


    {
        char *res = al.alloc( 1 ); // пытаемся забрать 1 байт
        ASSERT_EQ( res, nullptr ); // должно не получиться
    }

    al.reset(); 
 
    {
        char *res = al.alloc( 1 ); // проверяем наличия места
        ASSERT_TRUE( res != nullptr );
    }
}

TEST(TestAlloc, alloc)
{
    Allocator al;
    al.makeAllocator( 10 ); //выделяем 10 байт

    {
        char *res = al.alloc( 0 ); // пытаемся забрать 0 байт
        ASSERT_TRUE( res == nullptr ); //должно быть ничего
    }

    {
        char *res = al.alloc( 10 ); // забираем 10 байт
        ASSERT_TRUE( res != nullptr );
    }

    {
        char *res = al.alloc( 1 ); // пытаемся забрать 1 байт
        ASSERT_EQ( res, nullptr ); // должно не получиться
    }

}

TEST(TestAlloc, reset)
{
    Allocator al;
    al.makeAllocator( 15 ); // выделяем 15 байт

    {
        char *res = al.alloc( 15 ); // выделяем 15 байт
        ASSERT_TRUE( res != nullptr );
    }

    al.reset();


    {
        char *res = al.alloc( 1 ); // пытаемся забрать 1 байт
        ASSERT_TRUE( res != nullptr ); // должно получиться
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}