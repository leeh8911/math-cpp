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

namespace math_cpp {
namespace matrix {
EigenSolver::EigenSolver(const Matrix& mat) {
    auto eigen = Solve(mat);

    eigenvalues_ = eigen.first;
    eigenvectors_ = eigen.second;
}

Matrix EigenSolver::Eigenvalues() const { return eigenvalues_; }

Matrix EigenSolver::Eigenvectors() const { return eigenvectors_; }

/// @brief
/// @param mat
/// @return Pair of eigen values and eigen vectors. first is 1D matrix made by eigen values. second is 2D matrix made by
/// eigen vectors. Eigen vectors are column vectors, V = [v1, v2, v3 ...]; Eigen values are 1D row vector, E = [e1, e2,
/// e2 ...];
std::pair<Matrix, Matrix> EigenSolver::Solve(const Matrix& mat) {
    // TODO(sangwon) : to be update
    if (mat.Row() != mat.Col()) {
        throw std::invalid_argument("Eigen should be square matrix");
    }

    Matrix result_values(mat.Row(), 1);
    Matrix result_vectors(mat.Row(), mat.Col());

    Matrix eigen_vector(mat.Row(), 1);
    Matrix prev(mat.Row(), 1);
    double eps = 1e-5;
    Matrix A = mat;
    for (std::size_t i = 0; i < mat.Row(); ++i) {
        eigen_vector = Matrix::Random(mat.Row(), 1);
        while ((Matrix::Norm2(eigen_vector - prev) > eps)) {
            prev = eigen_vector;

            // Prevent negative eigen value effect(?)
            // If there is negative eigen value, then eigen vector flip direction all iterate, and cannot converge.
            // Therefore, doubly multiply A matrix can prevent this effect, because alway positive!
            eigen_vector = A * A * eigen_vector;

            std::cout << Matrix::Norm2(eigen_vector) << "\n";
            eigen_vector /= Matrix::Norm2(eigen_vector);
        }

        Matrix eigen_vector_T = eigen_vector.Transpose();
        double eigen_value = eigen_vector_T * (A * eigen_vector) / (eigen_vector_T * eigen_vector);

        result_values(i, 0) = eigen_value;
        result_vectors.SetRow(i, eigen_vector);

        A -= eigen_vector * eigen_value * eigen_vector_T;
    }

    return std::make_pair(result_values, result_vectors);
}
}  // namespace matrix
}  // namespace math_cpp
