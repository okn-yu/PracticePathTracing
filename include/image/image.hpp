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
#include "util.hpp"
#include "pixel.hpp"


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

    // x: 0 ~ (width-1)
    // y: 0 ~ (height-1)
    Pixel getPixel(int x, int y) const {
        int r = data[y * width + x]->r;
        int g = data[y * width + x]->g;
        int b = data[y * width + x]->b;

        return Pixel(r, g, b);
    };

    void setPixel(int x, int y, const Pixel &p) {
        data[y * width + x]->r = p.r;
        data[y * width + x]->g = p.g;
        data[y * width + x]->b = p.b;
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