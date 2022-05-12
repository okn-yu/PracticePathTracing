//
// Created by okn-yu on 2022/05/05.
//

#ifndef PRACTICEPATHTRACING_SPHERE_H
#define PRACTICEPATHTRACING_SPHERE_H

#include <cmath>
#include "config.h"
#include "vec3.h"
#include "ray.h"
#include "hittable.h"

class Sphere : public Hittable {
public:
    Vec3 center;
    float radius;

    Sphere(const Vec3 &_center, float _radius) : center(_center), radius(_radius) {};

    bool hit(const Ray &ray, HitRecord &hit_record) override {
        float b = dot(ray.direction, ray.origin - center);
        float c = (ray.origin - center).length2() - radius * radius;
        float D = b * b - c;
        float t;

        //t1 <= t2
        float t1 = -b - std::sqrt(D);
        float t2 = -b + std::sqrt(D);


        // HIT_DISTANCE_MAX < t1 < t2
        if (t1 > ConstParam::HIT_DISTANCE_MAX)
            return false;
        // t1 < t2 < HIT_DISTANCE_MIN
        if (t2 < ConstParam::HIT_DISTANCE_MIN)
            return false;
        // t1 < HIT_DISTANCE_MIN, HIT_DISTANCE_MAX < t2
        if (t1 < ConstParam::HIT_DISTANCE_MIN & ConstParam::HIT_DISTANCE_MAX < t2)
            return false;

        // HIT_DISTANCE_MIN < t1 < t2
        if (t1 > ConstParam::HIT_DISTANCE_MIN)
            t = t1;
            // t1 < t2 < HIT_DISTANCE_MIN
        else {
            t = t2;
        }

        hit_record.t = t;
        hit_record.hit_pos = ray(t);
        hit_record.hit_normal = normalize(hit_record.hit_pos - center);

        return true;
    };
};

#endif //PRACTICEPATHTRACING_SPHERE_H
