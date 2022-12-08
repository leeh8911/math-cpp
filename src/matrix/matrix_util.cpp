/// @file matrix_util.cpp
/// @author sangwon (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2022-12-07
///
/// @copyright Copyright (c) 2022
///
///

#include "src/matrix/matrix_util.h"

#include <stdexcept>

#include "src/matrix/matrix.h"

namespace math_cpp {
namespace matrix {
double MatrixUtil::CosineSimilarity(const Matrix& lhs, const Matrix& rhs) {
    if ((lhs.Row() != 1) && (lhs.Col() != 1)) {
        throw std::invalid_argument("lhs should row/col vector");
    }
    if ((rhs.Row() != 1) && (rhs.Col() != 1)) {
        throw std::invalid_argument("rhs should row/col vector");
    }

    Matrix lhs_ = lhs;
    Matrix rhs_ = rhs;
    if (lhs.Col() == 1) {
        lhs_ = lhs.Transpose();
    }
    if (rhs.Row() == 1) {
        rhs_ = rhs.Transpose();
    }

    double result = lhs_ * rhs_;
    result /= Matrix::Norm2(lhs_) * Matrix::Norm2(rhs_);
    return result;
}

}  // namespace matrix
}  // namespace math_cpp
