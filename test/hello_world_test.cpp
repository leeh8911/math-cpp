/// @file hello_world_test.cpp
/// @author sangwon (leeh8911@gmail.com)
/// @brief
/// @version 0.1
/// @date 2022-11-26
///
/// @copyright Copyright (c) 2022
///

#include "src/hello_world.h"

#include <gtest/gtest.h>

TEST(HelloWorldTest, SampleCase) {
    math_cpp::Foo();
    EXPECT_TRUE(true);
}