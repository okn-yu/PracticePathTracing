//
// Created by okn-yu on 2022/05/08.
//

#ifndef PRACTICEPATHTRACING_PIXEL_CPP
#define PRACTICEPATHTRACING_PIXEL_CPP

#include <iostream>

struct Pixel {
private:
    int n;
    int m;
    int k;
public:
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
        n = _n;
        m = _m;
        k = _k;
    }

    template<typename T, typename U, typename F>
    Pixel(T _n, U _m, F _k) {
        n = _n;
        m = _m;
        k = _k;
        throw std::runtime_error("not integer argument");
    }
};

#endif //PRACTICEPATHTRACING_PIXEL_CPP