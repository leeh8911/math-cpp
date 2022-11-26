/// @file matrix_test.cpp
/// @author sangwon (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2022-11-26
///
/// @copyright Copyright (c) 2022
///
///

#include "src/matrix/matrix.h"

#include <gtest/gtest.h>

#include <iostream>
#include <stdexcept>

using math_cpp::matrix::Matrix;

// TODO(sangwon): 행렬의 기본적인 요소들만 생각하며 구성해보자!
// TODO(sangwon): 기본적인 행렬의 사칙연산 구현해보기

namespace math_cpp {
namespace test {

TEST(MatrixTest, CreationCase) {
    Matrix matrix(2, 2);

    EXPECT_EQ(2, matrix.Row());
    EXPECT_EQ(2, matrix.Col());
}

TEST(MatrixTest, CreationByInitializeCase) {
    Matrix matrix{{1.0, 0.0}, {0.0, 1.0}};

    EXPECT_EQ(2, matrix.Row());
    EXPECT_EQ(2, matrix.Col());

    EXPECT_EQ(1.0, matrix(0, 0));
    EXPECT_EQ(1.0, matrix(1, 1));
    EXPECT_EQ(0.0, matrix(0, 1));
    EXPECT_EQ(0.0, matrix(1, 0));
}

TEST(MatrixTest, CreationByInitialize2Case) {
    Matrix matrix{{1.0, 2.0}, {3.0, 4.0}};

    EXPECT_EQ(2, matrix.Row());
    EXPECT_EQ(2, matrix.Col());

    EXPECT_EQ(1.0, matrix(0, 0));
    EXPECT_EQ(2.0, matrix(0, 1));
    EXPECT_EQ(3.0, matrix(1, 0));
    EXPECT_EQ(4.0, matrix(1, 1));
}

TEST(MatrixTest, AdditionTrivialCase) {
    Matrix lhs{{0.0, 0.0}, {0.0, 0.0}};
    Matrix rhs{{0.0, 0.0}, {0.0, 0.0}};

    Matrix add = lhs + rhs;

    EXPECT_EQ(2, add.Row());
    EXPECT_EQ(2, add.Col());

    EXPECT_EQ(0.0, add(0, 0));
    EXPECT_EQ(0.0, add(0, 1));
    EXPECT_EQ(0.0, add(1, 0));
    EXPECT_EQ(0.0, add(1, 1));
}

TEST(MatrixTest, AdditionDifferentSizeThrowCase) {
    Matrix lhs{{0.0, 0.0}, {0.0, 0.0}};
    Matrix rhs{{0.0}};

    EXPECT_THROW(
        {
            try {
                Matrix add = lhs + rhs;
            } catch (const std::invalid_argument& e) {
                // and this tests that it has the correct message
                EXPECT_STREQ("other matrix must be same size [*this] (2, 2)!", e.what());
                throw;
            }
        },
        std::invalid_argument);
}
TEST(MatrixTest, MultiplyTrivialCase) {
    Matrix lhs{{0.0, 0.0}, {0.0, 0.0}};

    Matrix result = lhs * 1.0;

    EXPECT_EQ(0.0, result(0, 0));
    EXPECT_EQ(0.0, result(0, 1));
    EXPECT_EQ(0.0, result(1, 0));
    EXPECT_EQ(0.0, result(1, 1));
}

TEST(MatrixTest, SuperPositionCase) {
    Matrix A{{1.0, 2.0}, {3.0, 4.0}};
    Matrix B{{7.0, -2.0}, {5.0, 8.0}};
    double a = 3.0;
    double b = -2.0;

    Matrix result = a * A + b * B;

    EXPECT_EQ(-11.0, result(0, 0));
    EXPECT_EQ(10.0, result(0, 1));
    EXPECT_EQ(-1.0, result(1, 0));
    EXPECT_EQ(-4.0, result(1, 1));
}
TEST(MatrixTest, SuperPositionTrivialCase) {
    Matrix A{{1.0, 2.0}, {3.0, 4.0}};
    Matrix B = A;
    double a = 1.0;
    double b = -1.0;

    Matrix result = a * A + b * B;

    EXPECT_EQ(Matrix(2, 2), (a * A + b * B));
}

}  // namespace test
}  // namespace math_cpp
