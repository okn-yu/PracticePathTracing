/*
 * Created by okn-yu on 2022/05/08.
 */

#include <gtest/gtest.h>
#include "color.hpp"
#include "vec3.hpp"
#include "pixel.hpp"

/*
 * Color UnitTest
 */

TEST(ColorTest, Constructor1) {
    EXPECT_EQ(Color(), Color(0.0f, 0.0f, 0.0f));
}

TEST(ColorTest, Constructor2) {
    EXPECT_THROW(Color(3.14f, 0, 0), std::runtime_error);
}

TEST(ColorTest, Constructor3) {
    EXPECT_THROW(Color(-1, 0, 0), std::runtime_error);
}

TEST(ColorTest, Constructor4) {
    EXPECT_THROW(Color(0, 0, 256), std::runtime_error);
}

TEST(ColorTest, Constructor5) {
    EXPECT_EQ(Color(0.1f, 0.2f, 0.3f).r(), 0.1f);
}

TEST(ColorTest, Constructor6) {
    EXPECT_EQ(Color(0.1f, 0.2f, 0.3f).g(), 0.2f);
}

TEST(ColorTest, Constructor7) {
    EXPECT_EQ(Color(0.1f, 0.2f, 0.3f).b(), 0.3f);
}

TEST(ColorTest, Constructor8){
    EXPECT_THROW(Color(Vec3(100, 200, 300)), std::runtime_error);
}

TEST(ColorTest, Constructor9){
    EXPECT_THROW(Color(Vec3(0.1, 0.3, -0.5)), std::runtime_error);
}

TEST(ColorTest, Constructor10){
    EXPECT_FLOAT_EQ(Color(Vec3(0.1, 0.3, 0.5)).r(), 0.1);
    EXPECT_FLOAT_EQ(Color(Vec3(0.1, 0.3, 0.5)).g(), 0.3);
    EXPECT_FLOAT_EQ(Color(Vec3(0.1, 0.3, 0.5)).b(), 0.5);
}

TEST(ColorTest, pixalize1) {
    Color color = Color(0.1f, 0.3f, 0.5f);
    RGBPixel pixel = color.pixalize();
    EXPECT_EQ(pixel.r(), 25);
    EXPECT_EQ(pixel.g(), 76);
    EXPECT_EQ(pixel.b(), 127);
}