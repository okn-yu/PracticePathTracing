/*
 * Created by okn-yu on 2022/06/17.
 *
 * base_color:
 * 光の各波長（単純化のためRGBのみを扱う）に対してどの程度反射するかを表す
 * base_colorが(0, 0, 0)ならば常に黒となる
 * base_colorが(1, 1, 1)でも光がR成分のみだと赤くなる
 * 拡散反射の場合物体のbase_colorの効果はbrdfに現れる
 *
 * 拡散反射のbrdfは以下のベクトルで与えられる
 * base_color/pi
 *
 * 拡散反射の定義
 * 非金属表面付近で起きる光の反射のうち、界面で発生する鏡面反射を除いた成分
 * 金属表面では自由電子が界面下への侵入を防ぐため拡散反射は存在しない
 * 拡散反射は乱反射と同義
 *
 * 物理現象としての拡散反射
 * 界面下で入射光が十分小さい範囲で多重反射、透過、散乱する様子
 *
 * 拡散反射の性質
 * 入射角によって反射光の強度が異なる
 * 入射角が浅い場合（反射面に並行に近い場合）は暗く、入射角が深い場合（反射面に垂直に近い場合）
 * 現実には入射した光が完全に反射することはほとんどなく、ある程度吸収/減衰が存在する
 * 現実には入射した光が入射点から反射することはほとんどない（表面化散乱）
 *
 * 拡散反射のモデル:
 * ランバード反射:
 * 拡散反射を理想的に扱ったモデル
 *
 * オーレン・ネイヤー反射:
 *
 * ランベルトの余弦則:
 * 理想的な拡散反射面や拡散放射体で観測される放射強度あるいは光度が、入射光と面の法線との間の角度θの余弦と正比例することを示す法則
 * BRDFのcosine項がランベルトの預言則に該当する
 * ランベルトの余弦則を完全に満たすランベルト面は、どの角度から見ても同じ輝度となる
 *
 * https://area.autodesk.jp/column/tutorial/3ds_max_kitchen_stadium/5_rgb_level/
 *
 */

#ifndef PRACTICEPATHTRACING_DIFFUSE_H
#define PRACTICEPATHTRACING_DIFFUSE_H

#include "core/color.hpp"
#include "materials/material.hpp"
#include "core/utils.hpp"
#include "core/vec3.hpp"

class Diffuse : public Material {
public:
    Vec3 base_color;

    Diffuse(const Vec3 &_base_color) : base_color(_base_color) {};

    Vec3 sample(const Vec3 &wo, Vec3 &wi, float &pdf) const override{
        float u = rnd();
        float v = rnd();

        float theta = 0.5 * std::acos(1 - 2 * u);
        float phi = 2 * M_PI * v;

        float x = std::cos(phi) * std::sin(theta);
        float y = std::cos(theta);
        float z = std::sin(phi) * std::sin(theta);

        wi = Vec3(x, y, z);
        pdf = std::cos(theta) / M_PI;

        //std::cout << "pdf: " << pdf << std::endl;
        //std::cout << "return: " << (base_color / M_PI) << std::endl;

        return (base_color / M_PI);

    };
};

#endif //PRACTICEPATHTRACING_DIFFUSE_H
