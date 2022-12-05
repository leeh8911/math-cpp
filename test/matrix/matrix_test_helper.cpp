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
Eigen::MatrixXd MakeEigen(math_cpp::matrix::Matrix mat) {
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
}  // namespace test
}  // namespace math_cpp
