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

    Pixel getPixel(int i, int j) const {
        int r = data[(j-1) * width + i]->r;
        int g = data[(j-1) * width + i]->g;
        int b = data[(j-1) * width + i]->b;

        return Pixel(r, g, b);
    };

    //iは横の座標でjは縦の座標
    //i:1~width
    //j:1~height
    void setPixel(int i, int j, const Pixel &p) {
        data[(j-1) * width + i]->r = p.r;
        data[(j-1) * width + i]->g = p.g;
        data[(j-1) * width + i]->b = p.b;
    };

    void ppm_output(const std::string &filename) const {
        std::ofstream file(filename);
        file << "P3" << std::endl;
        file << width << " " << height << std::endl;
        file << "255" << std::endl;
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                Pixel pixel = this->getPixel(i, j);
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