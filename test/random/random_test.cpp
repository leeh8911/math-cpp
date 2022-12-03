/// @file random_test.cpp
/// @author sangwon (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2022-12-03
///
/// @copyright Copyright (c) 2022
///
///

#include "src/random/random.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

namespace math_cpp {

namespace test {

using namespace random;  // NOLINT

double Mean(const std::vector<double>& src) {
    double result = std::accumulate(std::begin(src), std::end(src), 0.0);

    return result / static_cast<double>(src.size());
}

double Variance(const std::vector<double>& src) {
    double result = 0;
    std::vector<double> other{};
    other.reserve(src.size());

    double mean = Mean(src);
    std::transform(std::begin(src), std::end(src), std::back_inserter(other),
                   [mean](double elm) { return std::pow(elm - mean, 2); });

    result = Mean(other);
    return result;
}

double StandardDeviation(const std::vector<double>& src) { return std::sqrt(Variance(src)); }

std::ostream& operator<<(std::ostream& os, const std::vector<double>& src) {
    os << "<";
    for (auto& elm : src) {
        os << elm << " ";
    }
    os << ">";
    return os;
}

TEST(RandomTest, UniformCase) {
    Random generator = Random::GetInstance();

    std::size_t max_iter = 100;
    std::vector<double> values{};
    values.reserve(max_iter);

    while (values.size() < max_iter) {
        values.emplace_back(generator.Uniform());
    }

    double min_value = *std::min_element(std::begin(values), std::end(values));
    double max_value = *std::max_element(std::begin(values), std::end(values));

    EXPECT_LE(0, min_value);
    EXPECT_LE(max_value, 1);
}

TEST(RandomTest, GaussianCase) {
    Random generator = Random::GetInstance();

    std::size_t max_iter = 100;

    double actual_mean = 0.0;
    double actual_std = 1.0;

    std::vector<double> values{};
    values.reserve(max_iter);

    while (values.size() < max_iter) {
        values.emplace_back(generator.Gaussian(actual_mean, actual_std));
    }

    double mean = Mean(values);
    double std_dev = StandardDeviation(values);

    EXPECT_NEAR(actual_mean, mean, 1e-1);
    EXPECT_NEAR(actual_std, std_dev, 1e-1);
}
}  // namespace test

}  // namespace math_cpp
