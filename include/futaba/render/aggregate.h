/*
 * Created by okn-yu on 2022/06/04.
 */

#ifndef PRACTICEPATHTRACING_AGGREGATE_HPP
#define PRACTICEPATHTRACING_AGGREGATE_HPP

#include <memory>
#include <vector>
#include "futaba/core/ray.h"
#include "futaba/render/hit.h"
#include "futaba/render/sphere.h"

class Aggregate {
public:
    std::vector<std::shared_ptr<Sphere>> spheres;

    Aggregate() = default;;

    explicit Aggregate(const std::vector<std::shared_ptr<Sphere>> &_spheres) {
        spheres = _spheres;
    }

    void add(const std::shared_ptr<Sphere> &s) {
        spheres.push_back(s);
    }

    bool intersect(Ray &ray, HitRecord &hit_rec) const {
        bool is_hit = false;

        for (const auto &s: spheres) {
            HitRecord hit_temp = HitRecord();
            if (s->is_hittable(ray, hit_temp)) {
                if (hit_temp.t < hit_rec.t) {
                    is_hit = true;
                    hit_rec = hit_temp;
                }
            }
        }
        return is_hit;
    }
};

#endif //PRACTICEPATHTRACING_AGGREGATE_HPP
