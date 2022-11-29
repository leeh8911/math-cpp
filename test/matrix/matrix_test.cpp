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

TEST(MatrixTest, MatrixMultiplication) {
    Matrix A{{1.0, 2.0}, {3.0, 4.0}};
    Matrix B{{1.0, 0.0}, {0.0, 1.0}};

    EXPECT_EQ(A, (A * B));
    EXPECT_EQ(A, (B * A));
}

TEST(MatrixTest, MatrixInverse) {
    Matrix A{{1.0, 0.0}, {0.0, 1.0}};

    EXPECT_EQ(A, A.Inverse());
}

TEST(MatrixTest, MatrixRowConcatenate) {
    Matrix A{{1.0, 0.0}, {0.0, 1.0}};
    Matrix B{{1.0, 0.0}, {0.0, 1.0}};

    Matrix result = Matrix::Concatenate(A, B, 0);
    Matrix expect{{1.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}, {0.0, 1.0}};

    EXPECT_EQ(expect, result);
}

TEST(MatrixTest, MatrixColConcatenate) {
    Matrix A{{1.0, 0.0}, {0.0, 1.0}};
    Matrix B{{1.0, 0.0}, {0.0, 1.0}};

    Matrix result = Matrix::Concatenate(A, B, 1);
    Matrix expect{{1.0, 0.0, 1.0, 0.0}, {0.0, 1.0, 0.0, 1.0}};

    EXPECT_EQ(expect, result);
}

}  // namespace test
}  // namespace math_cpp
