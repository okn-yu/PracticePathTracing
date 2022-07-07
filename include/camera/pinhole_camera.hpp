/*
 * Created by okn-yu on 2022/05/05.
 * ピンホールカメラは理論的には無限小の点を持つ
 * レンズがないため全ての距離に対してピントがあっている
 * レンズがないため焦点距離という概念がない
 * 実際は点の大きさは有限であるため像にぼけが生じる
 * さらにレンズを用いていないため撮影時の露光時間が長くなってしまう
 */

#ifndef PRACTICEPATHTRACING_PINHOLE_CAMERA_H
#define PRACTICEPATHTRACING_PINHOLE_CAMERA_H

#include <cassert>
#include <cmath>
#include "camera.hpp"

class PinholeCamera : public Camera {
public:

    PinholeCamera(const Vec3 &_camPos, const Vec3 &_cam_sight_vec, float _sensor_dist, float _sensor_width,
                  float _sensor_height) : Camera(_camPos,
                                                 _cam_sight_vec
    ) {
        sensor_dist = _sensor_dist;
        sensor_height = _sensor_height;
        sensor_width = _sensor_width;
    };

    /*
     * (u, v)はイメージセンサーの4隅を(1, 1), (1, -1), (-1, 1), (-1, -1)と仮定した場合のセンサー上の位置
     * sensor_widthとsensor_heightでセンサー上の座標に補正を行う
     */
    Ray shoot(float u, float v) const override {
        assert(-1 <= u && u <= 1);
        assert(-1 <= v && v <= 1);
        assert(std::abs(cam_right_vec.length() - 1) < 0.1);
        assert((std::abs(cam_up_vec.length() - 1) < 0.1));
        assert(std::abs(cam_sight_vec.length() - 1) < 0.1);

        Vec3 pinhole_pos = cam_pos + sensor_dist * cam_sight_vec;
        Vec3 uv_pos = cam_pos + u * cam_right_vec * (sensor_width / 2) + v * cam_up_vec * (sensor_height / 2);
        Ray ray = Ray(uv_pos, (pinhole_pos - uv_pos).normalize());

        return ray;
    };
};

#endif //PRACTICEPATHTRACING_PINHOLE_CAMERA_H