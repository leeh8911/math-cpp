/// @file matrix_util.h
/// @author sangwon (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2022-12-07
///
/// @copyright Copyright (c) 2022
///

#ifndef SRC_MATRIX_MATRIX_UTIL_H_
#define SRC_MATRIX_MATRIX_UTIL_H_

#include "src/matrix/matrix_core.h"

namespace math_cpp {
namespace matrix {
class MatrixUtil {
 public:
    static double CosineSimilarity(const Matrix& lhs, const Matrix& rhs);
};
}  // namespace matrix
}  // namespace math_cpp

#endif  // SRC_MATRIX_MATRIX_UTIL_H_
