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

#include <utility>

#include "src/matrix/matrix_core.h"

namespace math_cpp {
namespace matrix {

class EigenSolver {
 public:
    explicit EigenSolver(const Matrix& mat);

    Matrix Eigenvalues() const;
    Matrix Eigenvectors() const;

 private:
    std::pair<Matrix, Matrix> Solve(const Matrix& mat);
    Matrix eigenvalues_{};
    Matrix eigenvectors_{};
};

}  // namespace matrix
}  // namespace math_cpp
#endif  // SRC_MATRIX_MATRIX_SOLVER_H_
