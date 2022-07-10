/*
 * Created by okn-yu on 2022/06/11.
 */


#include <gtest/gtest.h>
#include "aggregate.hpp"
#include "core/color.hpp"
#include "diffuse.hpp"
#include "image.hpp"
#include "light.hpp"
#include "mirror.hpp"
#include "omp.h"
#include "pinhole_camera.h"
#include "sphere.hpp"
#include "core/utils.hpp"
#include "core/vec3.hpp"

TEST(ANTIALIAS_TEST, AGGREGATE) {
    Image<RGBPixel> img(256 * 4, 144 * 4);
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 0.8, 1.6 * 0.5, 0.9 * 0.5);
    //PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1, 1, 1);

    //Aggregate aggregate = Aggregate();
    //aggregate.add(std::make_shared<Sphere>(Sphere(Vec3(0, 0, -5), 1)));
    //aggregate.add(std::make_shared<Sphere>(Sphere(Vec3(0, -10001, 0), 10000)));

    auto mat1 = std::make_shared<Diffuse>(Vec3(0.9));
    auto mat2 = std::make_shared<Diffuse>(Vec3(0.2, 0.2, 0.8));

    auto light1 = std::make_shared<PointLight>(Vec3(0));
    auto light2 = std::make_shared<PointLight>(Vec3(0));

    Aggregate aggregate = Aggregate();
    aggregate.add(std::make_shared<Sphere>(Sphere(Vec3(0, 0, -5), 1, mat1, light1)));
    aggregate.add(std::make_shared<Sphere>(Sphere(Vec3(0, -10001, 0), 10000, mat2, light2)));

    #pragma omp parallel for schedule(dynamic, 1)
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            Color avg_color = Color();
            for (int k = 0; k < SUPER_SAMPLING; k++) {

                float u = (2.0f * (i + rnd()) - img.width) / img.width;
                float v = (2.0f * (j + rnd()) - img.height) / img.height;

                Ray ray = cam.shoot(u, v);
                HitRecord hit_record = HitRecord();
                RGBPixel pixel;
                Color color;

                if (aggregate.intersect(ray, hit_record)) {
                    Vec3 normal_vec = hit_record.hit_normal;
                    color = normal_vec_2_color(normal_vec.normalize());
                }else {
                    color = Color();
                }
                avg_color += color;
            }
            avg_color /= SUPER_SAMPLING;
            RGBPixel pixel = avg_color.pixalize();
            img.write_pixel(i, j, pixel);
        }
        img.png_output("antialias_test.png", 3);
    }
}

