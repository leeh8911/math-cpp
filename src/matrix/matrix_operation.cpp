/// @file matrix_operation.cpp
/// @author sangwon (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2022-12-08
///
/// @copyright Copyright (c) 2022
///
///

#include "src/matrix/matrix_operation.h"

#include "src/matrix/matrix_core.h"

namespace math_cpp {
namespace matrix {

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
    Matrix result = lhs;
    result += rhs;

    return result;
}

Matrix operator-(const Matrix& lhs, const Matrix& rhs) {
    Matrix result = lhs;
    result -= rhs;

    return result;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
    if (!lhs.CanMultiply(rhs)) {
        throw std::invalid_argument("cannot matrix multiply, check size!");
    }

    Matrix result(lhs.Row(), rhs.Col());

    for (std::size_t r = 0; r < result.Row(); ++r) {
        for (std::size_t c = 0; c < result.Col(); ++c) {
            for (std::size_t m = 0; m < lhs.Col(); ++m) {
                result(r, c) += lhs(r, m) * rhs(m, c);
            }
        }
    }
    return result;
}

Matrix operator/(const Matrix& lhs, const Matrix& rhs) {
    Matrix inv_rhs = rhs.Inverse();

    return (lhs * inv_rhs);
}

Matrix operator+(double scalar, const Matrix& rhs) {
    Matrix scalar_matrix(rhs.Row(), rhs.Col(), scalar);

    return (scalar_matrix + rhs);
}

Matrix operator-(double scalar, const Matrix& rhs) {
    Matrix scalar_matrix(rhs.Row(), rhs.Col(), scalar);

    return (scalar_matrix - rhs);
}

Matrix operator*(double scalar, const Matrix& rhs) {
    Matrix result(rhs);

    result *= scalar;

    return result;
}

Matrix operator/(double scalar, const Matrix& rhs) {
    Matrix result = rhs.Inverse();

    result *= scalar;

    return result;
}

Matrix operator+(const Matrix& lhs, double scalar) { return scalar + lhs; }

Matrix operator-(const Matrix& lhs, double scalar) { return (-scalar) + lhs; }

Matrix operator/(const Matrix& lhs, double scalar) { return lhs * (1.0 / scalar); }

Matrix operator*(const Matrix& lhs, double scalar) { return scalar * lhs; }

}  // namespace matrix
}  // namespace math_cpp
