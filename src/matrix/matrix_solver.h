/// @file matrix_solver.h
/// @author sangwon (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2022-12-05
///
/// @copyright Copyright (c) 2022
///
///

#ifndef SRC_MATRIX_MATRIX_SOLVER_H_
#define SRC_MATRIX_MATRIX_SOLVER_H_

#include <tuple>
#include <utility>

#include "src/matrix/matrix_core.h"

namespace math_cpp {
namespace matrix {

class EigenSolver {
 public:
    explicit EigenSolver(const Matrix& mat, double epsilon = 1e-5);

    Matrix Eigenvalues() const;
    Matrix Eigenvectors() const;

 private:
    std::pair<Matrix, Matrix> Solve(const Matrix& mat);
    Matrix eigenvalues_{};
    Matrix eigenvectors_{};

    double epsilon_{};
};

/// @brief
/// https://pages.mtu.edu/~struther/Courses/OLD/Other/Sp2012/5627/SVD/Report/Singular%20Value%20Decomposition%20and%20its%20numerical%20computations.pdf
///
/// [U, S, V] = svd(A) -> A = U * S * V'
///
/// D is row vector of eigen values
class SVDSolver {
 public:
    explicit SVDSolver(const Matrix& mat, double epsilon = 1e-5);

    Matrix U() const;
    Matrix V() const;
    Matrix S() const;
    Matrix D() const;

 private:
    std::tuple<Matrix, Matrix, Matrix, Matrix> Solve(const Matrix& A);
    std::tuple<Matrix, Matrix, Matrix> EigenSolverBaseSolve(const Matrix& A);
    Matrix U_{};
    Matrix V_{};
    Matrix S_{};
    Matrix D_{};

    double epsilon_{};
};

}  // namespace matrix
}  // namespace math_cpp
#endif  // SRC_MATRIX_MATRIX_SOLVER_H_
