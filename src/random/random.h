/// @file random.h
/// @author sangwon (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2022-12-03
///
/// @copyright Copyright (c) 2022
///
///

#ifndef SRC_RANDOM_RANDOM_H_
#define SRC_RANDOM_RANDOM_H_

#include <cstddef>
#include <random>

namespace math_cpp {
namespace random {

class Random {
 public:
    static Random& GetInstance();

    double Uniform(double min = 0.0, double max = 1.0);
    double Gaussian(double mean = 0.0, double std = 1.0);

 private:
    Random();

    std::mt19937 generator_{};
};

}  // namespace random
}  // namespace math_cpp

#endif  // SRC_RANDOM_RANDOM_H_
