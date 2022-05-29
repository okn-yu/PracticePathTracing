/*
 * Created by okn-yu on 2022/05/04.
 * 調べた結果以下の結論に達した
 * オブジェクト型のポイントを扱う場合は、生のポイントの代わりにスマートポインタを用いるとよい
 * 組み込み型の配列を扱う場合は、配列の代わりにvectorを用いる
 * オブジェクト型の配列を扱う場合は、vectorとスマートポインタを組み合わせて用いる
 * これらを用いることでポインタの開放忘れによる弊害を防ぐことができる
 */

#ifndef PRACTICEPATHTRACING_IMAGE_H
#define PRACTICEPATHTRACING_IMAGE_H
#include <cassert>
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


template<typename T>
class Image {
public:
    int width;
    int height;
    std::vector<std::shared_ptr<T>> pixels;

    // std::vector<std::shared_ptr<T>> objects {100, std::make_shared<T>()};
    Image(int _width, int _height) : width(_width), height(_height) {
        // TODO:もっと良い初期化方法を探すこと
        for (int i = 0; i < width * height; i++) {
            pixels.push_back(std::make_shared<T>());
        }
    }

    T read_pixel(int x, int y) const {
        int index = y * width + x;
        is_index_safe(index, static_cast<int>(pixels.size()));
        return *pixels[index];
    };

    void write_pixel(int x, int y, const T &p) {
        int index = y * width + x;
        is_index_safe(index, static_cast<int>(pixels.size()));
        *pixels[index] = p;
    };

    void ppm_output(const std::string &filename) const {
        std::ofstream file(filename);
        file << "P3" << std::endl;
        file << width << " " << height << std::endl;
        file << "255" << std::endl;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                T pixel = this->read_pixel(x, y);
                int r = pixel.r();
                int g = pixel.g();
                int b = pixel.b();
                file << r << " " << g << " " << b << std::endl;
            }
        }
        file.close();
    };

    // comp:1=Y, 2=YA, 3=RGB, 4=RGBA.
    // stride_bytes:"stride_in_bytes" is the distance in bytes from the first byte of a row of pixels to the first byte of the next row of pixels.
    void png_output(const std::string &filename, int comp) const {

        int pixel_size = (*pixels[0]).data.size();
        assert(comp == pixel_size);

        std::vector<uint8_t> output(width * height * pixel_size);
        for (int i = 0; i < width * height; i++) {
            for (int j = 0; j < pixel_size; j++) {
                output[i * pixel_size + j] = (*pixels[i]).data[j];
            }
        }
        stbi_write_png(filename.data(), width, height, comp, output.data(), width * pixel_size);
    };
};

#endif //PRACTICEPATHTRACING_IMAGE_H