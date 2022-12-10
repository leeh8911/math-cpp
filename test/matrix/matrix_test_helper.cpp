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

#include <Eigen/Dense>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <vector>

#include "src/matrix/matrix.h"

namespace math_cpp {
namespace test {

using math_cpp::matrix::Matrix;

Eigen::MatrixXd MakeEigenMatrix(const Matrix& mat) {
    Eigen::MatrixXd result(mat.Row(), mat.Col());
    for (std::size_t r = 0; r < mat.Row(); ++r) {
        for (std::size_t c = 0; c < mat.Col(); ++c) {
            result(r, c) = mat(r, c);
        }
    }
    return result;
}

std::pair<Eigen::MatrixXd, Eigen::MatrixXd> CalculateEigenUsingEigenLib(const Matrix& mat) {
    Eigen::MatrixXd eigen_mat = MakeEigenMatrix(mat);

    Eigen::EigenSolver<decltype(eigen_mat)> solver(eigen_mat);

    Eigen::MatrixXd eigenvalues = solver.eigenvalues().real();
    Eigen::MatrixXd eigenvectors = solver.eigenvectors().real();

    std::vector<std::pair<std::size_t, double>> v{};

    for (std::size_t i = 0; i < eigenvalues.rows(); ++i) {
        v.emplace_back(i, eigenvalues(i, 0));
    }

    std::sort(std::begin(v), std::end(v), [](std::pair<std::size_t, double>& a, std::pair<std::size_t, double>& b) {
        return std::abs(a.second) > std::abs(b.second);
    });

    Eigen::MatrixXd temp_eigenvalues = eigenvalues;
    Eigen::MatrixXd temp_eigenvectors = eigenvectors;
    for (std::size_t i = 0; i < eigenvalues.rows(); ++i) {
        temp_eigenvalues(i, 0) = v[i].second;
        temp_eigenvectors.col(i) = eigenvectors.col(v[i].first);
    }

    return std::make_pair(temp_eigenvalues, temp_eigenvectors);
}

std::tuple<Eigen::MatrixXd, Eigen::MatrixXd, Eigen::MatrixXd> CalculateSVDUsingEigenLib(const Matrix& mat) {
    Eigen::MatrixXd eigen_mat = MakeEigenMatrix(mat);

    Eigen::JacobiSVD<Eigen::MatrixXd> svd;
    svd.compute(eigen_mat, Eigen::ComputeFullU | Eigen::ComputeFullV);

    return std::make_tuple(svd.matrixU(), svd.singularValues(), svd.matrixV());
}

matrix::Matrix MakeMatrixFromEigen(const Eigen::MatrixXd& mat) {
    matrix::Matrix result(mat.rows(), mat.cols());

    for (size_t r = 0; r < result.Row(); ++r) {
        for (size_t c = 0; c < result.Col(); ++c) {
            result(r, c) = mat(r, c);
        }
    }

    return result;
}

Eigen::MatrixXd MakeRandomEigenMatrix(std::size_t row, std::size_t col) {
    Eigen::MatrixXd result = Eigen::MatrixXd::Random(row, col);
    return result;
}

bool IsSimilarUsingColumnWiseCosineSimilarity(const Eigen::MatrixXd eigen, const matrix::Matrix& mathcpp) {
    if ((eigen.rows() != mathcpp.Row()) && (eigen.cols() != mathcpp.Col())) {
        return false;
    }

    for (std::size_t c = 0; c < mathcpp.Col(); ++c) {
        matrix::Matrix e_col = MakeMatrixFromEigen(eigen.col(c));
        matrix::Matrix c_col = mathcpp.GetCol(c);

        if (std::abs(std::abs(matrix::Util::CosineSimilarity(e_col, c_col)) - 1) > 1e-4) {
            return false;
        }
    }
    return true;
}

bool operator==(const Matrix& lhs, const Eigen::MatrixXd& rhs) {
    if (lhs.Row() != rhs.rows()) return false;
    if (lhs.Col() != rhs.cols()) return false;

    for (std::size_t r = 0; r < lhs.Row(); ++r) {
        for (std::size_t c = 0; c < lhs.Col(); ++c) {
            if (std::abs(lhs(r, c) - rhs(r, c)) > 1e-4) {
                return false;
            }
        }
    }

    return true;
}

bool operator==(const Eigen::MatrixXd& lhs, const math_cpp::matrix::Matrix& rhs) { return rhs == lhs; }
bool operator!=(const math_cpp::matrix::Matrix& lhs, const Eigen::MatrixXd& rhs) { return !(lhs == rhs); }
bool operator!=(const Eigen::MatrixXd& lhs, const math_cpp::matrix::Matrix& rhs) { return !(rhs == lhs); }
}  // namespace test
}  // namespace math_cpp
