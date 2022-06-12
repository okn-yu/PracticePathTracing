/*
 * Created by okn-yu on 2022/05/19.
 */

#ifndef PRACTICEPATHTRACING_UTILS_HPP
#define PRACTICEPATHTRACING_UTILS_HPP

#include <random>

bool is_index_safe(int index, int max_index) {

    if (index < 0 || max_index < index) {
        throw std::runtime_error("invalid index");
    } else {
        return true;
    }
}

/*
 * メルセンヌ・ツイスタを乱数生成器として使用する
 * min:0, max:1
 */

std::random_device rnd_dev;
std::mt19937 mt(rnd_dev());
std::uniform_real_distribution<> dist(0, 1);
inline float rnd() {
    return dist(mt);
}

#endif //PRACTICEPATHTRACING_UTILS_HPP