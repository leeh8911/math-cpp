/// @file matrix_solver.cpp
/// @author sangwon (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2022-12-05
///
/// @copyright Copyright (c) 2022
///
///

#include "src/matrix/matrix_solver.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <utility>

#include "src/matrix/matrix.h"
namespace math_cpp {
namespace matrix {
EigenSolver::EigenSolver(const Matrix& mat, double epsilon) : epsilon_(epsilon) {
    auto eigen = Solve(mat);

    eigenvalues_ = eigen.first;
    eigenvectors_ = eigen.second;
}

Matrix EigenSolver::Eigenvalues() const { return eigenvalues_; }

Matrix EigenSolver::Eigenvectors() const { return eigenvectors_; }

/// @brief Solve eigen problem of input argument matrix.
/// @param mat
/// @return Pair of eigen values and eigen vectors. first is 1D matrix made by eigen values. second is 2D matrix made by
/// eigen vectors. Eigen vectors are column vectors, V = [v1, v2, v3 ...]; Eigen values are 1D row vector, E = [e1, e2,
/// e2 ...];
std::pair<Matrix, Matrix> EigenSolver::Solve(const Matrix& mat) {
    if (mat.Row() != mat.Col()) {
        throw std::invalid_argument("Eigen should be square matrix");
    }

    Matrix result_values(mat.Row(), 1);
    Matrix result_vectors(mat.Row(), mat.Col());

    Matrix eigen_vector(mat.Row(), 1);
    Matrix prev(mat.Row(), 1);

    Matrix A = mat;
    for (std::size_t i = 0; i < mat.Row(); ++i) {
        eigen_vector = Matrix::Random(mat.Row(), 1);
        Matrix A_square = A * A;
        while ((Matrix::Norm2(eigen_vector - prev) > epsilon_)) {
            prev = eigen_vector;

            // Prevent negative eigen value effect(?)
            // If there is negative eigen value, then eigen vector flip direction all iterate, and cannot converge.
            // Therefore, doubly multiply A matrix can prevent this effect, because alway positive!
            eigen_vector = A_square * eigen_vector;

            eigen_vector /= Matrix::Norm2(eigen_vector);
        }

        Matrix eigen_vector_T = eigen_vector.Transpose();
        double eigen_value = static_cast<double>(eigen_vector_T * (A * eigen_vector) / (eigen_vector_T * eigen_vector));

        result_values(i, 0) = eigen_value;
        result_vectors.SetRow(i, eigen_vector);

        A -= eigen_vector * eigen_value * eigen_vector_T;
    }

    return std::make_pair(result_values, result_vectors);
}

SVDSolver::SVDSolver(const Matrix& mat, double epsilon) : epsilon_(epsilon) {
    auto USV = Solve(mat);

    U_ = std::get<0>(USV);
    S_ = std::get<1>(USV);
    V_ = std::get<2>(USV);
}

Matrix SVDSolver::U() const { return U_; }
Matrix SVDSolver::V() const { return V_; }
Matrix SVDSolver::S() const { return S_; }

std::tuple<Matrix, Matrix, Matrix> SVDSolver::Solve(const Matrix& A) {
    std::tuple<Matrix, Matrix, Matrix> result{};

    EigenSolver es_AAT(A * A.Transpose(), epsilon_);
    EigenSolver es_ATA(A.Transpose() * A, epsilon_);

    Matrix U = es_AAT.Eigenvectors();
    Matrix V = es_ATA.Eigenvectors();

    Matrix D(A.Row(), A.Col());
    if (A.Row() < A.Col()) {
        D.Copy(0, 0, Matrix::Diag(Sqrt(es_AAT.Eigenvalues())));
    } else {
        D.Copy(0, 0, Matrix::Diag(Sqrt(es_ATA.Eigenvalues())));
    }
    return std::make_tuple(U, D, V);
}
}  // namespace matrix
}  // namespace math_cpp
