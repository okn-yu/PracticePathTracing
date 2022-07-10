/*
 * Created by okn-yu on 2022/06/27.
 */

#include <gtest/gtest.h>
#include <memory>
#include "aggregate.hpp"
#include "core/color.hpp"
#include "image.hpp"
#include "diffuse.hpp"
#include "glass.hpp"
#include "ibl.hpp"
#include "light.hpp"
#include "mirror.hpp"
#include "omp.h"
#include "pinhole_camera.h"
#include "../src/render/render.cpp"
#include "sky.hpp"
#include "sphere.hpp"
#include "core/utils.hpp"
#include "core/vec3.hpp"


TEST(IBL_TEST, IBL) {
    Image<RGBPixel> img(256 * 4, 144 * 4);
    //Image<RGBPixel> img(128 * 2, 128 * 2);
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 0.6, 1.6 * 0.5, 0.9 * 0.5);
    //PinholeCamera cam(Vec3(0, 5, 0), Vec3(0, -1, -1), 0.6, 1.6 * 0.5, 0.9 * 0.5);


    auto mat1 = std::make_shared<Diffuse>(Vec3(0.9));
    auto mat2 = std::make_shared<Glass>(1.5);
    auto mat3 = std::make_shared<Diffuse>(Vec3(0.2, 0.2, 0.8));
    auto mat4 = std::make_shared<Diffuse>(Vec3(0.2, 0.8, 0.2));
    auto mat5 = std::make_shared<Mirror>();


    auto light1 = std::make_shared<PointLight>(Vec3(0));

    Aggregate aggregate = Aggregate();
    // 床
    //aggregate.add(std::make_shared<Sphere>(Sphere(Vec3(0, -10001, 0), 10000, mat1, light1)));
    // 球
    aggregate.add(std::make_shared<Sphere>(Sphere(Vec3(2.1, 0, -6), 1, mat2, light1)));
    aggregate.add(std::make_shared<Sphere>(Sphere(Vec3(0, 0, -6), 1, mat5, light1)));
    aggregate.add(std::make_shared<Sphere>(Sphere(Vec3(-2.1, 0, -6), 1, mat2, light1)));
    //aggregate.add(std::make_shared<Sphere>(Sphere(Vec3(0, 0, -3), 1, mat5, light1)));

    //IBL sky("/tmp/tmp_/tests/10-Shiodome_Stairs_3k.hdr");
    //IBL sky("/tmp/tmp_/tests/LA_Downtown_Afternoon_Fishing_3k.hdr");
    IBL sky("/tmp/tmp_/tests/peppermint_powerplant_8k.hdr");


    //#pragma omp parallel for schedule(dynamic, 1)
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            Vec3 avg_color = Vec3();
            for (int k = 0; k < SUPER_SAMPLING; k++) {
                float u = (2.0f * (i + rnd()) - img.width) / img.width;
                float v = (2.0f * (j + rnd()) - img.height) / img.height;
                Ray init_ray = cam.shoot(u, v);
                Vec3 color = radiance(init_ray, aggregate, sky);
                avg_color += color;
            }

            if (omp_get_thread_num() == 0) {
                std::cout << double(j + i * img.height) / (img.width * img.height) * 100 << "\r" << std::flush;
            }

            avg_color /= SUPER_SAMPLING;
            Color avg_color2 = Color(avg_color.x(), avg_color.y(), avg_color.z());
            RGBPixel pixel = avg_color2.pixalize();
            img.write_pixel(i, j, pixel);
        }
        img.png_output("ibl_test.png", 3);
    }
}