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
 *  TODO:以下を確認すること
 *  ローカル座標系では法線n=(0, 1, 0)と過程する
 */
float cos_theta(const Vec3 &v){
    return v.y();
}

/*
 * cos_thetaでは物体の内部から外部に光が出る場合にcosineの値が負となりレンダリング結果が合わない場合がある
 * そのためcosineの値が負とならないように絶対値をつけることで対応する
 */

float abs_cos_theta(const Vec3 &v){
    return std::abs(v.y());
}

/*
 *  鏡にオブジェクトにレイが入社したばあ
 */

Vec3 reflect(Vec3 v_in, Vec3 n) {
    return -v_in + 2 * dot(v_in, n) * n;
}

/*
 * 屈折率のあるオブジェクトにレイが入射した場合を扱う
 */

bool reflect(const Vec3 &v_in, Vec3 &v_ref, const Vec3 &n, float n_in, float n_out) {

    float cos = abs_cos_theta(v_in);
    float sin = std::sqrt(std::max(1 - cos * cos, 0.0f));
    float alpha = (n_in / n_out) * sin;

    // total reflection
    if (alpha * alpha > 1.0f) return false;

    v_ref = (n_in / n_out) * (-v_in + dot(v_in, n) * n) - std::sqrt((1 - alpha * alpha)) * n;
    return true;

}


/*
 *
 */

float fresnel(const Vec3& v_in, const Vec3& n, float n_in, float n_out){
    float f0 = std::pow((n_in - n_out)/(n_in + n_out), 2.0f);
    float cos = abs_cos_theta(v_in);

    return f0 + (1.0f - f0)*std::pow(1.0f - cos, 5.0f);
}
#endif //PRACTICEPATHTRACING_MATERIAL_H
