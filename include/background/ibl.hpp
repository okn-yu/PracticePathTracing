/*
 * Created by okn-yu on 2022/07/02.
 */

/*
 * IBL: Image Base Lighting
 * 現実世界の全方向の光情報をキャプチャした画像を光源として用いるレンダリングの手法
 *
 * SDR: Standard Dynamic Range
 * HDR: High Dynamic Range
 * https://www.eizo.co.jp/eizolibrary/color_management/hdr/
 *
 * ダイナミックレンジ:
 * カメラが再現できることができる明るさの幅
 * 人の視覚が捉えることの可能な輝度（明るさ）の範囲は10^-6 ~ 10^6まで
 * つまりダイナミックレンジは10^12に及ぶ
 * 従来のSDRのダイナミックレンジは10^3程度
 * カメラのダイナミックレンジに収まらなかった場合は、色が潰れる（白飛び、黒つぶれ）
 *
 * 一方HDRのダイナミックレンジは10^5程度
 * 従来よりも100倍程度の明るさを捉えることができ、より肉眼に近い陰影を表現できる
 *
 * HDRはカメラで複数帯域のダイナミックレンジを合成することで実現しているらしい
 */


#ifndef PRACTICEPATHTRACING_IBL_H
#define PRACTICEPATHTRACING_IBL_H

#include <string>
#include "core/ray.hpp"
#include "background/sky.hpp"
#include "core/vec3.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

        class IBL : public Sky {
        public:
            int width;
            int height;

            float *hdr_image; // stbi_loadfの返り値はfloatの配列

            IBL(const std::string &filename) {
                int n;
                hdr_image = stbi_loadf(filename.c_str(), &width, &height, &n, 0);
            };

            ~IBL() {
                stbi_image_free(hdr_image);
            }

            Vec3 getRadiance(const Ray &ray) const override {
                float theta = std::acos(ray.direction.y());
                float phi = std::atan2(ray.direction.z(), ray.direction.x());
                if (phi < 0) phi += 2 * M_PI;
                int i = (phi / (2 * M_PI)) * width;
                int j = (theta / M_PI) * height;
                int index = 3 * i + 3 * width * j;

                return Vec3(hdr_image[index], hdr_image[index + 1], hdr_image[index + 2]);
            }
        };

#endif //PRACTICEPATHTRACING_IBL_H