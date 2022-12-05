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

#include "src/matrix/matrix.h"

namespace math_cpp {
namespace test {

Eigen::MatrixXd MakeEigen(math_cpp::matrix::Matrix mat);
Eigen::MatrixXd MakeRandomEigen(std::size_t row, std::size_t col);

}  // namespace test
}  // namespace math_cpp

#endif  // TEST_MATRIX_MATRIX_TEST_HELPER_H_
