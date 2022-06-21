/*
 * Created by okn-yu on 2022/06/13.
 * wは微小立体角
 */

#ifndef PRACTICEPATHTRACING_MATERIAL_H
#define PRACTICEPATHTRACING_MATERIAL_H

#include "color.hpp"
#include "vec3.hpp"

class Material {
public:
    /*
     * wi: 注目するある1点に外部から入射する光の方向
     * wo: 注目するある1点で反射した光の方向
     * pdf: 確率密度関数（probability density function）
     *
     * 非常に紛らわしいのだが、sampleの引数のwiおよびpdfは&がついている通り、関数を適用後に呼び出し元で値が変更される
     * 関数呼び出し時はwoのみしか値が定まっていないこともありうる（他は宣言のみで初期化未実施）！
     *
     * TODO: sampleの返り値のクラスをColorに変更すること
     *
     */
    virtual Vec3 sample(const Vec3 &wo, Vec3 &wi, float &pdf) const = 0;
};

/*
 *  nは法線ベクトル
 *  vは面に入射したベクトル
 */

Vec3 reflect(Vec3 v, Vec3 n) {
    return -v + 2 * dot(v, n) * n;
}

/*
 *  TODO:以下を確認すること
 *  ローカル座標系では法線n=(0, 1, 0)と過程する
 */
float cos_theta(const Vec3 &v){
    return v.y();
}

#endif //PRACTICEPATHTRACING_MATERIAL_H
