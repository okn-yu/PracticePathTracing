/*
 * Created by okn-yu on 2022/05/05.
 * カメラは3次元の物体を2次元に投影する透視投影を利用する
 * 視点はカメラのレンズ
 * 投影面上に3次元の物体が投影されている
 * センサーのアスペクト比と投影面のアスペクト比は一致する
 * https://cc.musabi.ac.jp/zoukei_file/03/seizu/NewFiles/touei.html
 */

#ifndef PRACTICEPATHTRACING_CAMERA_H
#define PRACTICEPATHTRACING_CAMERA_H

#include "vec3.hpp"
#include "ray.hpp"

/*
 * Cameraの位置と視線方向が定まればセンサーの平面は（視線を回転軸として回転の自由度はあるものの）定まる
 * センサー平面で上方向と横方向を定義すればセンサーの配置は一位に定まる
 * センサーの縦方向はワールド座標の上向き（y軸正）の単位ベクトルを回転面に射影してい取得する
 * センサーの横方向は視線方向と上方向の外積経由で取得する
 * センサーの大きさを極端に小さくするとRayの射出角度が狭くなるので、非常に狭い範囲のみしか撮影できなくなる
 * センサーから投影点までの距離が遠いと画角が狭くなり近いと画角が広くなる
 */

class Camera {
public:
    Vec3 cam_pos; // center of sensor
    Vec3 cam_sight_vec;
    Vec3 cam_right_vec;
    Vec3 cam_up_vec;
    float sensor_height;
    float sensor_width;
    float sensor_distance;
    float aspect_ratio;

    Camera(const Vec3 &_cam_pos, const Vec3 &_cam_sight_vec) : cam_pos(_cam_pos){
        // ベクトルの外積は右ねじの向き
        cam_sight_vec = _cam_sight_vec.normalize();
        cam_up_vec = cross(cam_sight_vec, Vec3(0, 1, 0)).normalize();
        cam_right_vec = cross(cam_sight_vec, cam_up_vec).normalize();
    };

    /*
     * センサー上の座標(u, v)に対応したRayを返す
     * virtualは仮想関数
     * 仮想関数にしないと継承した子クラスの処理は親クラスの処理を上書きできない
     * const = 0; は仮想関数を記載する際のお約束
     */
    virtual Ray getRay(double u, double v) const = 0;
};

#endif //PRACTICEPATHTRACING_CAMERA_H
