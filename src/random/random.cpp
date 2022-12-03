/// @file random.cpp
/// @author sangwon (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2022-12-03
///
/// @copyright Copyright (c) 2022
///
///

#include "src/random/random.h"

#include <cstdlib>
#include <ctime>

namespace math_cpp {
namespace random {
Random& Random::GetInstance() {
    static Random instance{};

    return instance;
}

double Random::Uniform(double min, double max) {
    std::uniform_real_distribution<> dis(min, max);
    return dis(generator_);
}

double Random::Gaussian(double mean, double std) {
    std::normal_distribution<> dis(mean, std);
    return dis(generator_);
}

Random::Random() : generator_{(std::random_device())()} {}

}  // namespace random
}  // namespace math_cpp
