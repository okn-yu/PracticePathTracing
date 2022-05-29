/*
 * Created by okn-yu on 2022/05/08.
 *
 * RGBPixel構造体
 * uint8_tは0未満や256以上の整数値に対しては不適切な値に変換されてしまう
 * この事象を防ぐために受け取る値はint型で受けて値が適切な範囲内かを確認している
 * float型の変数も3.14が3のようにキャストされるためint型以外はすべて実行時例外を送出している
 * RGBはarray<uint8_t>型のdataを用いて定義したほうがすっきりするかもしれない
 * その場合serializeは単にpublicなdataを返せば済むのでそもそも定義する必要すらない
 * 上記を満たすように実装を修正した(5/29)
 */

#ifndef PRACTICEPATHTRACING_PIXEL_CPP
#define PRACTICEPATHTRACING_PIXEL_CPP

#include <iostream>
#include <stack>

struct GrayPixel {
    std::array<uint8_t, 1> data{};

    GrayPixel() {
        data[0] = 0;
    }

    template<typename T>
    explicit GrayPixel(T n) {
        throw std::runtime_error("invalid range");
    }

    explicit GrayPixel(int n) {
        if (n < 0 || 255 < n) {
            throw std::runtime_error("invalid range");
        }
        data[0] = n;
    }

    uint8_t n(){
        return data[0];
    }

    // 代入操作の定義
    GrayPixel &operator=(const GrayPixel &src) = default;
};

bool operator==(const GrayPixel &src, const GrayPixel &dst) {
    return src.data == dst.data;
}

bool operator!=(const GrayPixel &src, const GrayPixel &dst) {
    return src.data != dst.data;
}

std::ostream &operator<<(std::ostream &stream, const GrayPixel &pixel) {
    stream << "(" << pixel.data[0] << ")";
    return stream;
}

struct RGBPixel {
    /*
     * data[0]: r
     * data[1]: g
     * data[2]: b
     */
    std::array<uint8_t, 3> data{};

    RGBPixel() {
        data[0] = 0;
        data[1] = 0;
        data[2] = 0;
    }

    template<typename T, typename U, typename F>
    RGBPixel(T r, U g, F b) {
        throw std::runtime_error("not integer argument");
    }

    RGBPixel(int r, int g, int b) {

        if (r < 0 || 255 < r) {
            throw std::runtime_error("invalid range");
        }

        if (g < 0 || 255 < g) {
            throw std::runtime_error("invalid range");
        }

        if (b < 0 || 255 < b) {
            throw std::runtime_error("invalid range");
        }
        data[0] = r;
        data[1] = g;
        data[2] = b;
    }

    uint8_t r(){
        return data[0];
    }

    uint8_t g(){
        return data[1];
    }

    uint8_t b(){
        return data[2];
    }

    // 代入操作の定義
    RGBPixel &operator=(const RGBPixel &src) = default;
};

bool operator==(const RGBPixel &src, const RGBPixel &dst) {
    return src.data == dst.data;
}

bool operator!=(const RGBPixel &src, const RGBPixel &dst) {
    return src.data != dst.data;
}

std::ostream &operator<<(std::ostream &stream, const RGBPixel &pixel) {
    stream << "(" << pixel.data[0] << ", " << pixel.data[1] << ", " << pixel.data[2] << ")";
    return stream;
}

#endif //PRACTICEPATHTRACING_PIXEL_CPP