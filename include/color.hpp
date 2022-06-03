/*
 * Created by okn-yu on 2022/06/01.
 * Colorは慣習として0から1の間の連続値を取る
 */

#ifndef PRACTICEPATHTRACING_COLOR_H
#define PRACTICEPATHTRACING_COLOR_H

#include <array>
#include "pixel.hpp"
#include "vec3.hpp"

struct Color {
    /*
     * data[0]: r
     * data[1]: g
     * data[2]: b
     */
    std::array<float, 3> data{};

    Color() {
        data[0] = 0.0f;
        data[1] = 0.0f;
        data[2] = 0.0f;
    }

    template<typename T, typename U, typename F>
    Color(T r, U g, F b) {
        throw std::runtime_error("not float argument");
    }

    Color(float r, float g, float b) {

        if (r < 0 || 1 < r) {
            throw std::runtime_error("invalid range");
        }

        if (g < 0 || 1 < g) {
            throw std::runtime_error("invalid range");
        }

        if (b < 0 || 1 < b) {
            throw std::runtime_error("invalid range");
        }
        data[0] = r;
        data[1] = g;
        data[2] = b;
    }

    explicit Color(Vec3 v):Color(v.x(), v.y(), v.z()){}
//    explicit Color(Vec3 v) {
//        data[0] = v.x();
//        data[1] = v.y();
//        data[2] = v.z();
//    }

    float r() {
        return data[0];
    }

    float g() {
        return data[1];
    }

    float b() {
        return data[2];
    }

    RGBPixel pixalize() {
        assert(0 <= data[0] && data[0] <= 1);
        assert(0 <= data[1] && data[1] <= 1);
        assert(0 <= data[2] && data[2] <= 1);

        auto R = static_cast<int>(data[0] * 255);
        auto G = static_cast<int>(data[1] * 255);
        auto B = static_cast<int>(data[2] * 255);

        RGBPixel pixel = RGBPixel(R, G, B);

        return pixel;
    }
};

bool operator==(const Color &src, const Color &dst) {
    return src.data == dst.data;
}

Color vec_2_color(Vec3 v) {
    if ((std::abs(v.x()) <= 1) && (std::abs(v.y()) <= 1) && (std::abs(v.z()) <= 1)) {
        Vec3 color_vec = (v + 1) / 2;
        return Color(color_vec);
    } else {
        throw std::runtime_error("invalid vector length.");
    }
}

#endif //PRACTICEPATHTRACING_COLOR_H
