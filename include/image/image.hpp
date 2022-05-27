//
// Created by okn-yu on 2022/05/04.
//

#ifndef PRACTICEPATHTRACING_IMAGE_H
#define PRACTICEPATHTRACING_IMAGE_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <memory>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"
#include "vec3.hpp"
#include "pixel.hpp"
#include "utils.hpp"


//https://worthliv.com/cpp_assert.html

template<typename T>
class Image {
public:
    int width;
    int height;
    std::vector<std::shared_ptr<RGBPixel>> data;

    //std::vector<std::shared_ptr<RGBPixel>> objects {100, std::make_shared<RGBPixel>()};
    Image(int _width, int _height) : width(_width), height(_height) {
        //TODO:もっと良い初期化方法を探すこと
        for (int i = 0; i < width * height; i++) {
            data.push_back(std::make_shared<T>());
        }
    }

    RGBPixel read_pixel(int x, int y) const {
        int index = y * width + x;
        is_index_safe(index, static_cast<int>(data.size()));
        return *data[index];
    };

    void write_pixel(int x, int y, const RGBPixel &p) {
        int index = y * width + x;
        is_index_safe(index, static_cast<int>(data.size()));
        *data[index] = p;
    };

    void ppm_output(const std::string &filename) const {
        std::ofstream file(filename);
        file << "P3" << std::endl;
        file << width << " " << height << std::endl;
        file << "255" << std::endl;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                RGBPixel pixel = this->read_pixel(x, y);
                int r = pixel.r;
                int g = pixel.g;
                int b = pixel.b;
                file << r << " " << g << " " << b << std::endl;
            }
        }
        file.close();
    };

    //comp:1=Y, 2=YA, 3=RGB, 4=RGBA.
    //stride_bytes:"stride_in_bytes" is the distance in bytes from the first byte of a row of pixels to the first byte of the next row of pixels.
    void png_output(const std::string &filename, int comp = 3) const {

        //TODO:
        // RGBとGrayの両方に対応するためinsertを使って書き換えること
        std::vector<uint8_t> output(width * height * 3);
        for (int i = 0; i < width * height; i++) {
            output[i * 3 + 0] = static_cast<uint8_t>(data[i]->r);
            output[i * 3 + 1] = static_cast<uint8_t>(data[i]->g);
            output[i * 3 + 2] = static_cast<uint8_t>(data[i]->b);
        }

        stbi_write_png(filename.data(), width, height, comp, output.data(), width * 3);
    };
};

#endif //PRACTICEPATHTRACING_IMAGE_H