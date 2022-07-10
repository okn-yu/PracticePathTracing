/*
 * Created by okn-yu on 2022/06/29.
 */

#ifndef PRACTICEPATHTRACING_SKY_H
#define PRACTICEPATHTRACING_SKY_H

#include "core/vec3.hpp"
#include "core/ray.hpp"

class Sky {
public:
    virtual Vec3 getRadiance(const Ray &ray) const = 0;

};

class UniformSky : public Sky {
public:
    Vec3 color;

    explicit UniformSky(const Vec3 &_color) : color(_color) {};

    Vec3 getRadiance(const Ray &ray) const override{
        return color;
    }
};

class SimpleSky : public Sky {
public:
    Vec3 color;

    explicit SimpleSky()= default;;

    Vec3 getRadiance(const Ray &ray) const override {
        float t = (ray.direction.y() + 1) / 2;
        return (1 - t) * Vec3(1) + t * Vec3(0.7, 0.8, 1);
    }
};

#endif //PRACTICEPATHTRACING_SKY_H
