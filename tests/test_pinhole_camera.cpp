/*
 * Created by okn-yu on 2022/05/06.
 */
#include <gtest/gtest.h>
#include "vec3.hpp"
#include "image.hpp"
#include "pinhole_camera.h"

// 慣例とは逆にカメラの視線方向は(0, 0, 1)
TEST(PINHOLE_CAMERA_TEST, VEC_TEST1){
    Image<RGBPixel> img(256, 256);
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, 1), 1);

    EXPECT_EQ(cam.cam_right_vec, Vec3(1, 0, 0));
    EXPECT_EQ(cam.cam_up_vec, Vec3(0, 1, 0));
}

// 慣例と同じくカメラの視線方向は(0, 0, -1)
// cam_right_vecが(-1, 0, 0)とり、cam_upは変わらない
// つまりy軸を中心にして反時計周りに180度回転したことに相当する
// ここはいまいちしっくりと来ない
TEST(PINHOLE_CAMERA_TEST, VEC_TEST2){
    Image<RGBPixel> img(256, 256);
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1);

    EXPECT_EQ(cam.cam_right_vec, Vec3(-1, 0, 0));
    EXPECT_EQ(cam.cam_up_vec, Vec3(0, 1, 0));
}

/*TEST(PINHOLE_CAMERA_TEST, PNG){
    Image<RGBPixel> img(256, 256);
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1);

    for(int i = 0; i < img.width; i++) {
        for(int j = 0; j < img.height; j++) {
            double u = (2.0*i - img.width)/img.width;
            double v = (2.0*j - img.height)/img.height;

            Ray ray = cam.getRay(-u, -v);
            Vec3 Color = Vec3((ray.direction + 1.0)/2.0);
            RGBPixel col(int(Color.x()*100), int(Color.y()*100), int(Color.z()*100));

            //画素(i, j)に色を書き込む
            img.write_pixel(i, j, col);
        }
    }
    img.png_output("pinhole_test.png", 3);

}*/
