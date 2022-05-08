//
// Created by okn-yu on 2022/05/08.
//

#include <gtest/gtest.h>
#include "pixel.h"

TEST(PixelTest, TestNoThrow1) {
    EXPECT_NO_THROW(Pixel(1, 2, 3));
}

TEST(PixelTest, TestNoThrow2) {
    EXPECT_NO_THROW(Pixel(0, 2, 3));
}

TEST(PixelTest, TestNoThrow3) {
    EXPECT_NO_THROW(Pixel(3, 14, 2, 3));
}

TEST(PixelTest, TestThrow1) {
    EXPECT_THROW(Pixel(256, 2, 3), std::runtime_error);
}

TEST(PixelTest, TestThrow2) {
    EXPECT_THROW(Pixel(-1, 2, 3), std::runtime_error);
}