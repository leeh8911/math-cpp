/// @file matrix.h
/// @author sangwon (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2022-11-26
///
/// @copyright Copyright (c) 2022
///
///

#ifndef SRC_MATRIX_MATRIX_H_
#define SRC_MATRIX_MATRIX_H_

#include <iostream>
#include <utility>
#include <vector>

namespace math_cpp {
namespace matrix {
class Matrix {
 public:
    Matrix(std::size_t row, std::size_t col);
    Matrix(const std::initializer_list<std::initializer_list<double>>& l);
    Matrix(const Matrix& other) = default;

    std::size_t Row() const;
    std::size_t Col() const;

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    Matrix operator/(double scalar) const;

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(double scalar);
    Matrix& operator/=(double scalar);

    Matrix& operator-();

    bool operator==(const Matrix& other) const;

    friend Matrix operator*(double scalar, const Matrix& other);

    double& operator()(std::size_t row, std::size_t col);

    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);

    bool IsSameSize(const Matrix& other) const;

 private:
    bool IsBoundedRow(std::size_t row);
    bool IsBoundedCol(std::size_t col);
    std::vector<double> TransposeData(std::vector<double> src);
    std::size_t row_{};
    std::size_t col_{};
    std::vector<double> data_{};
};
}  // namespace matrix

}  // namespace math_cpp
#endif  // SRC_MATRIX_MATRIX_H_
