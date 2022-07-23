/*
 * Created by okn-yu on 2022/05/19.
 */

#ifndef PRACTICEPATHTRACING_UTILS_H
#define PRACTICEPATHTRACING_UTILS_H

#include <random>
#include "vec3.h"

/*
 * 配列のインデックスエラーが発生しないかをチェックする
 */
bool is_index_safe(int index, int max_index) {

    if (index < 0 || max_index < index) {
        throw std::runtime_error("invalid index");
    } else {
        return true;
    }
}

/*
 * rand関数
 * メルセンヌ・ツイスタを乱数生成器として使用して0-1間の乱数を生成する
 */

std::random_device rnd_dev;
std::mt19937 mt(rnd_dev());
std::uniform_real_distribution<> dist(0, 1);
inline float rnd() {
    return dist(mt);
}

template<typename T>
T clamp(T x, T xmin, T xmax) {
    if (x < xmin) {
        return xmin;
    } else if (x > xmax) {
        return xmax;
    } else {
        return x;
    }
}

#endif //PRACTICEPATHTRACING_UTILS_H