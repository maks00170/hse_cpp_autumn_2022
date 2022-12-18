#include <iostream>
#include <gtest/gtest.h>

#include "numpy.hpp"

class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};

// Тест успешно пройдёт.
TEST(TestNumpy, test_all)
{
    Matrix mat = Matrix(2, 2);

    mat.print();
    std::cout << mat << std::endl;
    ASSERT_EQ( mat.get_rows(), 2 );
    ASSERT_EQ( mat.get_cols(), 2 );

    mat[1][0] = 2;
    std::cout << mat << std::endl;
    ASSERT_EQ( mat[1][0], 2 );

    mat *= 5;
    std::cout << mat << std::endl;
    ASSERT_EQ( mat[0][0], 5 );

    Matrix mat2 = Matrix(2, 2);
    Matrix mat3 = mat + mat2;
    std::cout << mat3 << std::endl;
    ASSERT_EQ( mat3[0][0], 6 );

    std::cout << (mat == mat2) << std::endl;
    ASSERT_EQ( mat == mat2, 0 );

    std::cout << (mat3 != mat) << std::endl;
    ASSERT_EQ( mat3 != mat, 1 );

    std::cout << (mat == mat) << std::endl;
    ASSERT_EQ( mat == mat, 1 );
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}