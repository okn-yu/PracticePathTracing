/*
 * Created by okn-yu on 2022/06/17.
 */

#ifndef PRACTICEPATHTRACING_DIFFUSE_H
#define PRACTICEPATHTRACING_DIFFUSE_H

#include "color.hpp"
#include "material.hpp"
#include "utils.hpp"
#include "vec3.hpp"


class Mirror : public Material {
public:
    Mirror() {};

    Vec3 sample(Vec3 &wi, const Vec3 &wo, float &pdf) const {
        wi = reflect(wo, Vec3(0, 1, 0));
        pdf = 1.0;
        return Vec3(1 / cos_theta(wi));
    };
};

#endif //PRACTICEPATHTRACING_DIFFUSE_H
