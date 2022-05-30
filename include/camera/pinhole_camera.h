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

#include "camera.h"

class PinholeCamera : public Camera {
public:
    double sensor_dist; //イメージセンサーの中心位置からピンホールまでの距離

    PinholeCamera(const Vec3 &_camPos, const Vec3 &_cam_sight_vec, double _sensor_dist) : Camera(_camPos,
                                                                                                 _cam_sight_vec),
                                                                                          sensor_dist(_sensor_dist) {};

    //イメージセンサー上の画素(u, v)に対応するRayを返す関数
    Ray getRay(double u, double v) const {
        Vec3 pinhole_pos = cam_pos + sensor_dist * cam_sight_vec;
        Vec3 u_v_pos = cam_pos + u * cam_right_vec + v * cam_up_vec;

        return Ray(u_v_pos, (pinhole_pos - u_v_pos).normalize());
    };
};

#endif //PRACTICEPATHTRACING_PINHOLE_CAMERA_H