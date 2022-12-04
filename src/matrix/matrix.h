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
    using Shape = std::pair<std::size_t, std::size_t>;
    Matrix() = default;
    explicit Matrix(const Shape& shape);
    explicit Matrix(std::size_t row, std::size_t col);
    Matrix(const std::initializer_list<std::initializer_list<double>>& l);
    Matrix(const Matrix& other) = default;

    std::size_t Row() const;
    std::size_t Col() const;

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    Matrix operator/(double scalar) const;

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(double scalar);
    Matrix& operator/=(double scalar);

    Matrix& operator-();

    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

    Matrix Inverse() const;
    Matrix Transpose() const;
    std::pair<Matrix, Matrix> Eigen() const;

    Matrix& Absolute();

    Matrix& RowMult(std::size_t idx, double scalar);
    Matrix& RowAdd(std::size_t idx, const Matrix& row);
    Matrix GetRow(std::size_t idx) const;
    Matrix& SetRow(std::size_t idx, const Matrix& src);
    Matrix GetSubMatrix(std::size_t start_row, std::size_t start_col);

    friend Matrix operator*(double scalar, const Matrix& other);

    double& operator()(std::size_t row, std::size_t col);
    double operator()(std::size_t row, std::size_t col) const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);

    bool IsSameSize(const Matrix& other) const;
    bool CanMultiply(const Matrix& other) const;

    Matrix& Copy(std::size_t start_row, std::size_t start_col, const Matrix& other);

    static Matrix Concatenate(const Matrix& lhs, const Matrix& rhs, std::size_t axis = 0);
    static Matrix Identity(std::size_t size);
    static Matrix Random(std::size_t row, std::size_t col);

    static double Norm2(const Matrix& mat);
    static double Determinant(const Matrix& mat);
    static Matrix EraseRowCol(const Matrix& mat, std::size_t row, std::size_t col);

    operator double();

 private:
    bool IsBoundedRow(std::size_t row) const;
    bool IsBoundedCol(std::size_t col) const;
    bool IsBoundedSize(std::size_t row, std::size_t col) const;
    std::vector<double> data_{};
    std::size_t row_{};
    std::size_t col_{};
};
}  // namespace matrix

}  // namespace math_cpp
#endif  // SRC_MATRIX_MATRIX_H_
