//
// Created by okn-yu on 2022/05/05.
//

#ifndef PRACTICEPATHTRACING_HIT_H
#define PRACTICEPATHTRACING_HIT_H

#include "config.h"
#include "vec3.h"
//#include "sphere.h"

const int ConstParam::HIT_DISTANCE_MIN = 0;
const int ConstParam::HIT_DISTANCE_MAX = 10000;


//Sphereクラスのプロトタイプ宣言
//単純にincludeすると循環参照になってしまうため
class Sphere;


class Hit {
public:
    double t;
    Vec3 hit_pos;
    Vec3 hit_normal;
    const Sphere* hit_sphere;

    Hit() {
        t = ConstParam::HIT_DISTANCE_MAX;
    };
};

#endif //PRACTICEPATHTRACING_HIT_H
