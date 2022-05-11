//
// Created by okn-yu on 2022/05/06.
//

#include "vec3.h"
#include "ray.h"
#include "image.h"
#include "pinhole_camera.h"

int main() {
    Image img(512, 512);
    PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1);

    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            //(u, v)の用意
            double u = (2.0 * i - img.width) / img.width;
            double v = (2.0 * j - img.height) / img.height;

            //レイの生成
            Ray ray = cam.getRay(-u, -v);

            //ピクセルに書き込む色
            Vec3 col = (ray.direction + 1.0) / 2.0;

            //画素(i, j)に色を書き込む
            img.setPixel(i, j, col);
        }
    }

    //PPM画像出力
    img.ppm_output("pinhole_test.ppm");
    std::string filename = "pinhole_test";
    std::cout << filename << std::endl;

    //TODO:support PNG output.
    //std::string cmd = "convert /home/user/tmp/clion/cmake-build-debug-remote-host/pinhole_test.ppm > /home/user/pinhole_test.png";
    //std::cout << cmd <<std::endl;
    //std::string cmd = "convert " + filename + ".ppm " + filename + ".png";
    //system(cmd.c_str());

    return 0;
}

