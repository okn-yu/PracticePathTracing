//
// Created by okn-yu on 2022/05/05.
//

#ifndef PRACTICEPATHTRACING_CAMERA_H
#define PRACTICEPATHTRACING_CAMERA_H

#include "vec3.h"
#include "ray.h"


class Camera {
public:
    Vec3 cam_pos; //カメラの位置
    Vec3 cam_forward; //カメラの前方向
    Vec3 cam_right; //カメラの横方向
    Vec3 cam_up; //カメラの上方向

    Camera(const Vec3 &_cam_pos, const Vec3 &_cam_forward) : cam_pos(_cam_pos), cam_forward(_cam_forward) {
        orthonormalBasis(cam_forward, cam_right, cam_up);

        std::cout << "cam_pos: " << cam_pos << std::endl;
        std::cout << "cam_forward: " << cam_forward << std::endl;
        std::cout << "cam_right: " << cam_right << std::endl;
        std::cout << "cam_up: " << cam_up << std::endl;
    };


    //(u, v)を受け取り、それに対応するレイを返す
    virtual Ray getRay(double u, double v) const = 0;
};

#endif //PRACTICEPATHTRACING_CAMERA_H
