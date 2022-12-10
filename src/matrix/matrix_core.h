/// @file matrix_core.h
/// @author sangwon (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2022-11-26
///
/// @copyright Copyright (c) 2022
///
///

#ifndef SRC_MATRIX_MATRIX_CORE_H_
#define SRC_MATRIX_MATRIX_CORE_H_

#include <iostream>
#include <utility>
#include <vector>

namespace math_cpp {
namespace matrix {

enum MatrixDir { kRow, kCol };
class Matrix {
 public:
    using Shape = std::pair<std::size_t, std::size_t>;
    explicit Matrix(const Shape& shape);
    explicit Matrix(std::size_t row, std::size_t col);
    explicit Matrix(std::size_t row, std::size_t col, double value);
    Matrix(const std::initializer_list<std::initializer_list<double>>& l);

    Matrix() = default;
    Matrix(const Matrix& other) = default;
    Matrix(Matrix&& other) = default;
    Matrix& operator=(const Matrix& other) = default;
    Matrix& operator=(Matrix&& other);

    std::size_t Row() const;
    std::size_t Col() const;

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(double scalar);
    Matrix& operator/=(double scalar);

    Matrix& operator-();

    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

    Matrix Inverse() const;
    Matrix Transpose() const;
    Matrix Diagonal() const;

    double Sum() const;
    double Prod() const;
    double Mean() const;
    double MinCoeff() const;
    double MaxCoeff() const;
    double Trace() const;

    Matrix& Absolute();

    Matrix& RowMult(std::size_t idx, double scalar);
    Matrix& RowAdd(std::size_t idx, const Matrix& row);
    Matrix GetCol(std::size_t idx) const;
    Matrix GetRow(std::size_t idx) const;
    Matrix& SetCol(std::size_t idx, const Matrix& src);
    Matrix& SetRow(std::size_t idx, const Matrix& src);
    Matrix GetSubMatrix(std::size_t start_row, std::size_t start_col);

    double& operator()(std::size_t row, std::size_t col);
    double operator()(std::size_t row, std::size_t col) const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);

    bool IsSameSize(const Matrix& other) const;
    bool CanMultiply(const Matrix& other) const;

    Matrix& Copy(std::size_t start_row, std::size_t start_col, const Matrix& other);

    void Swap(Matrix& other);
    void Swap(Matrix&& other);

    static Matrix Concatenate(const Matrix& lhs, const Matrix& rhs, MatrixDir axis = MatrixDir::kRow);
    static Matrix Identity(std::size_t size);
    static Matrix Diag(const Matrix& vec);
    static Matrix Random(std::size_t row, std::size_t col);

    static double Norm2(const Matrix& mat);
    static double Determinant(const Matrix& mat);
    static Matrix EraseRowCol(const Matrix& mat, std::size_t row, std::size_t col);

    static Matrix Zeros(const Matrix& mat);

    explicit operator double();

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
#endif  // SRC_MATRIX_MATRIX_CORE_H_
