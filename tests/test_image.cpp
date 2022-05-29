/*
 * Created by okn-yu on 2022/05/18.
 */

#include <gtest/gtest.h>
#include "pixel.hpp"
#include "image.hpp"

TEST(ImageTest, Constructor) {
    Image<RGBPixel> image = Image<RGBPixel>(100, 100);
    EXPECT_EQ(image.pixels[0]->r(), 0);
    EXPECT_EQ(image.pixels[0]->g(), 0);
    EXPECT_EQ(image.pixels[0]->b(), 0);
}

TEST(ImageTest, read_pixel) {
    Image<RGBPixel> image = Image<RGBPixel>(100, 100);
    EXPECT_EQ(image.read_pixel(0, 0), RGBPixel());
}

TEST(ImageTest, indexError) {
    Image<RGBPixel> image = Image<RGBPixel>(100, 100);
    EXPECT_THROW(image.read_pixel(100, 100), std::runtime_error);
}

TEST(ImageTest, indexError2) {
    Image<RGBPixel> image = Image<RGBPixel>(100, 100);
    EXPECT_THROW(image.read_pixel(-1, 0), std::runtime_error);

}

TEST(ImageTest, indexNoError) {
    Image<RGBPixel> image = Image<RGBPixel>(100, 100);
    EXPECT_NO_THROW(image.read_pixel(99, 99));
}

TEST(ImageTest, write_pixel) {
    Image<RGBPixel> image = Image<RGBPixel>(100, 100);
    image.write_pixel(50, 50, RGBPixel(200, 200, 200));
    EXPECT_EQ(image.read_pixel(50, 50), RGBPixel(200, 200, 200));
}

TEST(ImageTest, setRGBPixel2) {
    Image<RGBPixel> image = Image<RGBPixel>(100, 100);
    image.write_pixel(50, 50, RGBPixel(100, 100, 100));
    EXPECT_NE(image.read_pixel(50, 50), RGBPixel(200, 200, 200));
}

TEST(ImageTest, ppmOutput1) {
    Image<RGBPixel> image = Image<RGBPixel>(255, 255);
    for (int x = 0; x < 255; x++) {
        for (int y = 0; y < 255; y++) {
            image.write_pixel(x, y, RGBPixel(x, y, 0));
        }
    }

    image.ppm_output("test1.ppm");
    EXPECT_EQ(image.read_pixel(100, 100), RGBPixel(100, 100, 0));
}

TEST(ImageTest, ppmOutput2) {
    Image<RGBPixel> image = Image<RGBPixel>(255, 255);
    for (int x = 0; x < 255; x++) {
        for (int y = 0; y < 255; y++) {
            image.write_pixel(x, y, RGBPixel(x, x, x));
        }
    }

    image.ppm_output("test2.ppm");
    EXPECT_EQ(image.read_pixel(10, 100), RGBPixel(10, 10, 10));
}

TEST(ImageTest, ppmOutput3) {
    Image<RGBPixel> image = Image<RGBPixel>(255, 255);
    for (int x = 0; x < 255; x++) {
        for (int y = 0; y < 255; y++) {
            image.write_pixel(x, y, RGBPixel(y, y, y));
        }
    }

    image.ppm_output("test3.ppm");
    RGBPixel test = image.read_pixel(100, 10);

    EXPECT_EQ(image.read_pixel(100, 10), RGBPixel(10, 10, 10));
}

TEST(ImageTest, RGB_pngOutput) {
    Image<RGBPixel> image = Image<RGBPixel>(255, 255);
    for (int x = 0; x < image.width; x++) {
        for (int y = 0; y < image.height; y++) {
            image.write_pixel(x, y, RGBPixel(x, x, x));
        }
    }
    image.png_output("test.png", 3);
}

TEST(ImageTest, Gray_pngOutput) {
    Image<GrayPixel> image = Image<GrayPixel>(255, 255);
    for (int x = 0; x < image.width; x++) {
        for (int y = 0; y < image.height; y++) {
            image.write_pixel(x, y, GrayPixel(x));
        }
    }

    image.png_output("test2.png", 1);
}
