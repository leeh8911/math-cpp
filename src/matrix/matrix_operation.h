/// @file matrix_operation.h
/// @author sangwon (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2022-12-08
///
/// @copyright Copyright (c) 2022
///
///
#ifndef SRC_MATRIX_MATRIX_OPERATION_H_
#define SRC_MATRIX_MATRIX_OPERATION_H_

#include "src/matrix/matrix_core.h"

namespace math_cpp {
namespace matrix {
Matrix operator+(const Matrix& lhs, const Matrix& rhs);
Matrix operator-(const Matrix& lhs, const Matrix& rhs);
Matrix operator*(const Matrix& lhs, const Matrix& rhs);
Matrix operator/(const Matrix& lhs, const Matrix& rhs);

Matrix operator+(double scalar, const Matrix& rhs);
Matrix operator-(double scalar, const Matrix& rhs);
Matrix operator*(double scalar, const Matrix& rhs);
Matrix operator/(double scalar, const Matrix& rhs);

Matrix operator+(const Matrix& lhs, double scalar);
Matrix operator-(const Matrix& lhs, double scalar);
Matrix operator*(const Matrix& lhs, double scalar);
Matrix operator/(const Matrix& lhs, double scalar);

Matrix Sqrt(const Matrix& src);
}  // namespace matrix
}  // namespace math_cpp

#endif  // SRC_MATRIX_MATRIX_OPERATION_H_
