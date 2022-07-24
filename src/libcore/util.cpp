/*
 * Created by okn-yu on 2022/07/23.
 */

#include <iostream>
#include <random>
//#include "futaba/core/vec3.h"

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

float rnd() {
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

/*
 * templateをヘッダファイルと.cppに分けて書くとコンパイル時に失敗する
 * 対策としてはそもそも分けないか、以下のように型毎に明記することで回避できる（明示的実体化）
 * https://pknight.hatenablog.com/entry/20090826/1251303641
 */

template float clamp<float>(float x, float xmin, float xmax);

template int clamp<int>(int x, int xmin, int xmax);


void util_test() {
    std::cout << "util_test is called!" << std::endl;
};