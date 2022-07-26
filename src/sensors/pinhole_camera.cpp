/*
 * Created by okn-yu on 2022/05/05.
 * ピンホールカメラはレンズの代わりにピンホールを利用するカメラ
 *
 * 以下のPinholeCameraクラスは理想化されたピンホールカメラで、面積無限小のピンホールを利用する
 * レンズが存在しないため全ての距離に対してピントがあう
 * またレンズが存在しないため焦点距離という概念がない
 *
 * 現実のカメラではレンズの大きさは有限であるため像にぼけが生じる
 * 現実のピンホールカメラではレンズを利用しないため露光時間が非常に長くなる
 */

#include <cassert>
#include "futaba/core/ray.h"
#include "futaba/render/camera.h"

PinholeCamera::PinholeCamera(const Point3 &_cam_sensor_pos, const Vec3 &_cam_sight_vec, float _cam_sensor_width,
              float _cam_sensor_height, float _cam_sensor_dist) :
        Camera(_cam_sensor_pos, _cam_sight_vec, _cam_sensor_width, _cam_sensor_height, _cam_sensor_dist) {};

// overrideは.cppファイル内ではクラス外では記載できない
// 代わりにヘッダファイルのメンバ関数内に記載する必要がある
Ray PinholeCamera::shoot(float u, float v) const{
    assert(-1 <= u && u <= 1);
    assert(-1 <= v && v <= 1);

    Point3 pinhole_pos = cam_sensor_pos + cam_sensor_dist * cam_sight_vec;
    Point3 uv_pos = cam_sensor_pos + u * cam_side_vec * (cam_sensor_width / 2) + v * cam_up_vec * (cam_sensor_height / 2);
    Ray ray = Ray(uv_pos, unit_vec(pinhole_pos - uv_pos));

    return ray;
};