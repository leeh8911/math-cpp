/// @file matrix_util_test.cpp
/// @author sangwon (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2022-12-07
///
/// @copyright Copyright (c) 2022
///
///

#include "src/matrix/matrix_util.h"

#include <gtest/gtest.h>

#include "src/matrix/matrix.h"

namespace math_cpp {

namespace test {

using matrix::Matrix;
using matrix::Util;

TEST(MatrixUtilTest, CosineSimilarityTrivialCase) {
    Matrix a{{1, 2, 3}};

    EXPECT_EQ(1., MatrixUtil::CosineSimilarity(a, a));
}
TEST(MatrixUtilTest, CosineSimilarityOrthogonalCase) {
    Matrix a{{1, 0, 0}};
    Matrix b{{0, 1, 0}};

    EXPECT_EQ(0., MatrixUtil::CosineSimilarity(a, b));
}
TEST(MatrixUtilTest, CosineSimilarityOppositeCase) {
    Matrix a{{1, 0, 0}};
    Matrix b{{-1, 0, 0}};

    EXPECT_EQ(-1., MatrixUtil::CosineSimilarity(a, b));
}
}  // namespace test
}  // namespace math_cpp
