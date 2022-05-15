//
// Created by okn-yu on 2022/05/08.
//

#include <gtest/gtest.h>
#include "pixel.hpp"


TEST(PixelTest, TestNoThrow1) {
    EXPECT_NO_THROW(Pixel(1, 2, 3));
}

TEST(PixelTest, TestNoThrow2) {
    EXPECT_NO_THROW(Pixel(0, 0, 0));
}

TEST(PixelTest, TestNoThrow3) {
    EXPECT_NO_THROW(Pixel(255, 255, 255));
}

TEST(PixelTest, TestThrow1) {
EXPECT_THROW(Pixel(3.14f, 0.0f, 1.0f), std::runtime_error);
}

TEST(PixelTest, TestThrow2) {
    EXPECT_THROW(Pixel(3.14f, 0, 1), std::runtime_error);
}

TEST(PixelTest, TestThrow3) {
    EXPECT_THROW(Pixel(256, 2, 3), std::runtime_error);
}

TEST(PixelTest, TestThrow4) {
    EXPECT_THROW(Pixel(-1, 2, 3), std::runtime_error);
}
