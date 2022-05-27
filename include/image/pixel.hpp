//
// Created by okn-yu on 2022/05/08.
//

/*
 *  RGBPixel構造体
 *  uint8_tは0未満や256以上の整数値に対しては不適切な値に変換されてしまう
 *  この事象を防ぐために受け取る値はint型で受けて値が適切な範囲内かを確認している
 *  float型の変数も3.14が3のようにキャストされるためint型以外はすべて実行時例外を送出している
 */

#ifndef PRACTICEPATHTRACING_PIXEL_CPP
#define PRACTICEPATHTRACING_PIXEL_CPP

#include <iostream>

struct GrayPixel {
    int n;

    GrayPixel() {
        n = 0;
    }

    template<typename T>
    explicit GrayPixel(T _n) {
        n = _n;
        throw std::runtime_error("invalid range");
    }

    explicit GrayPixel(int _n) {
        if (_n < 0 || 255 < _n) {
            throw std::runtime_error("invalid range");
        }
        n = _n;
    }

    GrayPixel &operator=(const GrayPixel &src) = default;

};

bool operator==(const GrayPixel &src, const GrayPixel &dst) {
    return src.n == dst.n;
}

bool operator!=(const GrayPixel &src, const GrayPixel &dst) {
    return src.n != dst.n;
}

std::ostream &operator<<(std::ostream &stream, const GrayPixel &pixel) {
    stream << "(" << pixel.n << ")";
    return stream;
}

struct RGBPixel {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    RGBPixel() {
        r = 0;
        g = 0;
        b = 0;
    }

    template<typename T, typename U, typename F>
    RGBPixel(T _n, U _m, F _k) {
        r = _n;
        g = _m;
        b = _k;
        throw std::runtime_error("not integer argument");
    }

    RGBPixel(int _n, int _m, int _k) {

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

    RGBPixel &operator=(const RGBPixel &src) = default;

};

bool operator==(const RGBPixel &src, const RGBPixel &dst) {
    return src.r == dst.r && src.g == dst.g & src.b == dst.b;
}

bool operator!=(const RGBPixel &src, const RGBPixel &dst) {
    return src.r != dst.r || src.g != dst.g || src.b != dst.b;
}

std::ostream &operator<<(std::ostream &stream, const RGBPixel &pixel) {
    stream << "(" << pixel.r << ", " << pixel.g << ", " << pixel.b << ")";
    return stream;
}

#endif //PRACTICEPATHTRACING_PIXEL_CPP