/*
 * Created by okn-yu on 2022/05/08.
 */

#include <gtest/gtest.h>
#include "pixel.hpp"

/*
 * GrayPixel UnitTest
 */

TEST(GrayPixelTest, Constructor1) {
    EXPECT_EQ(GrayPixel().n(), 0);
}

TEST(GrayPixelTest, Constructor2) {
    EXPECT_THROW(GrayPixel(3.14f), std::runtime_error);

}

TEST(GrayPixelTest, Constructor3) {
    EXPECT_THROW(GrayPixel(-1), std::runtime_error);

}

TEST(GrayPixelTest, Constructor4) {
    EXPECT_THROW(GrayPixel(256), std::runtime_error);

}

TEST(GrayPixelTest, Constructor5) {
    EXPECT_EQ(GrayPixel(255).n(), 255);
}

TEST(GrayPixelTest, Substitution) {
    GrayPixel src = GrayPixel(255);
    GrayPixel dst = GrayPixel(1);
    dst = src;

    EXPECT_EQ(dst.n(), 255);
}

TEST(GrayPixelTest, Equal) {
    GrayPixel src = GrayPixel(255);
    GrayPixel dst = GrayPixel(1);

    EXPECT_FALSE(src == dst);
}

TEST(GrayPixelTest, NotEqual) {
    GrayPixel src = GrayPixel(255);
    GrayPixel dst = GrayPixel(1);

    EXPECT_TRUE(src != dst);
}

/*
 * RGBPixel UnitTest
 */

TEST(RGBPixelTest, Constructor1) {
    EXPECT_EQ(RGBPixel(), RGBPixel(0, 0, 0));
}

TEST(RGBPixelTest, Constructor2) {
    EXPECT_THROW(RGBPixel(3.14f, 0, 0), std::runtime_error);
}

TEST(RGBPixelTest, Constructor3) {
    EXPECT_THROW(RGBPixel(-1, 0, 0), std::runtime_error);
}

TEST(RGBPixelTest, Constructor4) {
    EXPECT_THROW(RGBPixel(0, 0, 256), std::runtime_error);
}

TEST(RGBPixelTest, Constructor5) {
    EXPECT_EQ(RGBPixel(1, 2, 3).r(), 1);
}

TEST(RGBPixelTest, Constructor6) {
    EXPECT_EQ(RGBPixel(1, 2, 3).g(), 2);
}

TEST(RGBPixelTest, Constructor7) {
    EXPECT_EQ(RGBPixel(1, 2, 3).b(), 3);
}

TEST(RGBPixelTest, Substitution) {
    RGBPixel src = RGBPixel(255, 255, 255);
    RGBPixel dst = RGBPixel(1, 1, 1);
    dst = src;
    EXPECT_EQ(dst.r(), src.r());
    EXPECT_EQ(dst.g(), src.g());
    EXPECT_EQ(dst.b(), src.b());

}

TEST(RGBPixelTest, TestThrow2) {
    EXPECT_THROW(RGBPixel(3.14f, 0, 1), std::runtime_error);
}

TEST(RGBPixelTest, TestThrow3) {
    EXPECT_THROW(RGBPixel(256, 2, 3), std::runtime_error);
}

TEST(RGBPixelTest, TestThrow4) {
    EXPECT_THROW(RGBPixel(-1, 2, 3), std::runtime_error);
}

