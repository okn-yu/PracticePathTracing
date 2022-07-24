/*
 * Created by okn-yu on 2022/05/05.
 *  複数オブジェクトの衝突判定をする場合に考慮にいれるのは最前面のオブジェクトのみ
 *  そのためtはHitRecordの生成時に最初から値を設定しておく
 */

#ifndef PRACTICEPATHTRACING_HITTABLE_H
#define PRACTICEPATHTRACING_HITTABLE_H

#include "futaba/core/config.h"
#include "futaba/core/ray.h"
#include "futaba/core/vec3.h"

class Sphere;

class HitRecord {
public:
    Vec3 hit_pos;
    Vec3 hit_normal;
    const Sphere *hit_object;
    float t;

    HitRecord() {
        t = HIT_DISTANCE_MAX;
    }
};

#endif //PRACTICEPATHTRACING_HITTABLE_H
