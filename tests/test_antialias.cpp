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
#include "utils.hpp"
#include "omp.h"


TEST(ANTIALIAS_TEST, AGGREGATE) {
    Image<RGBPixel> img(256 * 4, 144 * 4);
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 0.8, 1.6 * 0.5, 0.9 * 0.5);
    //PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1, 1, 1);

    Aggregate aggregate = Aggregate();
    aggregate.add(std::make_shared<Sphere>(Sphere(Vec3(0, 0, -5), 1)));
    aggregate.add(std::make_shared<Sphere>(Sphere(Vec3(0, -10001, 0), 10000)));

    int myid, nthreads;
    nthreads = omp_get_num_threads();
    std::cout << "nthreads: " << nthreads << std::endl;

    #pragma omp parallel for default(img)
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
                    //RGBPixel pixel = color.pixalize();
                    //img.write_pixel(i, j, pixel);
                }else {
                    color = Color();
                    //RGBPixel pixel = RGBPixel();
                    //img.write_pixel(i, j, pixel);
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


//                if (aggregate.intersect(ray, hit_record)) {
//                    normal_vec += hit_record.hit_normal;
//                }
//            }
//
//            normal_vec = normal_vec / SUPER_SAMPLING;
//            Color color = vec_2_color(normal_vec);
//            RGBPixel pixel = color.pixalize();
//            img.write_pixel(i, j, pixel);

