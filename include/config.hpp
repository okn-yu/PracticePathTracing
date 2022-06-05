/*
 * Created by okn-yu on 2022/05/05.
 */

#ifndef PRACTICEPATHTRACING_CONFIG_H
#define PRACTICEPATHTRACING_CONFIG_H

struct ConstParam
{
    static const int HIT_DISTANCE_MAX = 10000;
    static const int HIT_DISTANCE_MIN = 0;
    constexpr static const double RAY_T_MAX = 100;
};

#endif //PRACTICEPATHTRACING_CONFIG_H
