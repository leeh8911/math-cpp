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

    Matrix expect_eigen_value{{-3}, {2}, {1}};
    Matrix expect_eigen_vector{{0, 0, 1}, {0, 1, 0}, {1, 0, 0}};

    EXPECT_EQ(expect_eigen_value, solver.Eigenvalues());
    EXPECT_EQ(expect_eigen_vector, solver.Eigenvectors());
}

TEST(MatrixSolverTest, EigenLibEigenCase) {
    Matrix A{{1, 0, 0}, {0, 2, 0}, {0, 0, -3}};
    Eigen::MatrixXd mat = MakeEigen(A);

    Eigen::EigenSolver<decltype(mat)> solver(mat);

    auto eigenvalues = solver.eigenvalues().cast<double>();
    std::vector<std::pair<std::size_t, double>> v{};
    std::size_t i = 0;
    std::cout << eigenvalues.rows() << ", " << eigenvalues.cols() << "\n";
    // std::transform(eigenvalues.reshaped().begin(), eigenvalues.reshaped().end(), std::back_inserter(v),
    //                [&i](double e) { return std::make_pair(i++, e); });

    std::cout << solver.eigenvalues() << "\n";
    std::cout << solver.eigenvectors() << "\n";
}
}  // namespace test
}  // namespace math_cpp
