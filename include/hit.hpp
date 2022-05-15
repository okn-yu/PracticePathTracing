//
// Created by okn-yu on 2022/05/05.
//

#ifndef PRACTICEPATHTRACING_HITTABLE_H
#define PRACTICEPATHTRACING_HITTABLE_H

#include "config.hpp"
#include "ray.hpp"
#include "vec3.hpp"

struct HitRecord {
    Vec3 hit_pos;
    Vec3 hit_normal;
    double t;
};

#endif //PRACTICEPATHTRACING_HITTABLE_H
