/*
 * Created by okn-yu on 2022/05/06.
 */
#include <gtest/gtest.h>
#include "vec3.hpp"
#include "image.hpp"
#include "pinhole_camera.h"
#include "color.hpp"

// 慣例とは逆にカメラの視線方向は(0, 0, 1)
TEST(PINHOLE_CAMERA_TEST, VEC_TEST1) {
    Image<RGBPixel> img(256, 256);
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, 1), 1);

    EXPECT_EQ(cam.cam_right_vec, Vec3(1, 0, 0));
    EXPECT_EQ(cam.cam_up_vec, Vec3(0, 1, 0));
}

// 慣例と同じくカメラの視線方向は(0, 0, -1)
// cam_right_vecが(-1, 0, 0)とり、cam_upは変わらない
// つまりy軸を中心にして反時計周りに180度回転したことに相当する
// カメラの視線方向を反転しても右手系で扱っているのが原因
TEST(PINHOLE_CAMERA_TEST, VEC_TEST2) {
    Image<RGBPixel> img(256, 256);
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1);

    EXPECT_EQ(cam.cam_right_vec, Vec3(-1, 0, 0));
    EXPECT_EQ(cam.cam_up_vec, Vec3(0, 1, 0));
}

TEST(PINHOLE_CAMERA_TEST, SQUSRE_RED_IMG) {
    Image<RGBPixel> img(256, 256);
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1);

    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            Color color = vec_2_color(Vec3(1, 0, 0));
            RGBPixel pixel = color.pixalize();

            img.write_pixel(i, j, pixel);
        }
    }
    img.png_output("red_test.png", 3);
}

TEST(PINHOLE_CAMERA_TEST, SQUSRE_GREEN_IMG) {
    Image<RGBPixel> img(256, 256);
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1);

    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            Color color = vec_2_color(Vec3(0, 0, 1));
            RGBPixel pixel = color.pixalize();

            img.write_pixel(i, j, pixel);
        }
    }
    img.png_output("green_test.png", 3);
}

TEST(PINHOLE_CAMERA_TEST, SQUSRE_BLUE_IMG) {
    Image<RGBPixel> img(256, 256);
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1);

    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            Color color = vec_2_color(Vec3(0, 0, 1));
            RGBPixel pixel = color.pixalize();

            img.write_pixel(i, j, pixel);
        }
    }
    img.png_output("blue_test.png", 3);
}

TEST(PINHOLE_CAMERA_TEST, RAY_DIRECTION_IMG) {
    Image<RGBPixel> img(256, 256);
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1);

    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            float u = (2.0f * i - img.width) / img.width;
            float v = (2.0f * j - img.height) / img.height;

            Ray ray = cam.shoot(u, v);

            Color color = vec_2_color(ray.direction.normalize());

            RGBPixel pixel = color.pixalize();

            img.write_pixel(i, j, pixel);
        }
    }
    img.png_output("ray_direction_test.png", 3);
}
