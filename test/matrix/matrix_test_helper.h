/// @file matrix_test_helper.h
/// @author sangwon (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2022-12-05
///
/// @copyright Copyright (c) 2022
///
///

#ifndef TEST_MATRIX_MATRIX_TEST_HELPER_H_
#define TEST_MATRIX_MATRIX_TEST_HELPER_H_

#include <gtest/gtest.h>

#include <eigen3/Eigen/Dense>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "src/matrix/matrix.h"

namespace math_cpp {
namespace test {

Eigen::MatrixXd MakeEigenMatrix(const math_cpp::matrix::Matrix& mat);
std::pair<Eigen::MatrixXd, Eigen::MatrixXd> CalculateEigen(const math_cpp::matrix::Matrix& mat);
Eigen::MatrixXd MakeRandomEigenMatrix(std::size_t row, std::size_t col);

bool operator==(const math_cpp::matrix::Matrix& lhs, const Eigen::MatrixXd& rhs);
bool operator==(const Eigen::MatrixXd& lhs, const math_cpp::matrix::Matrix& rhs);
bool operator!=(const math_cpp::matrix::Matrix& lhs, const Eigen::MatrixXd& rhs);
bool operator!=(const Eigen::MatrixXd& lhs, const math_cpp::matrix::Matrix& rhs);
}  // namespace test
}  // namespace math_cpp

#endif  // TEST_MATRIX_MATRIX_TEST_HELPER_H_
