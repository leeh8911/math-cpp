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
TEST(MatrixSolverTest, EigenPropertyCheckCase) {
    Matrix A{{1, 0, 0}, {0, 2, 0}, {0, 0, -3}};

    EigenSolver solver(A);

    Matrix eigen_vectors_t = solver.Eigenvectors().Transpose();
    Matrix eigen_values = solver.Eigenvalues();
    Matrix restore_A = Matrix::Zeros(A);

    for (std::size_t index = 0; index < eigen_vectors_t.Row(); ++index) {
        Matrix eigen_vector_t = eigen_vectors_t.GetRow(index);

        restore_A += eigen_values(index, 0) * eigen_vector_t.Transpose() * eigen_vector_t;
    }

    EXPECT_EQ(A, restore_A);
}

TEST(MatrixSolverTest, HandmadeEigenCompareEigenLibraryCase) {
    Matrix A{{1, 0, 0}, {0, 2, 0}, {0, 0, -3}};

    Eigen::MatrixXd e_eigen_values{}, e_eigen_vectors{};
    std::tie(e_eigen_values, e_eigen_vectors) = CalculateEigenUsingEigenLib(A);

    EigenSolver solver(A);

    EXPECT_TRUE(e_eigen_values == solver.Eigenvalues()) << "Eigen result\n"
                                                        << e_eigen_values << "\nMathLib result\n"
                                                        << solver.Eigenvalues();

    Matrix eigen_vectors = solver.Eigenvectors();
    for (std::size_t col = 0; col < eigen_vectors.Col(); ++col) {
        Matrix ev = eigen_vectors.GetCol(col);
        Matrix e_ev = MakeMatrixFromEigen(e_eigen_vectors.col(col));

        EXPECT_NEAR(1, std::abs(matrix::Util::CosineSimilarity(ev, e_ev)), 1e-4);
    }
}

TEST(MatrixSolverTest, HandmadeEigenCompareEigenLibrary2Case) {
    Matrix A_{{1, 3, 5}, {1, 7, 9}, {1, 2, 3}};
    Matrix A = A_ + A_.Transpose();

    Eigen::MatrixXd e_eigen_values{}, e_eigen_vectors{};
    std::tie(e_eigen_values, e_eigen_vectors) = CalculateEigenUsingEigenLib(A);

    EigenSolver solver(A, 1e-4);

    EXPECT_TRUE(e_eigen_values == solver.Eigenvalues()) << "Eigen result\n"
                                                        << e_eigen_values << "\nMathLib result\n"
                                                        << solver.Eigenvalues();

    Matrix eigen_vectors = solver.Eigenvectors();
    for (std::size_t col = 0; col < eigen_vectors.Col(); ++col) {
        Matrix ev = eigen_vectors.GetCol(col);
        Matrix e_ev = MakeMatrixFromEigen(e_eigen_vectors.col(col));

        EXPECT_NEAR(1, std::abs(matrix::Util::CosineSimilarity(ev, e_ev)), 1e-4)
            << "\nEigenLibrary: " << e_ev << "\nMathCpp: " << ev;
    }

    Matrix eigen_vectors_t = eigen_vectors.Transpose();
    Matrix eigen_values = solver.Eigenvalues();
    Matrix restore_A(A.Row(), A.Col());

    for (std::size_t index = 0; index < eigen_vectors_t.Row(); ++index) {
        Matrix eigen_vector_t = eigen_vectors_t.GetRow(index);

        restore_A += eigen_values(index, 0) * eigen_vector_t.Transpose() * eigen_vector_t;
    }
    EXPECT_EQ(A, restore_A);
}

TEST(MatrixSolverTest, SVDTrivialCase) {
    Matrix A{{1, 1}, {2, 2}, {2, 0}};

    matrix::SVDSolver solver(A);

    EXPECT_EQ(3, solver.U().Row());
    EXPECT_EQ(3, solver.S().Row());
    EXPECT_EQ(2, solver.S().Col());
    EXPECT_EQ(2, solver.V().Col());

    EXPECT_EQ(A, solver.U() * solver.S() * solver.V().Transpose());
}

TEST(MatrixSolverTest, SVDCompareEigenCase) {
    Matrix A{{1, 1}, {2, 2}, {2, 0}};

    matrix::SVDSolver solver(A);
    auto eigen_result = CalculateSVDUsingEigenLib(A);

    EXPECT_EQ(3, solver.U().Row());
    EXPECT_EQ(3, solver.S().Row());
    EXPECT_EQ(2, solver.S().Col());
    EXPECT_EQ(2, solver.V().Col());

    EXPECT_EQ(A, solver.U() * solver.S() * solver.V().Transpose());

    std::cout << "U\n" << std::get<0>(eigen_result) << "\n";
    std::cout << "D\n" << std::get<1>(eigen_result) << "\n";
    std::cout << "V\n" << std::get<2>(eigen_result) << "\n";
}

}  // namespace test
}  // namespace math_cpp
