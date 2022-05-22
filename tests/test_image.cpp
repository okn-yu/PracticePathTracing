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

TEST(ImageTest, read_pixel) {
    Image image = Image(100, 100);
    EXPECT_EQ(image.read_pixel(0, 0), Pixel());
}

TEST(ImageTest, indexError) {
    Image image = Image(100, 100);
    EXPECT_THROW(image.read_pixel(100, 100), std::runtime_error);
}

TEST(ImageTest, indexError2) {
    Image image = Image(100, 100);
    EXPECT_THROW(image.read_pixel(-1, 0), std::runtime_error);

}

TEST(ImageTest, indexNoError) {
    Image image = Image(100, 100);
    EXPECT_NO_THROW(image.read_pixel(99, 99));
}

TEST(ImageTest, write_pixel) {
    Image image = Image(100, 100);
    image.write_pixel(50, 50, Pixel(200, 200, 200));
    EXPECT_EQ(image.read_pixel(50, 50), Pixel(200, 200, 200));
}

TEST(ImageTest, setPixel2) {
    Image image = Image(100, 100);
    image.write_pixel(50, 50, Pixel(100, 100, 100));
    EXPECT_NE(image.read_pixel(50, 50), Pixel(200, 200, 200));
}

TEST(ImageTest, ppmOutput1) {
    Image image = Image(255, 255);
    for (int x = 0; x < 255; x++) {
        for (int y = 0; y < 255; y++) {
            image.write_pixel(x, y, Pixel(x, y, 0));
        }
    }

    image.ppm_output("test1.ppm");
    EXPECT_EQ(image.read_pixel(100, 100), Pixel(100, 100, 0));
}

TEST(ImageTest, ppmOutput2) {
    Image image = Image(255, 255);
    for (int x = 0; x < 255; x++) {
        for (int y = 0; y < 255; y++) {
            image.write_pixel(x, y, Pixel(x, x, x));
        }
    }

    image.ppm_output("test2.ppm");
    EXPECT_EQ(image.read_pixel(10, 100), Pixel(10, 10, 10));
}

TEST(ImageTest, ppmOutput3) {
    Image image = Image(255, 255);
    for (int x = 0; x < 255; x++) {
        for (int y = 0; y < 255; y++) {
            image.write_pixel(x, y, Pixel(y, y, y));
        }
    }

    image.ppm_output("test3.ppm");
    EXPECT_EQ(image.read_pixel(100, 10), Pixel(10, 10, 10));
}

TEST(ImageTest, pngOutput){
    Image image = Image(255, 255);
    for (int x = 0; x < image.width; x++) {
        for (int y = 0; y < image.height; y++) {
            image.write_pixel(x, y, Pixel(x, x, x));
        }
    }

    image.png_output("test.png");
}
