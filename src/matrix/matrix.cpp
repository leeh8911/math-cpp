/// @file matrix.cpp
/// @author sangwon (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2022-11-26
///
/// @copyright Copyright (c) 2022
///
///

#include "matrix/matrix.h"

#include <stdexcept>
#include <string>

namespace math_cpp {
namespace matrix {

// using std::string_literals::operator""s;

Matrix::Matrix(std::size_t row, std::size_t col) : row_(row), col_(col), data_(std::vector<double>(row * col, 0.0)) {}

Matrix::Matrix(const std::initializer_list<std::initializer_list<double>>& l) : row_{}, col_{}, data_{} {
    for (auto row : l) {
        ++row_;
        data_.insert(data_.end(), row.begin(), row.end());
    }

    col_ = data_.size() / row_;
}

std::size_t Matrix::Row() const { return row_; }
std::size_t Matrix::Col() const { return col_; }

Matrix& Matrix::operator+=(const Matrix& other) {
    if (!IsSameSize(other)) {
        std::string throw_msg =
            "other matrix must be same size [*this] (" + std::to_string(row_) + ", " + std::to_string(col_) + ")!";
        throw std::invalid_argument(throw_msg);
    }

    auto this_it = data_.begin();
    auto other_it = other.data_.begin();
    for (; this_it != data_.end(); ++this_it, ++other_it) {
        *this_it += *other_it;
    }

    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const {
    Matrix add = *this;

    add += other;
    return add;
}

double& Matrix::operator()(std::size_t row, std::size_t col) {
    if (!IsBoundedRow(row)) {
        std::string throw_msg =
            "row must be greater or equal than 0 and less or equal than " + std::to_string(row_) + "!";
        throw std::invalid_argument(throw_msg);
    }
    if (!IsBoundedCol(col)) {
        std::string throw_msg =
            "col must be greater or equal than 0 and less or equal than " + std::to_string(col_) + "!";
        throw std::invalid_argument(throw_msg);
    }
    return data_[row * col_ + col];
}

Matrix Matrix::operator/(double scalar) const {
    Matrix result = *this;
    result /= scalar;
    return result;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    *this += -Matrix(other);
    return *this;
}

Matrix& Matrix::operator/=(double scalar) {
    if (scalar == 0) {
        throw std::invalid_argument("scalar must be not 0(ZERO)!");
    }
    *this *= (1 / scalar);
    return *this;
}

Matrix Matrix::operator-(const Matrix& other) const {
    Matrix result = *this;
    result -= other;
    return result;
}

Matrix& Matrix::operator-() {
    *this *= -1.0;
    return *this;
}

bool Matrix::operator==(const Matrix& other) const {
    bool equal = true;
    if (!IsSameSize(other)) {
        equal = false;
    } else {
        auto this_it = data_.begin();
        auto other_it = other.data_.begin();
        for (; this_it != data_.end(); ++this_it, ++other_it) {
            if (*this_it != *other_it) {
                equal = false;
                break;
            }
        }
    }
    return equal;
}

Matrix operator*(double scalar, const Matrix& other) { return other * scalar; }

Matrix Matrix::operator*(double scalar) const {
    Matrix scalar_mult = *this;
    scalar_mult *= scalar;

    return scalar_mult;
}

Matrix& Matrix::operator*=(double scalar) {
    auto this_it = data_.begin();
    for (; this_it != data_.end(); ++this_it) {
        *this_it *= scalar;
    }
    return *this;
}

bool Matrix::IsSameSize(const Matrix& other) const { return (row_ == other.row_) && (col_ == other.col_); }

bool Matrix::IsBoundedRow(std::size_t row) { return (row <= row_); }

bool Matrix::IsBoundedCol(std::size_t col) { return (col <= col_); }

std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
    os << mat.Row() << ", " << mat.Col();

    return os;
}
}  // namespace matrix

}  // namespace math_cpp
