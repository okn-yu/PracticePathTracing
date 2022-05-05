//
// Created by okn-yu on 2022/05/05.
//

#ifndef PRACTICEPATHTRACING_PINHOLE_CAMERA_H
#define PRACTICEPATHTRACING_PINHOLE_CAMERA_H

#include "camera.h"

class PinholeCamera : public Camera {
public:
    double pinholeDist; //イメージセンサーの中心位置からピンホールまでの距離

    PinholeCamera(const Vec3 &_camPos, const Vec3 &_camForward, double _pinholeDist) : Camera(_camPos, _camForward),
                                                                                       pinholeDist(_pinholeDist) {};

    Ray getRay(double u, double v) const {
        //ピンホールの位置
        Vec3 pinholePos = cam_pos + pinholeDist * cam_forward;
        //(u, v)に対応するセンサー上の位置
        Vec3 sensorPos = cam_pos + u * cam_right + v * cam_up;

        return Ray(sensorPos, normalize(pinholePos - sensorPos));
    };
};

#endif //PRACTICEPATHTRACING_PINHOLE_CAMERA_H
