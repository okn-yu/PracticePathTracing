/*
 * Created by okn-yu on 2022/05/05.
 *
 * C++の文法補足:
 * 仮想関数
 */

#include <cassert>
#include "futaba/core/vec3.h"
#include "futaba/core/ray.h"
#include "futaba/render/camera.h"

/*
 * デジタルカメラの原理:
 * 外部からの光をイメージセンサで電気信号に変換している
 *
 * イメージセンサ:
 * 1.カラーフィルタでRGBの3成分に分解
 * 2.RGBの成分毎に受光素子で電気信号に変換後
 * 3.アンプで増大してRGB値の輝度値を算出
 * 代表的なイメージセンサはCMOSやCCDなどがある
 *
 * 受光素子(フォトダイオード/光検出器):
 * 光を照射したときにその光の強さを電流に変換する受光素子
 *
 * 参考URL:
 * https://www.spdigital.net/digi-came/digi-came-03
 */

/*
 * 座標の命名規則:
 * (x, y, z)はワールド座標系の正規直交基底
 * (u, v, w)はカメラ座標系（より正確にはセンサ座標系）の正規直交基底　
 *
 * 右手系:
 * x: 右手の親指
 * y: 右手の人差し指
 * z: 右手の中指
 */

/*
 * Cameraクラス
 * 今後実装する様々な種類のCameraの基底クラス
 * Cameraクラスのメンバには原則命名時に接頭辞としてcam_をつける
 *
 * cam_sensor_pos:イメージセンサの中心のワールド座標系での座標
 * cam_sight_vec:カメラの視線方向
 * cam_right_vec:カメラの視線方向をz正方向としたときの右手系でのx正方向
 * cam_up_vec:カメラの視線方向をz正方向としたときの右手系でのy正方向
 *
 * cam_sensor_posとcam_sight_vecとcam_sensor_distが定まればセンサの平面は回転の自由度を除いて定まる
 * センサの上方向はワールド座標の上向き（y軸正）の単位ベクトルと視線方向の外積で取得する
 * センサの横方向は視線方向と上方向の外積で取得する
 * ただしこの手法では視線方向とワールド座標の上向きが並行だと失敗する
 *
 * cam_sensor_height:イメージセンサの高さ
 * cam_sensor_width:イメージセンサの幅
 * cam_sensor_dist:イメージセンサとレンズ間の距離
 *
 * レンダリングにより生成される画像のアスペクト比は、イメージセンサのアスペクト比と等しい
 * レンダリングにより生成される画像のピクセル数はレイのサンプリング間隔に依存する
 * そのため画像の画質（ピクセルの密度）を上げるにはレイのサンプリング間隔を密にすればよいが、計算時間がかかる
 * センサの大きさを極端に小さくするとRayの射出角度が狭くなるので狭い範囲のみしか撮影できなくなる
 * センサからレンズまでの距離が遠いと画角が狭くなり近いと画角が広くなる
 */

Camera::Camera(const Point3 &_cam_sensor_pos, const Vec3 &_cam_sight_vec, float _cam_sensor_width,
               float _cam_sensor_height,
               float _cam_sensor_dist) {

    cam_sensor_pos = _cam_sensor_pos;

    /* 一番素直な実装はcam_sight_vecの回転と連動してcam_side_vecとcam_up_vecも変換されるのが最も望ましい
     * 初期状態では各ベクトルは以下のように与えられる
     * cam_sight_vec: (0, 0, 1)
     * cam_right_vec: (1, 0, 0)
     * cam_up_vec: (0, 1, 0)
     *
     * 任意の正規化されたcam_sight_vecは(0, 0, 1)のx軸回転とy軸回転の組み合わせで表すことができる
     * 同等の回転をcam_right_vecおよびcam_up_vecに作用させればよい
     */
    cam_sight_vec = unit_vec(_cam_sight_vec);
    float _theta_x = _rot_x_angle();
    float _theta_y = _rot_y_angle();
    cam_side_vec = rotation_y(rotation_x(Vec3(1, 0, 0), _theta_x), _theta_y);
    cam_up_vec = rotation_y(rotation_x(Vec3(0, 1, 0), _theta_x), _theta_y);

    /*
     * デバッグを考えるとセンサーのアスペクト比が1:1は望ましくない
     * 横16:縦9の一般的なモニターの比率が望ましい
     */
    cam_sensor_width = _cam_sensor_width;
    cam_sensor_height = _cam_sensor_height;
    cam_sensor_dist = _cam_sensor_dist;

};

float Camera::_rot_x_angle() const {
    return asin(-cam_sight_vec.y());
}

float Camera::_rot_y_angle() const {
    return acos(cam_sight_vec.z() / sqrt(1 - pow(cam_sight_vec.y(), 2)));
}