//
// Created by okn-yu on 2022/05/08.
//

#ifndef PRACTICEPATHTRACING_PIXEL_CPP
#define PRACTICEPATHTRACING_PIXEL_CPP

#include <iostream>

struct Pixel{
    int r;
    int g;
    int b;

    Pixel() {
        r = 0;
        g = 0;
        b = 0;
    }

    Pixel(int _n, int _m, int _k) {

        if (_n < 0 || 255 < _n) {
            throw std::runtime_error("invalid range");
        }

        if (_m < 0 || 255 < _m) {
            throw std::runtime_error("invalid range");
        }

        if (_k < 0 || 255 < _k) {
            throw std::runtime_error("invalid range");
        }
        r = _n;
        g = _m;
        b = _k;
    }

    template<typename T, typename U, typename F>
    Pixel(T _n, U _m, F _k) {
        r = _n;
        g = _m;
        b = _k;
        throw std::runtime_error("not integer argument");
    }

};

bool operator==(const Pixel &src, const Pixel &dst) {
    return src.r == dst.r && src.g == dst.g & src.b == dst.b;
}

bool operator!=(const Pixel &src, const Pixel &dst) {
    return src.r != dst.r || src.g != dst.g || src.b != dst.b;
}

#endif //PRACTICEPATHTRACING_PIXEL_CPP