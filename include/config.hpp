/*
 * Created by okn-yu on 2022/05/05.
 * constexpr static const
 *
 */

#ifndef PRACTICEPATHTRACING_CONFIG_H
#define PRACTICEPATHTRACING_CONFIG_H

struct ConstParam
{
    constexpr static const float HIT_DISTANCE_MAX = 10000.0f;
    constexpr static const float HIT_DISTANCE_MIN = 0.0f;
    constexpr static const float GAMMA_VALUE = 1.8f;
};

#endif //PRACTICEPATHTRACING_CONFIG_H
