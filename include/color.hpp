/*
 * Created by okn-yu on 2022/06/01.
 * Colorは慣習として0から1の間の連続値を取る
 *
 * ガンマ補正は"画像のデータとしての正しさ"と"モニターの物理的な出力"が相互に関連するため紛らわしい
 *
 * ガンマ値:
 * 画像の階調の応答特性
 * ディスプレイなどの出力機器では入力値（画像の輝度）と出力値（ディスプレイ上の表示）は線形ではなくV_out = V_in^γの非線形な関係となる
 * このべき乗の値γをガンマ値と呼ぶ
 * CRTディスプレイ（ブラウン管）ではガンマ値は2.2前後（つまり下に凸な関係）
 * 液晶ディスプレイでもCRTディスプレイと同程度になるように調整がされている
 * この場合出力機器上では実際よりも全体として黒ずんで見える
 *
 * 歴史的経緯
 * テレビ放送の際にCRTディスプレイの上の特性を考慮して放送局側で予めガンマ補整をかけた信号を送信していた（上に凸な補正をかけていた）
 * 一方受信側のCRTディスプレイでは、表示する際に下に凸に補正がかけられ双方が打ち消し合って適切な画像の表示が実現されていた
 * 一方偶然ではあるが人の目は低輝度の変化に敏感で高輝度には鈍感なため都合が良かった(ロウソクの数が倍々に増えていっても人の眼には大体等間隔で明るく見える)
 *
 * ガンマ補正
 * 画像の色の明暗が出力機器で正しく表示されるように対象機器のガンマ値に応じた色の補正を行うこと
 * ディスプレイなどの出力機器で画像をそのまま表示すると画面が暗くなってしまうため、RGBの値を予め大きくすることで出力機器の特性を排除した画像表示を行う
 * 具体的にはガンマ値とは逆にV_out = V_in^(-γ)の変換を行う
 *
 * ガンマ値の具体的な値はOSにより異なる
 * Windows系のOS:
 * ガンマ値は2.2のディスプレイを前提にしている
 * Mac系のOS:
 * ガンマ値は1.8のディスプレイを前提にしている
 *
 * またディスプレイによりガンマ値は異なるため、ガンマ値2.2のディスプレイで最適な画像をガンマ値1.8のディスプレイで表示する場合を考える
 * 実際のガンマ値はγ=1.8/2.2≒0.82となるため意図した画像よりも明るくなる
 *
 * ガンマ補正は（ディスプレイとは別に）画像解析の手法の1つとしても利用ができる
 * ガンマ値が小さいと輝度の大きな値が強調されるようになる
 * ガンマ値が大きいと輝度の小さな値が強調されるようになる
 * http://rs.aoyaman.com/seminar/about10.html
 *
 * ガンマ補正の問題点
 * 色深度が8ビット（つまり256階調）ではガンマ補正により低輝度が潰れる
 * 輝度が6以下（実装によっては20以下）が0になる
 * また計算にpowを用いるので計算コストが高い
 * 12ビット以上の色深度が望ましい
 * https://qiita.com/yoya/items/122b93970c190068c752
 *
 * 色深度
 * 1ピクセル内の1チャンネルの値を何ビットで表すか
 * OpenCVのサポートしている色深度は以下の通り
 * 画像処理をがっつりするなら色深度の大きなディスプレイが望ましい
 * CV_8U
 * CV_8S
 * CV_16U
 * CV_16S
 * CV_32S
 * CV_32F
 * CV_64F
 *
 * TODO:階調とピクセル
 * pixel.hppに階調に関して整理してまとめること
 * https://camerapocket.com/gashitsu/
 *
 * 余談
 * 画像処理100本ノックは周りに紹介したほうが良い
 */

#ifndef PRACTICEPATHTRACING_COLOR_H
#define PRACTICEPATHTRACING_COLOR_H

#include <array>
#include <cassert>
#include <cmath>
#include "pixel.hpp"
#include "vec3.hpp"

struct Color {
    /*
     * data[0]: r
     * data[1]: g
     * data[2]: b
     */
    std::array<float, 3> data{};

    Color() {
        data[0] = 0.0f;
        data[1] = 0.0f;
        data[2] = 0.0f;
    }

    template<typename T, typename U, typename F>
    Color(T r, U g, F b) {
        throw std::runtime_error("not float argument");
    }

    Color(float r, float g, float b) {

        if (r < 0 || 1 < r) {
            throw std::runtime_error("invalid range");
        }

        if (g < 0 || 1 < g) {
            throw std::runtime_error("invalid range");
        }

        if (b < 0 || 1 < b) {
            throw std::runtime_error("invalid range");
        }

        // ガンマ補正の実行
        data[0] = std::pow(r, 1/ConstParam::GAMMA_VALUE);//r;
        data[1] = std::pow(g, 1/ConstParam::GAMMA_VALUE);//g;
        data[2] = std::pow(b, 1/ConstParam::GAMMA_VALUE);//b;

    }

    explicit Color(Vec3 v) : Color(v.x(), v.y(), v.z()) {}

    float r() {
        return data[0];
    }

    float g() {
        return data[1];
    }

    float b() {
        return data[2];
    }

    RGBPixel pixalize() {
        assert(0 <= data[0] && data[0] <= 1);
        assert(0 <= data[1] && data[1] <= 1);
        assert(0 <= data[2] && data[2] <= 1);

        auto R = static_cast<int>(data[0] * 255);
        auto G = static_cast<int>(data[1] * 255);
        auto B = static_cast<int>(data[2] * 255);

        RGBPixel pixel = RGBPixel(R, G, B);

        return pixel;
    }
};

bool operator==(const Color &src, const Color &dst) {
    return src.data == dst.data;
}

Color normal_vec_2_color(Vec3 v) {
    assert(std::abs(v.length() - 1) <= 0.1);
    if ((std::abs(v.x()) <= 1) && (std::abs(v.y()) <= 1) && (std::abs(v.z()) <= 1)) {
        Vec3 color_vec = (v + 1) / 2;
        return Color(color_vec);
    } else {
        throw std::runtime_error("invalid vector length.");
    }
}

#endif //PRACTICEPATHTRACING_COLOR_H
