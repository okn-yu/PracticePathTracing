/*
 * Created by okn-yu on 2022/06/17.
 */

#ifndef PRACTICEPATHTRACING_LIGHT_H
#define PRACTICEPATHTRACING_LIGHT_H

#include "vec3.hpp"

/*
 * すべての方向に等しい放射輝度を返す
 */

class PointLight {
public:
    Vec3 color;

    explicit PointLight(const Vec3 &_color) : color(_color) {};


    Vec3 Le() const {
        return color;
    }
};

#endif //PRACTICEPATHTRACING_LIGHT_H
