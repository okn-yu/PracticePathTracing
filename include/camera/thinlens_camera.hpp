/*
 * Created by okn-yu on 2022/07/04.
 *
 * 薄レンズモデル:
 * 薄レンズ1枚を用いたガメラモデル
 * 実際のカメラは複数枚のレンズの組み合わせからなる
 *
 * ピンホールカメラとの差分:
 * ピンホールカメラでは光はすべて面積0のピンホールを通過するためボケは一切生じない
 * 一方薄レンズモデルでは光がある程度の領域を通過するためボケが発生する
 * ピンホールカメラではfocus_planeを考慮する必要はないが、薄レンズモデルでは考慮する必要がある
 *
 * 薄レンズモデルの特徴:
 * レンズの中心を通る光は直進する
 * 光軸に並行に入射した光は焦点を通るように屈折する
 * 焦点を通過してレンズに入射した光は、光軸に並行となるように屈折する（上の逆の経路）
 *
 * ボケが発生する理由:
 * ピンホールカメラ:外部のオブジェクトとイメージセンサがレイを通して1:1に対応している
 * 薄レンズ:外部のオブジェクトとイメージセンサがレイを通して1:1に対応していない
 *
 * ボケに影響を与えるパラメータ
 * カメラの焦点距離: 長いほど撮影した画像はボケる
 * カメラのレンズの半径: 半径が0ならボケは生じない
 */

#ifndef PRACTICEPATHTRACING_THINLENS_CAMERA_H
#define PRACTICEPATHTRACING_THINLENS_CAMERA_H

#include <cassert>
#include <cmath>
#include "camera.hpp"
#include "utils.hpp"
#include "vec3.hpp"

void sample_disk(float &x, float &y) {
    float r = rnd();
    float theta = rnd();
    x = std::sqrt(r) * std::cos(2 * M_PI * theta);
    y = std::sqrt(r) * std::sin(2 * M_PI * theta);
}

class ThinLensCamera : public Camera {
public:
    /*
     * a: イメージセンサーからレンズの中心までの距離
     * b: レンズ中心からピント平面までの距離
     * f: 焦点距離
     * lens_radius: レンズの半径（ボケ具合に影響する）
     *
     * aとfが与えられればbは自動的に定まる
     * 下の実装ではaとfocus_pointを与えて、bとfは両者から算出する
     */
    float a;
    float b;
    float f;
    float lens_radius;
    Vec3 lens_center;

    ThinLensCamera(
            const Vec3 &_camPos,
            const Vec3 &_cam_sight_vec,
            const Vec3 &focus_point,
            float _a,
            float _lens_radius,
            float _sensor_dist,
            float _sensor_width,
            float _sensor_height
    ) : Camera(_camPos, _cam_sight_vec), a(_a), lens_radius(_lens_radius) {
        float cos = dot(cam_sight_vec, (focus_point - cam_pos).normalize());
        b = cos * (focus_point - cam_pos).length() - a;
        assert(b > 0);

        f = 1 / ((1 / a) + (1 / b));
        lens_center = cam_pos + a * cam_sight_vec;
        sensor_dist = _sensor_dist;
        sensor_height = _sensor_height;
        sensor_width = _sensor_width;
    };

    /*
     * 注意
     * レイはイメージセンサー上からではなくレンズ上から射出されることとなる
     * 射出点はレンズ上からランダムにサンプリングされる
     * イメージセンサー上の点はピント平面を算出するのに用いられる
     * これはレンズ上の様々な点の光がイメージセンサーの同一の点に集まること対応している
     */

    Ray shoot(float u, float v) const override {
        // イメージセンサー上の点
        Vec3 uv_pos = cam_pos + u * cam_right_vec * (sensor_width / 2) + v * cam_up_vec * (sensor_height / 2);
        // イメージセンサー上の点からレンズ中心までの方向ベクトル
        Vec3 r = (lens_center - uv_pos).normalize();
        // ベクトルrがピント平面と交差する位置
        Vec3 pf = cam_pos + ((a + b) / dot(cam_sight_vec, r)) * r;

        // レンズ上の点をランダムにサンプリングする
        float x, y;
        sample_disk(x, y);

        // レンズ上のレイの射出点
        Vec3 l = lens_center + lens_radius * (x * cam_right_vec + y * cam_up_vec);
        Ray ray = Ray(l, (pf - l).normalize());

        return ray;
    }
};

#endif //PRACTICEPATHTRACING_THINLENS_CAMERA_H
