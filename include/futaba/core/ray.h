/*
 * Created by okn-yu on 2022/05/04.
 *
 * Rayは物理的には放射輝度に対応する
 *
 * Rayがオブジェクトに衝突するかの判定はRayでは実装しない
 * Rayのメンバ変数にColorをもたせたり、direct/indirectをもたせたりなどのアプローチも存在する
 *
 */

#ifndef PRACTICEPATHTRACING_RAY_H
#define PRACTICEPATHTRACING_RAY_H

#include <iostream>
#include "core/vec3.h"

class Ray {
public:
    Point3 origin;
    Vec3 direction;

    Ray(const Vec3 &_origin, const Vec3 &_direction) : origin(_origin), direction(_direction) {};

    /*
     * float型の引数を取る関数()を定義している
     * Ray(3.0)のように呼び出しを行う
     */
    Vec3 operator()(float t) const {
        return origin + t * direction;
    };
};


std::ostream &operator<<(std::ostream &stream, const Ray &ray) {
    stream << "origin: " << ray.origin << " direction: " << ray.direction;
    return stream;
}

#endif //PRACTICEPATHTRACING_RAY_H