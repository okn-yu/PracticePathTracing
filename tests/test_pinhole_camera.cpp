/*
 * Created by okn-yu on 2022/05/06.
 */
#include <gtest/gtest.h>
#include "vec3.hpp"
#include "image.hpp"
#include "pinhole_camera.h"
#include "color.hpp"
#include "sphere.hpp"

// 慣例とは逆にカメラの視線方向は(0, 0, 1)
TEST(PINHOLE_CAMERA_TEST, VEC_TEST1) {
    Image<RGBPixel> img(256, 256);
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, 1), 1, 2, 2);

    EXPECT_EQ(cam.cam_right_vec, Vec3(1, 0, 0));
    EXPECT_EQ(cam.cam_up_vec, Vec3(0, 1, 0));
}

// 慣例と同じくカメラの視線方向は(0, 0, -1)
// cam_right_vecが(-1, 0, 0)とり、cam_upは変わらない
// つまりy軸を中心にして反時計周りに180度回転したことに相当する
// カメラの視線方向を反転しても右手系で扱っているのが原因
TEST(PINHOLE_CAMERA_TEST, VEC_TEST2) {
    Image<RGBPixel> img(256, 256);
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1, 2, 2);

    EXPECT_EQ(cam.cam_right_vec, Vec3(-1, 0, 0));
    EXPECT_EQ(cam.cam_up_vec, Vec3(0, 1, 0));
}

TEST(PINHOLE_CAMERA_TEST, SQUSRE_RED_IMG) {
    Image<RGBPixel> img(256, 256);
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1, 2, 2);

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
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1, 2, 2);

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
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1, 2, 2);

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
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1, 2, 2);

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

TEST(PINHOLE_CAMERA_TEST, SENSOR_SIZE) {
    Image<RGBPixel> img(256, 144);
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1, 1.6, 0.9);

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
    img.png_output("sensor_size_test.png", 3);
}

TEST(PINHOLE_CAMERA_TEST, NORMAL_IMSGE) {
    Image<RGBPixel> img(256*2, 144*2);
    PinholeCamera cam(Vec3(0, 5, 0), Vec3(0, -1, -1), 0.8, 1.6*0.5, 0.9*0.5);
    Sphere sphere = Sphere(Vec3(0, 0, -5), 1);

    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            float u = (2.0f * i - img.width) / img.width;
            float v = (2.0f * j - img.height) / img.height;

            Ray ray = cam.shoot(u, v);
            HitRecord hit_record;
            if(sphere.is_hittable(ray, hit_record)){
                Vec3 normal_vec = hit_record.hit_normal;
                Color color = vec_2_color(normal_vec.normalize());
                RGBPixel pixel = color.pixalize();
                img.write_pixel(i, j, pixel);

            }else{
                RGBPixel pixel = RGBPixel();
                img.write_pixel(i, j, pixel);
            }
        }
    }
    img.png_output("normal_test.png", 3);
}

/*
 *   下のケースではcam_right_vecおよびcam_up_vecがnanとなってしまう
TEST(PINHOLE_CAMERA_TEST, NORMAL_IMSGE2) {
    Image<RGBPixel> img(256*2, 144*2);
    PinholeCamera cam(Vec3(0, 5, -4), Vec3(0, -1, 0), 0.8, 1.6*0.5, 0.9*0.5);
    Sphere sphere = Sphere(Vec3(0, 0, -5), 1);

    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            float u = (2.0f * i - img.width) / img.width;
            float v = (2.0f * j - img.height) / img.height;

            Ray ray = cam.shoot(u, v);
            HitRecord hit_record;
            if(sphere.is_hittable(ray, hit_record)){
                Vec3 normal_vec = hit_record.hit_normal;

                if(normal_vec.length() != 1){
                    std::cout << 'error happened.' << std::endl;
                }
                Color color = vec_2_color(normal_vec.normalize());
                RGBPixel pixel = color.pixalize();
                img.write_pixel(i, j, pixel);

            }else{
                RGBPixel pixel = RGBPixel();
                img.write_pixel(i, j, pixel);
            }
        }
    }
    img.png_output("normal_test2.png", 3);
}
*/

TEST(PINHOLE_CAMERA_TEST, NORMAL_IMSGE3) {
    Image<RGBPixel> img(256*2, 144*2);
    PinholeCamera cam(Vec3(5, 0, -5), Vec3(-1, 0, 0), 0.8, 1.6*0.5, 0.9*0.5);
    Sphere sphere = Sphere(Vec3(0, 0, -5), 1);

    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            float u = (2.0f * i - img.width) / img.width;
            float v = (2.0f * j - img.height) / img.height;

            Ray ray = cam.shoot(u, v);
            HitRecord hit_record;
            if(sphere.is_hittable(ray, hit_record)){
                Vec3 normal_vec = hit_record.hit_normal;
                Color color = vec_2_color(normal_vec.normalize());
                RGBPixel pixel = color.pixalize();
                img.write_pixel(i, j, pixel);
            }else{
                RGBPixel pixel = RGBPixel();
                img.write_pixel(i, j, pixel);
            }
        }
    }
    img.png_output("normal_test3.png", 3);
}