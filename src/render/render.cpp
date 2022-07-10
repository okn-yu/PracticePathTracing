/*
 * Created by okn-yu on 2022/06/17.
 *
 * カメラから出る最初のRayのinit_rayを受け取り最終的な放射輝度を計算する
 * BRDFはローカル系で計算を行う
 *
 * 物体の反射が続き光源に届かない場合は最大でMAX_DEPTH回の計算を行う
 * 結局のところ無限級数としてのレンダリング方程式は(BRDF * cos / pdf)を衝突回数だけ積算した形式になっている
 * throughputは上記のレンダリング方程式の計算結果を格納している項
 *
 */

#ifndef PRACTICEPATHTRACING_RENDER_H
#define PRACTICEPATHTRACING_RENDER_H

#include "object/aggregate.hpp"
#include "core/config.hpp"
#include "object/hit.hpp"
#include "core/ray.hpp"
#include "background/sky.hpp"
#include "core/utils.hpp"
#include "core/vec3.hpp"

Vec3 radiance(const Ray &init_ray, const Aggregate &aggregate, Sky &sky) {
    Vec3 output_color;
    Vec3 throughput(1);
    Ray ray = init_ray;

    for (int depth = 0; depth < MAX_DEPTH; depth++) {
        HitRecord res;

        if (aggregate.intersect(ray, res)) {
            Vec3 n = res.hit_normal;
            Vec3 s, t;
            orthonormal_basis(n, s, t);

            Vec3 wo_local = world_2_local(-ray.direction, s, n, t);

            auto hit_material = res.hit_object->material;
            auto hit_light = res.hit_object->light;

            // この項はhit_light->colorがゼロではない自発光の物体でのみ有効となる
            output_color += throughput * hit_light->color;

            Vec3 brdf;
            Vec3 wi_local;
            float pdf;
            brdf = hit_material->sample(wo_local, wi_local, pdf);
            float cos = abs_cos_theta(wi_local);

            Vec3 wi_world = local_2_world(wi_local, s, n, t);
            throughput *= (brdf * cos) / pdf;
            //ray = Ray(res.hit_pos + 0.001 * res.hit_normal, wi_world);
            ray = Ray(res.hit_pos, wi_world);

        } else {
            output_color += throughput * sky.getRadiance(ray);
            break;
        }

        if (rnd() >= ROULETTE) {
            break;
        } else {
            throughput /= ROULETTE;
        }

    }
    return output_color;
}

Vec3 radiance(const Ray &init_ray, const Aggregate &aggregate) {
    Vec3 output_color;
    Vec3 throughput(1);
    Ray ray = init_ray;

    for (int depth = 0; depth < MAX_DEPTH; depth++) {
        HitRecord res;

        if (aggregate.intersect(ray, res)) {
            Vec3 n = res.hit_normal;
            Vec3 s, t;
            orthonormal_basis(n, s, t);

            Vec3 wo_local = world_2_local(-ray.direction, s, n, t);

            auto hit_material = res.hit_object->material;
            auto hit_light = res.hit_object->light;

            // この項はhit_light->colorがゼロではない自発光の物体でのみ有効となる
            output_color += throughput * hit_light->color;

            Vec3 brdf;
            Vec3 wi_local;
            float pdf;
            brdf = hit_material->sample(wo_local, wi_local, pdf);
            float cos = abs_cos_theta(wi_local);

            Vec3 wi_world = local_2_world(wi_local, s, n, t);
            throughput *= (brdf * cos) / pdf;
            //ray = Ray(res.hit_pos + 0.001 * res.hit_normal, wi_world);
            ray = Ray(res.hit_pos, wi_world);

        } else {
            output_color += throughput * Vec3(1);
            break;
        }

        if (rnd() >= ROULETTE) {
            break;
        } else {
            throughput /= ROULETTE;
        }

    }
    return output_color;
}

#endif //PRACTICEPATHTRACING_RENDER_H