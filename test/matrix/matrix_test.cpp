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

#include <eigen3/Eigen/Dense>
#include <iostream>
#include <stdexcept>

using math_cpp::matrix::Matrix;

// TODO(sangwon): 행렬의 기본적인 요소들만 생각하며 구성해보자!
// TODO(sangwon): 기본적인 행렬의 사칙연산 구현해보기
// TODO(sangwon): Determinant
// TODO(sangwon): Eigen value, eigen vector
// TODO(sangwon): Singular value
// TODO(sangwon): Fixed double을 구현하는 것이 좋지 않을까?

namespace math_cpp {
namespace test {

Eigen::MatrixXd MakeEigen(Matrix mat) {
    Eigen::MatrixXd result(mat.Row(), mat.Col());
    for (std::size_t r = 0; r < mat.Row(); ++r) {
        for (std::size_t c = 0; c < mat.Col(); ++c) {
            result(r, c) = mat(r, c);
        }
    }
    return result;
}
Eigen::MatrixXd MakeRandomEigen(std::size_t row, std::size_t col) {
    Eigen::MatrixXd result = Eigen::MatrixXd::Random(row, col);
    return result;
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

TEST(MatrixTest, MatrixMultiplication) {
    Matrix A{{1.0, 2.0}, {3.0, 4.0}};
    Matrix B{{1.0, 0.0}, {0.0, 1.0}};

    EXPECT_EQ(A, (A * B));
    EXPECT_EQ(A, (B * A));
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

TEST(MatrixTest, MultRowCase) {
    Matrix A{{1.0, 1.0}, {1.0, 1.0}};

    A.RowMult(0, 2.0);

    EXPECT_EQ(Matrix({{2.0, 2.0}, {1.0, 1.0}}), A);
}
TEST(MatrixTest, AddRowCase) {
    Matrix A{{1.0, 1.0}, {1.0, 1.0}};

    A.RowAdd(0, Matrix{{1.0, 2.0}});

    EXPECT_EQ(Matrix({{2.0, 3.0}, {1.0, 1.0}}), A);
}

TEST(MatrixTest, InverseMatrixTrivialCase) {
    Matrix A{{1.0, 0.0}, {0.0, 1.0}};
    Matrix invA = A.Inverse();

    EXPECT_EQ(A, invA);
}

TEST(MatrixTest, InverseMatrixPropertyCase) {
    Matrix A{{2.0, 0.0}, {0.0, 2.0}};
    Matrix invA = A.Inverse();

    EXPECT_EQ(Matrix::Identity(2), (A * invA));
    EXPECT_EQ(Matrix::Identity(2), (invA * A));
}

TEST(MatrixTest, InverseMatrixTrivial3x3Case) {
    Matrix A{{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};
    Matrix invA = A.Inverse();

    EXPECT_EQ(A, invA);
}

TEST(MatrixTest, InverseMatrixProperty3x3Case) {
    Matrix A{{2.0, 1.0, 3.0}, {-1.0, 2.0, 5.0}, {8.0, 0.0, 2.0}};
    Matrix invA = A.Inverse();

    EXPECT_EQ(Matrix::Identity(3), (A * invA));
    EXPECT_EQ(Matrix::Identity(3), (invA * A));
}

TEST(MatrixTest, Determinant2x2Case) {
    Matrix A{{1.0, 0.0}, {0.0, 2.0}};

    double det = Matrix::Determinant(A);

    EXPECT_EQ(2.0, det);
}

TEST(MatrixTest, Determinant3x3Case) {
    Matrix A{{1.0, 0.0, 0.0}, {0.0, 2.0, 0.0}, {0.0, 0.0, 3.0}};

    double det = Matrix::Determinant(A);

    EXPECT_EQ(6.0, det);
}

TEST(MatrixTest, EraseRowColMatrixCase11) {
    Matrix A{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};

    Matrix result = Matrix::EraseRowCol(A, 1, 1);

    EXPECT_EQ(Matrix({{1.0, 3.0}, {7.0, 9.0}}), result);
}
TEST(MatrixTest, EraseRowColMatrixCase01) {
    Matrix A{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};

    Matrix result = Matrix::EraseRowCol(A, 0, 1);

    EXPECT_EQ(Matrix({{4.0, 6.0}, {7.0, 9.0}}), result);
}
TEST(MatrixTest, EraseRowColMatrixCase21) {
    Matrix A{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};

    Matrix result = Matrix::EraseRowCol(A, 2, 1);

    EXPECT_EQ(Matrix({{1.0, 3.0}, {4.0, 6.0}}), result);
}
TEST(MatrixTest, EraseRowColMatrixCase10) {
    Matrix A{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};

    Matrix result = Matrix::EraseRowCol(A, 1, 0);

    EXPECT_EQ(Matrix({{2.0, 3.0}, {8.0, 9.0}}), result);
}
TEST(MatrixTest, EraseRowColMatrixCase12) {
    Matrix A{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};

    Matrix result = Matrix::EraseRowCol(A, 1, 2);

    EXPECT_EQ(Matrix({{1.0, 2.0}, {7.0, 8.0}}), result);
}
TEST(MatrixTest, PowerIteration) {
    // http://madrury.github.io/jekyll/update/statistics/2017/10/04/qr-algorithm.html
    // def power_iteration(A, tol=0.0001):
    // v = np.random.normal(size=A.shape[1])
    // v = v / np.linalg.norm(v)
    // previous = np.empty(shape=A.shape[1])
    // while True:
    //     previous[:] = v
    //     v = A @ v
    //     v = v / np.linalg.norm(v)
    //     if np.allclose(v, previous, atol=tol):
    //         break
    // return v
    Matrix A{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};

    double tol = 1e-4;
    Matrix v{{1.0, 0.0, 0.0}};
    Matrix prev(1, 3);

    auto dist = [](const Matrix& lhs, const Matrix& rhs) { Matrix diff = lhs - rhs; };
    while () }

}  // namespace test
}  // namespace math_cpp
