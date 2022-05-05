//
// Created by okn-yu on 2022/05/05.
//

#ifndef PRACTICEPATHTRACING_SPHERE_H
#define PRACTICEPATHTRACING_SPHERE_H

#include <cmath>
#include "config.h"
#include "vec3.h"
#include "ray.h"
#include "hit.h"

class Sphere {
public:
    Vec3 center; //中心位置
    double radius; //半径

    Sphere(const Vec3 &_center, double _radius) : center(_center), radius(_radius) {};

    //rayと交差しているか判定する。交差している場合は衝突情報をhitに格納する
    bool intersect(const Ray &ray, Hit &hit) const {
        //二次方程式の係数
        double b = dot(ray.direction, ray.origin - center);
        double c = (ray.origin - center).length2() - radius * radius;
        //判別式
        double D = b * b - c;

        //解の候補距離
        //t1 <= t2
        double t1 = -b - std::sqrt(D);
        double t2 = -b + std::sqrt(D);

        // t1 <= t2
        if (t1 > ConstParam::HIT_DISTANCE_MAX)
            return false;
        if (t2 < ConstParam::HIT_DISTANCE_MIN)
            return false;
        if (t1 < ConstParam::HIT_DISTANCE_MIN & ConstParam::HIT_DISTANCE_MAX < t2)
            return false;

        double t;

        if (t1 > ConstParam::HIT_DISTANCE_MIN)
            t = t1;
        else{
            t = t2;
        }

        //衝突情報を格納
        hit.t = t;
        hit.hit_pos = ray(t);
        hit.hit_normal = normalize(hit.hit_pos - center);
        hit.hit_sphere = this;

        return true;
    };
};

#endif //PRACTICEPATHTRACING_SPHERE_H
