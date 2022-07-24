/*
 * Created by okn-yu on 2022/05/19.
 */

#ifndef PRACTICEPATHTRACING_UTILS_H
#define PRACTICEPATHTRACING_UTILS_H

/*
 * 配列のインデックスエラーが発生しないかをチェックする
 */
bool is_index_safe(int index, int max_index);

/*
 * rand関数
 * メルセンヌ・ツイスタを乱数生成器として使用して0-1間の乱数を生成する
 */

float rnd();

template<typename T>
T clamp(T x, T xmin, T xmax);

void util_test();

#endif //PRACTICEPATHTRACING_UTILS_H