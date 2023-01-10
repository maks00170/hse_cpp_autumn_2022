#include <iostream>
#include <gtest/gtest.h>

#include "ser.hpp"

class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};

struct Data2
{
    uint64_t a;
    uint64_t b;
    bool c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>

    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
   
};




TEST(TestSerializer, test_good)
{
    Data x { 1380, false, 1480 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data y { 1799, true, 1789 };

    Deserializer deserializer(stream);
    const Error error = deserializer.load(y);

    ASSERT_EQ(error, Error::NoError);

    ASSERT_EQ(x.a, y.a);
    ASSERT_EQ(x.b, y.b);
    ASSERT_EQ(x.c, y.c);
}


TEST(TestSerializer, test_bad)
{
    Data x {  1242, true, 1240 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data2 y { 1945, 1941, true };

    Deserializer deserializer(stream);
    
    Error error = deserializer.load(y);

    ASSERT_EQ(error, Error::CorruptedArchive);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}