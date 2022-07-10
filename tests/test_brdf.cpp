/*
 * Created by okn-yu on 2022/06/11.
 */


#include <gtest/gtest.h>
#include <memory>
#include "object/aggregate.hpp"
#include "core/color.hpp"
#include "image/image.hpp"
#include "materials/diffuse.hpp"
#include "lights/light.hpp"
#include "camera/pinhole_camera.hpp"
#include "render/render.cpp"
#include "object/sphere.hpp"
#include "core/utils.hpp"
#include "core/vec3.hpp"

TEST(BRDF_TEST, BRDF) {
    Image<RGBPixel> img(256 * 4, 144 * 4);
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 0.6, 1.6 * 0.5, 0.9 * 0.5);

    //auto mat1 = std::make_shared<Mirror>();
    auto mat1 = std::make_shared<Diffuse>(Vec3(1, 0, 0));
    auto mat2 = std::make_shared<Diffuse>(Vec3(0.2, 0.2, 0.8));

    auto light1 = std::make_shared<PointLight>(Vec3(0));
    auto light2 = std::make_shared<PointLight>(Vec3(0.2, 0.2, 0.8));

    Aggregate aggregate = Aggregate();
    aggregate.add(std::make_shared<Sphere>(Sphere(Vec3(0, 0, -6), 1, mat2, light2)));
    aggregate.add(std::make_shared<Sphere>(Sphere(Vec3(0, -10001, 0), 10000, mat1, light1)));

    #pragma omp parallel for schedule(dynamic, 1)
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            Vec3 avg_color = Vec3();
            for (int k = 0; k < SUPER_SAMPLING; k++) {
                float u = (2.0f * (i + rnd()) - img.width) / img.width;
                float v = (2.0f * (j + rnd()) - img.height) / img.height;
                Ray init_ray = cam.shoot(u, v);
                Vec3 color = radiance(init_ray, aggregate);
                avg_color += color;

            }

            // std::cout << "avg_color: " << avg_color << std::endl;

            avg_color /= SUPER_SAMPLING;
            Color avg_color2 = Color(avg_color.x(), avg_color.y(), avg_color.z());
            RGBPixel pixel = avg_color2.pixalize();
            img.write_pixel(i, j, pixel);
        }
        img.png_output("brdf_test.png", 3);
    }
}