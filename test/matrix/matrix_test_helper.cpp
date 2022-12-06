/// @file matrix_test_helper.cpp
/// @author sangwon (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2022-12-05
///
/// @copyright Copyright (c) 2022
///
///

#include "test/matrix/matrix_test_helper.h"

#include <gtest/gtest.h>

#include <eigen3/Eigen/Dense>
#include <iostream>
#include <stdexcept>

#include "src/matrix/matrix.h"

namespace math_cpp {
namespace test {

using math_cpp::matrix::Matrix;

Eigen::MatrixXd MakeEigen(Matrix mat) {
    Eigen::MatrixXd result(mat.Row(), mat.Col());
    for (std::size_t r = 0; r < mat.Row(); ++r) {
        for (std::size_t c = 0; c < mat.Col(); ++c) {
            result(r, c) = mat(r, c);
        }
    }
    return result;
}
Eigen::MatrixXd MakeRandomEigen(std::size_t row, std::size_t col) {
    Eigen::MatrixXd result = Eigen::MatrixXd::Random(row, col);
    return result;
}

bool operator==(const Matrix& lhs, const Eigen::MatrixXd& rhs) {
    if (lhs.Row() != rhs.rows()) return false;
    if (lhs.Col() != rhs.cols()) return false;

    for (std::size_t r = 0; r < lhs.Row(); ++r) {
        for (std::size_t c = 0; c < lhs.Col(); ++c) {
            if (std::abs(lhs(r, c) - rhs(r, c)) > 1e-4) {
                return false;
            }
        }
    }

    return true;
}

bool operator==(const Eigen::MatrixXd& lhs, const math_cpp::matrix::Matrix& rhs) { return rhs == lhs; }
bool operator!=(const math_cpp::matrix::Matrix& lhs, const Eigen::MatrixXd& rhs) { return !(lhs == rhs); }
bool operator!=(const Eigen::MatrixXd& lhs, const math_cpp::matrix::Matrix& rhs) { return !(rhs == lhs); }
}  // namespace test
}  // namespace math_cpp
