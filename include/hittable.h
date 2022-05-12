//
// Created by okn-yu on 2022/05/05.
//

#ifndef PRACTICEPATHTRACING_HITTABLE_H
#define PRACTICEPATHTRACING_HITTABLE_H

#include "config.h"
#include "ray.h"
#include "vec3.h"

struct HitRecord {
    Point3 hit_pos;
    Vec3 hit_normal;
    double t;
};

class Hittable {
public:
    //virtual  ~Hittable();
    virtual bool hit(const Ray &ray, HitRecord &record) = 0;
};

#endif //PRACTICEPATHTRACING_HITTABLE_H
