/*
 * Created by okn-yu on 2022/05/04.
 * Rayには加減乗除のような操作が定義されないため非常にシンプル
 */

#ifndef PRACTICEPATHTRACING_RAY_H
#define PRACTICEPATHTRACING_RAY_H

#include <iostream>
#include "vec3.hpp"

class Ray {
public:
    Vec3 origin;
    Vec3 direction;

    Ray(const Vec3& _origin, const Vec3& _direction) : origin(_origin), direction(_direction) {};

    // float型の引数を取る関数()を定義している
    Vec3 operator()(float t) const {
        return origin + t * direction;
    };
};


std::ostream& operator<<(std::ostream& stream, const Ray& ray) {
    stream << "origin: " << ray.origin << " direction: " << ray.direction;
    return stream;
}

#endif //PRACTICEPATHTRACING_RAY_H
