/*
 * Created by okn-yu on 2022/05/05.
 * HitRecord構造体のメンバ変数のhit_normalの使いみちが不明
 * メンバ変数のtもRayと密結合しているのが気になる
 *  複数オブジェクトの衝突判定をする場合に考慮にいれるのは最前面のオブジェクトのみ
 *  そのためtはHitRecordの生成時に最初から値を設定しておく
 */

#ifndef PRACTICEPATHTRACING_HITTABLE_H
#define PRACTICEPATHTRACING_HITTABLE_H

#include "config.hpp"
#include "ray.hpp"
//#include "sphere.hpp"
#include "vec3.hpp"

class Sphere;

class HitRecord {
public:
    Vec3 hit_pos;
    Vec3 hit_normal;
    const Sphere * hit_object;
    float t;

    HitRecord() {
        t = HIT_DISTANCE_MAX;
    }
};

#endif //PRACTICEPATHTRACING_HITTABLE_H
