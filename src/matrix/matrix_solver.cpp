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
    auto USVT = Solve(mat);

    U_ = std::get<0>(USVT);
    S_ = std::get<1>(USVT);
    V_ = std::get<2>(USVT).Transpose();
}

Matrix SVDSolver::U() const { return U_; }
Matrix SVDSolver::V() const { return V_; }
Matrix SVDSolver::S() const { return S_; }

Matrix GramSchmidt(const Matrix& A) {
    std::size_t n = A.Row();
    std::size_t m = A.Col();

    Matrix Q1(n, m);
    Q1.SetCol(0, A.GetCol(0));

    return Q1;
}

std::tuple<Matrix, Matrix, Matrix> SVDSolver::Solve(const Matrix& mat) {
    std::tuple<Matrix, Matrix, Matrix> result{};
    Matrix U_(mat.Row(), mat.Row());
    Matrix S_(mat.Row(), mat.Col());
    Matrix V_(mat.Col(), mat.Col());

    return result;
}
}  // namespace matrix
}  // namespace math_cpp
