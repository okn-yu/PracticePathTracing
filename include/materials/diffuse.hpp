/*
 * Created by okn-yu on 2022/06/17.
 *
 * base_color:
 * 光の各波長（単純化のためRGBのみを扱う）に対してどの程度反射するかを表す
 * base_colorが(0, 0, 0)ならば常に黒となる
 * base_colorが(1, 1, 1)でも光がR成分のみだと赤くなる
 * 拡散反射の場合物体のbase_colorの効果はbrdfに現れる
 *
 * 拡散反射のbrdfは以下のベクトルで与えられる
 * base_color/pi
 *
 */

#ifndef PRACTICEPATHTRACING_DIFFUSE_H
#define PRACTICEPATHTRACING_DIFFUSE_H

#include "color.hpp"
#include "material.hpp"
#include "utils.hpp"
#include "vec3.hpp"

class Diffuse : public Material {
public:
    Vec3 base_color;

    Diffuse(const Vec3 &_base_color) : base_color(_base_color) {};

    Vec3 sample(const Vec3 &wo, Vec3 &wi, float &pdf) const override{
        float u = rnd();
        float v = rnd();

        float theta = 0.5 * std::acos(1 - 2 * u);
        float phi = 2 * M_PI * v;

        float x = std::cos(phi) * std::sin(theta);
        float y = std::cos(theta);
        float z = std::sin(phi) * std::sin(theta);

        wi = Vec3(x, y, z);
        pdf = std::cos(theta) / M_PI;

        //std::cout << "pdf: " << pdf << std::endl;
        //std::cout << "return: " << (base_color / M_PI) << std::endl;

        return (base_color / M_PI);

    };
};

#endif //PRACTICEPATHTRACING_DIFFUSE_H
