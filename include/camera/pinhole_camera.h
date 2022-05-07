//
// Created by okn-yu on 2022/05/05.
//

#ifndef PRACTICEPATHTRACING_PINHOLE_CAMERA_H
#define PRACTICEPATHTRACING_PINHOLE_CAMERA_H

#include "camera.h"

class PinholeCamera : public Camera {
public:
    double pinhole_dist; //イメージセンサーの中心位置からピンホールまでの距離

    PinholeCamera(const Vec3 &_camPos, const Vec3 &_camForward, double _pinhole_dist) : Camera(_camPos, _camForward),
                                                                                       pinhole_dist(_pinhole_dist) {};
    //イメージセンサー上の画素(u, v)に対応するRayを返す関数
    //u, vは-1~1の値をとる
    Ray getRay(double u, double v) const {
        //カメラ座標系におけるピンホールの位置
        //こちらは(u, v)に依存せず、カメラ座標系とカメラの内部パラメータのpihholeDistにのみ依存する
        Vec3 pinhole_pos = cam_pos + pinhole_dist * cam_forward;
        //カメラ座標系における(u, v)に対応するセンサー上の位置
        //cam_rightとcam_upは正規化されていることに注意
        Vec3 u_v_sensor_pos = cam_pos + u * cam_right + v * cam_up;

        //Ray(const Vec3& _origin, const Vec3& _direction)
        //sensor_pos: Rayの原点
        //normalize(pinhole_pos - sensor_pos): Rayの方向
        return Ray(u_v_sensor_pos, normalize(pinhole_pos - u_v_sensor_pos));
    };
};

#endif //PRACTICEPATHTRACING_PINHOLE_CAMERA_H
