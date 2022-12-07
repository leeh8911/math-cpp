/// @file matrix_solver_test.cpp
/// @author sangwon (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2022-12-05
///
/// @copyright Copyright (c) 2022
///
///
#include "src/matrix/matrix_solver.h"

#include <gtest/gtest.h>

#include <eigen3/Eigen/Dense>
#include <iostream>
#include <stdexcept>

#include "src/matrix/matrix.h"
#include "test/matrix/matrix_test_helper.h"

using math_cpp::matrix::EigenSolver;
using math_cpp::matrix::Matrix;

namespace math_cpp {
namespace test {
TEST(MatrixSolverTest, PowerIteration) {
    Matrix A{{1, 0, 0}, {0, 2, 0}, {0, 0, -3}};

    EigenSolver solver(A);

    // Matrix expect_eigen_value{{-3}, {2}, {1}};
    // Matrix expect_eigen_vector{{0, 0, 1}, {0, 1, 0}, {1, 0, 0}};

    Matrix eigen_vectors_t = solver.Eigenvectors().Transpose();
    Matrix eigen_values = solver.Eigenvalues();
    Matrix restore_A = Matrix::Zeros(A);

    for (std::size_t index = 0; index < eigen_vectors_t.Row(); ++index) {
        Matrix eigen_vector_t = eigen_vectors_t.GetRow(index);

        restore_A += eigen_values(index, 0) * eigen_vector_t.Transpose() * eigen_vector_t;
    }

    EXPECT_EQ(A, restore_A);
}

TEST(MatrixSolverTest, EigenLibEigenCase) {
    Matrix A{{1, 0, 0}, {0, 2, 0}, {0, 0, -3}};

    Eigen::MatrixXd e_eigen_values{}, e_eigen_vectors{};
    std::tie(e_eigen_values, e_eigen_vectors) = CalculateEigen(A);

    EigenSolver solver(A);

    EXPECT_TRUE(e_eigen_values == solver.Eigenvalues()) << "Eigen result\n"
                                                        << e_eigen_values << "\nMathLib result\n"
                                                        << solver.Eigenvalues();
    EXPECT_TRUE(e_eigen_vectors == solver.Eigenvectors()) << "Eigen result\n"
                                                          << e_eigen_vectors << "\nMathLib result\n"
                                                          << solver.Eigenvectors();
}
}  // namespace test
}  // namespace math_cpp
