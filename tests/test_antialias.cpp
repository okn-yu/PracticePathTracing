/*
 * Created by okn-yu on 2022/06/11.
 */


#include <gtest/gtest.h>
#include "vec3.hpp"
#include "image.hpp"
#include "pinhole_camera.h"
#include "color.hpp"
#include "sphere.hpp"
#include "aggregate.hpp"


TEST(ANTIALIAS_TEST, AGGREGATE) {
    Image<RGBPixel> img(256 * 4, 144 * 4);
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 0.8, 1.6*0.5, 0.9*0.5);
    //PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1, 1, 1);

    Aggregate aggregate = Aggregate();
    aggregate.add(std::make_shared<Sphere>(Sphere(Vec3(0, 0, -5), 1)));
    aggregate.add(std::make_shared<Sphere>(Sphere(Vec3(0, -10001, 0), 10000)));

#pragma omp parallel for schedule(dynamic, 1)
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            float u = (2.0f * i - img.width) / img.width;
            float v = (2.0f * j - img.height) / img.height;

            Ray ray = cam.shoot(u, v);
            HitRecord hit_record = HitRecord();

            if (aggregate.intersect(ray, hit_record)) {
                Vec3 normal_vec = hit_record.hit_normal;
                Color color = normal_vec_2_color(normal_vec.normalize());
                RGBPixel pixel = color.pixalize();
                img.write_pixel(i, j, pixel);
            } else {
                RGBPixel pixel = RGBPixel();
                img.write_pixel(i, j, pixel);
            }
        }
    }
    img.png_output("antialias_test.png", 3);
}

