/// @file matrix.cpp
/// @author sangwon (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2022-11-26
///
/// @copyright Copyright (c) 2022
///

#include "src/matrix/matrix.h"

#include <algorithm>
#include <cstdlib>
#include <limits>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "src/random/random.h"

namespace math_cpp {
namespace matrix {

// using std::string_literals::operator""s;

Matrix::Matrix(std::size_t row, std::size_t col) : data_(std::vector<double>(row * col, 0.0)), row_(row), col_(col) {}
Matrix::Matrix(const Shape& shape) : Matrix(shape.first, shape.second) {}

Matrix::Matrix(const std::initializer_list<std::initializer_list<double>>& l) : data_{}, row_{}, col_{} {
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
    if (!IsBoundedSize(row, col)) {
        std::string throw_msg =
            "shape should be less or equal to <" + std::to_string(row_) + ", " + std::to_string(col_) + ">!";
        throw std::invalid_argument(throw_msg);
    }
    return data_[row * col_ + col];
}

double Matrix::operator()(std::size_t row, std::size_t col) const {
    if (!IsBoundedSize(row, col)) {
        std::string throw_msg =
            "shape should be less or equal to <" + std::to_string(row_) + ", " + std::to_string(col_) + ">!";
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

Matrix Matrix::operator*(const Matrix& other) const {
    if (!CanMultiply(other)) {
        throw std::invalid_argument("cannot matrix multiply, check size!");
    }

    Matrix result(row_, other.col_);

    for (std::size_t r = 0; r < row_; ++r) {
        for (std::size_t c = 0; c < other.col_; ++c) {
            for (std::size_t m = 0; m < col_; ++m) {
                result(r, c) += (*this)(r, m) * other(m, c);
            }
        }
    }
    return result;
}

bool Matrix::operator==(const Matrix& other) const {
    bool equal = true;
    if (!IsSameSize(other)) {
        equal = false;
    } else {
        auto this_it = data_.begin();
        auto other_it = other.data_.begin();
        for (; this_it != data_.end(); ++this_it, ++other_it) {
            // TODO(sangwon) : How to compare to floating point values.. (there is so many errors..)
            // below code is just assigned magic number (1e-8). not designed value.
            if (std::abs(*this_it - *other_it) > 1e-4) {
                equal = false;
                break;
            }
        }
    }
    return equal;
}

bool Matrix::operator!=(const Matrix& other) const { return !(*this == other); }

Matrix Matrix::Inverse() const {
    if (row_ != col_) {
        throw std::invalid_argument("matrix should be square");
    }

    Matrix eye = Identity(row_);
    Matrix cat = Concatenate(*this, eye, 1);

    // Gauss Elimination
    for (std::size_t i = 0; i < row_ - 1; ++i) {
        cat.RowMult(i, 1 / cat(i, i));
        Matrix row_matrix = cat.GetRow(i);

        for (std::size_t j = i + 1; j < row_; ++j) {
            Matrix temporal_row = row_matrix * (-cat(j, i));
            cat.RowAdd(j, temporal_row);
        }
    }

    // Jordan Elimination
    for (std::size_t i = row_ - 1; i > 0; --i) {
        cat.RowMult(i, 1 / cat(i, i));
        Matrix row_matrix = cat.GetRow(i);

        for (std::size_t j = i - 1; j != std::numeric_limits<std::size_t>::max(); --j) {
            Matrix temporal_row = row_matrix * (-cat(j, i));
            cat.RowAdd(j, temporal_row);
        }
    }

    Matrix result = cat.GetSubMatrix(0, col_);

    return result;
}

Matrix Matrix::Transpose() const {
    Matrix result(col_, row_);
    for (std::size_t row = 0; row < row_; ++row) {
        for (std::size_t col = 0; col < col_; ++col) {
            result(col, row) = (*this)(row, col);
        }
    }
    return result;
}

std::pair<Matrix, Matrix> Matrix::Eigen() const {
    // TODO(sangwon) : to be update
    if (row_ != col_) {
        throw std::invalid_argument("Eigen should be square matrix");
    }

    Matrix result_values(row_, 1);
    Matrix result_vectors(row_, col_);

    Matrix eigen_vector(row_, 1);
    Matrix prev(row_, 1);
    double eps = 1e-4;
    std::size_t count = 0;
    Matrix A = (*this);
    for (std::size_t i = 0; i < row_; ++i) {
        eigen_vector = Random(row_, 1);
        while ((Norm2(eigen_vector - prev) > eps)) {
            prev = eigen_vector;

            // Prevent negative eigen value effect(?)
            // If there is negative eigen value, then eigen vector flip direction all iterate, and cannot converge.
            // Therefore, doubly multiply A matrix can prevent this effect, because alway positive!
            eigen_vector = A * A * eigen_vector;

            eigen_vector /= Norm2(eigen_vector);

            if (count++ > 10) {
                break;
            }
        }

        Matrix eigen_vector_T = eigen_vector.Transpose();
        double eigen_value = eigen_vector_T * (A * eigen_vector) / (eigen_vector_T * eigen_vector);

        result_values(i, 0) = eigen_value;
        result_vectors.SetRow(i, eigen_vector);

        A -= eigen_vector * eigen_value * eigen_vector_T;
    }

    return std::make_pair(result_values, result_vectors);
}

Matrix& Matrix::Absolute() {
    std::transform(std::begin(data_), std::end(data_), std::begin(data_), [](double& elm) { return std::abs(elm); });

    return *this;
}

double Matrix::Determinant(const Matrix& mat) {
    if (mat.row_ != mat.col_) {
        throw std::invalid_argument("determinant should be defined square matrix");
    }
    if ((mat.row_ == 2) && (mat.col_ == 2)) {
        return mat(0, 0) * mat(1, 1) - mat(1, 0) * mat(0, 1);
    }

    std::size_t r = 0, c = 0;
    int8_t sign = 1;
    double det = 0.0;
    for (c = 0; c < mat.col_; ++c) {
        double sub_det = sign * mat(r, c) * Determinant(EraseRowCol(mat, r, c));
        sign *= -1;

        det += sub_det;
    }

    return det;
}

Matrix Matrix::EraseRowCol(const Matrix& mat, std::size_t row, std::size_t col) {
    Matrix result(mat.row_ - 1, mat.col_ - 1);
    std::size_t rr = 0, cc = 0;
    for (std::size_t r = 0; r < mat.row_; ++r) {
        cc = 0;
        for (std::size_t c = 0; c < mat.col_; ++c) {
            if ((r != row) && (c != col)) {
                result(rr, cc++) = mat(r, c);
            }
        }
        if (r != row) rr++;
    }
    return result;
}

Matrix::operator double() {
    if ((row_ != 1) || (col_ != 1)) {
        throw std::invalid_argument("Matrix to double type casting should be 1 x 1 size matrix");
    }

    return (*this)(0, 0);
}

Matrix& Matrix::RowMult(std::size_t idx, double scalar) {
    if (idx >= row_) {
        throw std::invalid_argument("check row index");
    }
    auto start = std::next(std::begin(data_), static_cast<std::ptrdiff_t>(idx * col_));
    auto finish = std::next(start, static_cast<std::ptrdiff_t>(col_));

    std::transform(start, finish, start, [scalar](double elm) { return elm * scalar; });

    return *this;
}

Matrix& Matrix::RowAdd(std::size_t idx, const Matrix& row) {
    if (col_ != row.col_) {
        throw std::invalid_argument("check column size");
    }
    if (idx >= row_) {
        throw std::invalid_argument("check row index");
    }
    auto start = std::next(std::begin(data_), static_cast<std::ptrdiff_t>(idx * col_));
    auto finish = std::next(start, static_cast<std::ptrdiff_t>(col_));
    auto row_start = std::cbegin(row.data_);

    std::transform(start, finish, start, [&row_start](double elm) { return elm + (*(row_start++)); });

    return *this;
}

Matrix Matrix::GetRow(std::size_t idx) const {
    if (idx >= row_) {
        throw std::invalid_argument("check row index");
    }

    Matrix row_matrix(1, col_);

    auto start = std::next(std::begin(data_), static_cast<std::ptrdiff_t>(idx * col_));
    auto finish = std::next(start, static_cast<std::ptrdiff_t>(col_));
    auto row_start = std::begin(row_matrix.data_);
    std::copy(start, finish, row_start);

    return row_matrix;
}

Matrix& Matrix::SetRow(std::size_t idx, const Matrix& src) {
    if (src.col_ != 1) {
        throw std::invalid_argument("Set row method can accept row vector");
    }
    if (row_ != src.row_) {
        throw std::invalid_argument("Set row method should be same row");
    }

    Matrix transposed_this = (*this).Transpose();
    auto start = std::begin(transposed_this.data_);

    std::copy(std::begin(src.data_), std::end(src.data_), std::next(start, static_cast<std::ptrdiff_t>(idx * col_)));

    *this = transposed_this.Transpose();
    return *this;
}

Matrix Matrix::GetSubMatrix(std::size_t start_row, std::size_t start_col) {
    Matrix result(row_ - start_row, col_ - start_col);

    std::size_t target_row = 0;
    for (std::size_t row = start_row; row < row_; ++row, ++target_row) {
        std::size_t target_col = 0;
        for (std::size_t col = start_col; col < col_; ++col, ++target_col) {
            result(target_row, target_col) = (*this)(row, col);
        }
    }
    return result;
}

Matrix operator*(double scalar, const Matrix& other) { return other * scalar; }

Matrix Matrix::operator*(double scalar) const {
    Matrix scalar_mult = *this;
    scalar_mult *= scalar;

    return scalar_mult;
}

Matrix& Matrix::operator*=(double scalar) {
    auto start = std::begin(data_);
    auto finish = std::end(data_);
    std::transform(start, finish, start, [&scalar](double& elm) { return elm * scalar; });

    return *this;
}

bool Matrix::IsSameSize(const Matrix& other) const { return (row_ == other.row_) && (col_ == other.col_); }

bool Matrix::CanMultiply(const Matrix& other) const { return (col_ == other.row_); }

Matrix& Matrix::Copy(std::size_t start_row, std::size_t start_col, const Matrix& other) {
    for (std::size_t r = 0; r < other.row_; ++r) {
        for (std::size_t c = 0; c < other.col_; ++c) {
            (*this)(r + start_row, c + start_col) = other(r, c);
        }
    }

    return *this;
}

Matrix Matrix::Concatenate(const Matrix& lhs, const Matrix& rhs, std::size_t axis) {
    Matrix result{};

    if (axis == 0) {
        if (lhs.col_ != rhs.col_) {
            throw std::invalid_argument("check matrix size!");
        }
        Matrix row_concat(lhs.row_ + rhs.row_, lhs.col_);

        row_concat.Copy(0, 0, lhs);
        row_concat.Copy(lhs.row_, 0, rhs);

        result = row_concat;
    } else if (axis == 1) {
        if (lhs.row_ != rhs.row_) {
            throw std::invalid_argument("check matrix size!");
        }
        Matrix col_concat(lhs.row_, lhs.col_ + rhs.col_);

        col_concat.Copy(0, 0, lhs);
        col_concat.Copy(0, lhs.col_, rhs);

        result = col_concat;
    }

    return result;
}

Matrix Matrix::Identity(std::size_t size) {
    Matrix result(size, size);
    for (std::size_t index = 0; index < size; ++index) {
        result(index, index) = 1.0;
    }

    return result;
}

Matrix Matrix::Random(std::size_t row, std::size_t col) {
    Matrix result(row, col);

    random::Random instance = random::Random::GetInstance();
    for (auto& elm : result.data_) {
        elm = instance.Gaussian();
    }

    return result;
}

double Matrix::Norm2(const Matrix& mat) {
    double result = 0.0;
    for (auto elm : mat.data_) {
        result += elm * elm;
    }
    return std::sqrt(result);
}

bool Matrix::IsBoundedRow(std::size_t row) const { return (row <= row_); }

bool Matrix::IsBoundedCol(std::size_t col) const { return (col <= col_); }

bool Matrix::IsBoundedSize(std::size_t row, std::size_t col) const { return IsBoundedRow(row) && IsBoundedCol(col); }

std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
    os << "[\n";
    for (std::size_t r = 0; r < mat.row_; ++r) {
        os << "[";
        for (std::size_t c = 0; c < mat.col_; ++c) {
            os << mat(r, c) << " ";
        }
        os << "]\n";
    }
    os << "]";

    return os;
}
}  // namespace matrix
}  // namespace math_cpp