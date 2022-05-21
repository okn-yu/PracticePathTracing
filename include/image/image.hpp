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

    Pixel getPixel(int x, int y) const {
        int index = y * width + x;
        is_index_safe(index, static_cast<int>(data.size()));

        int r = data[index]->r;
        int g = data[index]->g;
        int b = data[index]->b;

        return Pixel(r, g, b);
    };

    void setPixel(int x, int y, const Pixel &p) {
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
                Pixel pixel = this->getPixel(x, y);
                int r = pixel.r;
                int g = pixel.g;
                int b = pixel.b;
                file << r << " " << g << " " << b << std::endl;
            }
        }
        file.close();
    };
};

#endif //PRACTICEPATHTRACING_IMAGE_H