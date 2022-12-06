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

    std::cout << A << "\n";
    std::cout << restore_A << "\n";
}

TEST(MatrixSolverTest, EigenLibEigenCase) {
    Matrix A{{1, 0, 0}, {0, 2, 0}, {0, 0, -3}};
    Eigen::MatrixXd mat = MakeEigen(A);

    Eigen::EigenSolver<decltype(mat)> solver(mat);

    Eigen::MatrixXd eigenvalues = solver.eigenvalues().real();
    Eigen::MatrixXd eigenvectors = solver.eigenvectors().real();

    std::vector<std::pair<std::size_t, double>> v{};
    for (std::size_t i = 0; i < eigenvalues.rows(); ++i) {
        v.emplace_back(i, eigenvalues(i, 0));
    }

    std::sort(std::begin(v), std::end(v), [](std::pair<std::size_t, double> &a, std::pair<std::size_t, double> &b) {
        return std::abs(a.second) > std::abs(b.second);
    });

    Eigen::MatrixXd temp_eigenvalues = eigenvalues;
    Eigen::MatrixXd temp_eigenvectors = eigenvectors;
    for (std::size_t i = 0; i < eigenvalues.rows(); ++i) {
        temp_eigenvalues(i, 0) = v[i].second;
        temp_eigenvectors.col(i) = eigenvectors.col(v[i].first);
    }

    std::cout << temp_eigenvalues << "\n";
    std::cout << temp_eigenvectors << "\n";
}
}  // namespace test
}  // namespace math_cpp
