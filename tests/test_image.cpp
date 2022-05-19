//
// Created by okn-yu on 2022/05/18.
//

#include <gtest/gtest.h>
#include "image.hpp"

TEST(ImageTest, Constructor) {
    Image image = Image(100, 100);
    EXPECT_EQ(image.data[0]->r, 0);
    EXPECT_EQ(image.data[0]->g, 0);
    EXPECT_EQ(image.data[0]->b, 0);
}

TEST(ImageTest, getPixel) {
    Image image = Image(100, 100);
    EXPECT_EQ(image.getPixel(0, 0), Pixel());
}

TEST(ImageTest, setPixel) {
    Image image = Image(100, 100);
    image.setPixel(50, 50, Pixel(200, 200, 200));
    EXPECT_EQ(image.getPixel(50, 50), Pixel(200, 200, 200));
}

TEST(ImageTest, setPixel2) {
    Image image = Image(100, 100);
    image.setPixel(50, 50, Pixel(100, 100, 100));
    EXPECT_NE(image.getPixel(50, 50), Pixel(200, 200, 200));
}

TEST(ImageTest, ppmOutput) {
    Image image = Image(255, 255);
    for (int x = 0; x < 255; x++) {
        for (int y = 0; y < 255; y++) {
            image.setPixel(x, y, Pixel(x, y, 0));
        }
    }

    image.ppm_output("test.ppm");
    EXPECT_EQ(image.getPixel(100, 100), Pixel(100, 100, 0));
}

