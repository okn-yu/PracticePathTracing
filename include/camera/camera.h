/*
 * Created by okn-yu on 2022/05/05.
 * カメラは3次元の物体を2次元に投影する透視投影を利用する
 * 視点はカメラのレンズ
 * 投影面上に3次元の物体が投影されている
 * センサーのアスペクト比と投影面のアスペクト比は一致する
 * https://cc.musabi.ac.jp/zoukei_file/03/seizu/NewFiles/touei.html
 *
 * 座標系に関して
 * (x, y, z)はワールド座標系の正規直交基底
 * (u, v, w)はカメラ座標系の正規直交基底　
 */

#ifndef PRACTICEPATHTRACING_CAMERA_H
#define PRACTICEPATHTRACING_CAMERA_H

#include "vec3.hpp"
#include "ray.hpp"

/*
 * Cameraの位置と視線方向が定まればセンサーの平面は（視線を回転軸として回転の自由度はあるものの）定まる
 * センサー平面で上方向と横方向を定義すればセンサーの配置は一位に定まる
 * センサーの縦方向はワールド座標の上向き（y軸正）の単位ベクトルを回転面に射影して取得する
 * センサーの横方向は視線方向と上方向の外積経由で取得する
 * センサーの大きさを極端に小さくするとRayの射出角度が狭くなるので、非常に狭い範囲のみしか撮影できなくなる
 * センサーから投影点までの距離が遠いと画角が狭くなり近いと画角が広くなる
 * 画像のピクセル数はセンサーの分割数に相当する
 * ピクセルの分割数が多いほど投影面の分割数が増える
 * 投影面のピンホールからの距離を伸ばせば投影面のサイズも拡大する一方、単位ピクセルあたり長さも増大する
 * そのため投影面のピンホールからの距離をどのように設定しても最終的な出力は変わらない
 * 画像の精度を上げるには単位面積あたりのピクセル密度を上げる必要がある
 */

class Camera {
public:
    Vec3 cam_pos; // center of sensor
    Vec3 cam_sight_vec;
    Vec3 cam_right_vec;
    Vec3 cam_up_vec;
    float sensor_height{};
    float sensor_width{};
    float sensor_dist{};
    float aspect_ratio{};

    Camera(const Vec3 &_cam_pos, const Vec3 &_cam_sight_vec) : cam_pos(_cam_pos){
        /*
         * 右手系:
         * x: 右手の親指
         * y: 右手の人差し指
         * z: 右手の中指
         *
         * 外積の向き:
         * 右ねじの法則と同じ
         * 外積の順序を逆にすると向きも逆となる
         *
         * カメラの視線方向:
         * 一般に-z方向(0, 0, -1)をカメラの視線方向とする
         * なぜ-z方向を視線とするのか
         * センサーに映る像は原理上上下左右が反転する
         * 右手系でx軸とy軸を反転するとz軸が(0, 0, -1)方向となり扱いが良いというのが回答
         * こういうのは自分で手を動かすと自明だが最初は混乱する
         *
         * cam_sight_vec:カメラの視線方向
         * cam_right_vec:カメラの視線方向をz正方向としたときの右手系でのx正方向
         * cam_up_vec:カメラの視線方向をz正方向としたときの右手系でのy正方向
         */
        cam_sight_vec = _cam_sight_vec.normalize();
        cam_right_vec = cross(Vec3(0, 1, 0), cam_sight_vec).normalize();
        cam_up_vec = cross(cam_sight_vec, cam_right_vec).normalize();
    };

    /*
     * (u, v)はセンサー上のワールド座標をcam_right_vecおよびcam_up_vecを用いた表現したときの係数
     * 例:
     * ワールド座標系で(1, -1, 0)の点（センサー右下）
     * cam_right_vecが(-1, 0, 0), cam_up_vecが(0, 1, 0)の場合(u, v) = (-1, -1)となる
     * virtualは仮想関数
     * 仮想関数にしないと継承した子クラスの処理は親クラスの処理を上書きできない
     * const = 0; は仮想関数を記載する際のお約束
     */
    virtual Ray shoot(float u, float v) const = 0;
};

#endif //PRACTICEPATHTRACING_CAMERA_H
