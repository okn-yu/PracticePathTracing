/*
 * Created by okn-yu on 2022/06/30.
 */

#ifndef PRACTICEPATHTRACING_GLASS_H
#define PRACTICEPATHTRACING_GLASS_H

#include "core/color.hpp"
#include "materials/material.hpp"
#include "core/utils.hpp"
#include "core/vec3.hpp"

class Glass : public Material {
public:
    // ior(屈折率): Index Of Refraction
    float ior;

    Glass(float _ior) : ior(_ior) {};

    Vec3 sample(const Vec3 &wo, Vec3 &wi, float &pdf) const {

        bool is_ray_from_out = cos_theta(wo) > 0;
        float n_out; // n1: 入射光の媒質の屈折率
        float n_in; // n2: 屈折光の媒質の屈折率
        Vec3 normal;

        if (is_ray_from_out) {
            n_out = 1.0;
            n_in = ior;
            normal = Vec3(0, 1, 0);
        } else {
            n_out = ior;
            n_in = 1.0;
            normal = Vec3(0, -1, 0);
        }

        // fresnelと入射および出射の方向が異なることに注意
        float fr = fresnel(wo, normal, n_out, n_in);

        // 反射
        if (rnd() < fr) {
            wi = reflect(wo, normal);
            pdf = fr;

            return fr / abs_cos_theta(wi) * Vec3(1);
        } else{
            // 屈折
            if (reflect(wo, wi, normal, n_out, n_in)) {
                pdf = 1 - fr;

                return std::pow(n_out / n_in, 2.0) * ((1 - fr) / abs_cos_theta(wi)) * Vec3(1);
            } else {
                // 全反射
                wi = reflect(wo, normal);
                pdf = 1 - fr;

                return (1 - fr) / abs_cos_theta(wi) * Vec3(1);
            }
        }
    }
};

#endif //PRACTICEPATHTRACING_GLASS_H
