/*
 * Created by okn-yu on 2022/05/12.
 * GoogleTestの注意
 * 浮動小数点の比較にexpected_eqは使えない
 * https://qiita.com/Dromar61243968/items/55223a969a769975176a
 */

#include "gtest/gtest.h"
//#include "test_pixel.cpp"
//#include "test_vec3.cpp"
//#include "test_ray.cpp"
//#include "test_sphere.cpp"
#include "test_image.cpp"


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

