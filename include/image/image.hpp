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

class Image {
public:
    int width;
    int height;
    std::vector<std::shared_ptr<Pixel>> data;


    //std::vector<std::shared_ptr<Pixel>> objects {100, std::make_shared<Pixel>()};
    Image(int _width, int _height) : width(_width), height(_height) {
        //TODO:もっと良い初期化方法を探すこと
        for (int i = 0; i < width * height; i++) {
            data.push_back(std::make_shared<Pixel>());
        }
    }

    Pixel read_pixel(int x, int y) const {
        int index = y * width + x;
        is_index_safe(index, static_cast<int>(data.size()));

        int r = data[index]->r;
        int g = data[index]->g;
        int b = data[index]->b;

        return Pixel(r, g, b);
    };

    void write_pixel(int x, int y, const Pixel &p) {
        int index = y * width + x;
        is_index_safe(index, static_cast<int>(data.size()));

        data[index]->r = p.r;
        data[index]->g = p.g;
        data[index]->b = p.b;
    };

    void ppm_output(const std::string &filename) const {
        std::ofstream file(filename);
        file << "P3" << std::endl;
        file << width << " " << height << std::endl;
        file << "255" << std::endl;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                Pixel pixel = this->read_pixel(x, y);
                int r = pixel.r;
                int g = pixel.g;
                int b = pixel.b;
                file << r << " " << g << " " << b << std::endl;
            }
        }
        file.close();
    };

    void png_output(const std::string &filename) const {
        //comp:1=Y, 2=YA, 3=RGB, 4=RGBA.
        //stride_bytes:"stride_in_bytes" is the distance in bytes from the first byte of a row of pixels to the first byte of the next row of pixels.

        std::vector<uint8_t> output(width * height * 3);
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                int index = h * width + w;
                output[index * 3 + 0] = static_cast<uint8_t>(data[index]->r);
                output[index * 3 + 1] = static_cast<uint8_t>(data[index]->g);
                output[index * 3 + 2] = static_cast<uint8_t>(data[index]->b);
            }
        }

        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                int index = h * width + w;
                output[index * 3 + 0] = w;
                output[index * 3 + 1] = w;
                output[index * 3 + 2] = w;
            }
        }

        stbi_write_png(filename.data(), width, height, 3, output.data(), width * 3);
        //stbi_write_png(filename.data(), width, height, 3, output.data(), width*3);

    };
};

#endif //PRACTICEPATHTRACING_IMAGE_H