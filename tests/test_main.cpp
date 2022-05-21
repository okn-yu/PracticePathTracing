//
// Created by okn-yu on 2022/05/12.
//

#include "gtest/gtest.h"
#include "test_pixel.cpp"
#include "test_ray.cpp"
#include "test_vec3.cpp"
#include "test_sphere.cpp"
#include "test_image.cpp"


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

