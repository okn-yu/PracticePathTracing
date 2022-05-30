/*
 * Created by okn-yu on 2022/05/02.
 *
 * Vec3クラス
 * RGBなどの数値が3つセットで1つのオブジェクトもVec3クラスで扱うことはできる
 * その場合各色の和や差をどう意味づけするかが直感的に不明となる
 * 色の構造体を別途定義したほうが良いかもしれない
 */

#ifndef PRACTICEPATHTRACING_VEC3_H
#define PRACTICEPATHTRACING_VEC3_H

#include <iostream>
#include <cmath>

class Vec3 {
public:
    std::array<float, 3> elements{};


    // 引数なしのコンストラクタ
    // 呼び出し時は以下のように宣言する
    // Vec3 v0;
    // 以下のように()付きで呼び出すとエラーとなる
    // Vec3 v0();
    Vec3() { elements[0] = elements[1] = elements[2] = 0.0f; };

    // コンストラクタにexpicitを付与すると暗黙的な型変換とコピーコンストラクタを防ぐことができる
    // コピーコンストラクタ: インスタンスの代入時に実行されるコンストラクタ
    // コピーコンストラクタは引数に(const クラス名& 引数名)を取る
    // TODO: explicitを付与することで初期化子リストを用いたコンストラクタのみが実現されることを試験する
    explicit Vec3(float _x) { elements[0] = elements[1] = elements[2] = _x; };

    // 初期化子リストを用いたコンストラクタ
    Vec3(float _x, float _y, float _z) {
        elements[0] = _x;
        elements[1] = _y;
        elements[2] = _z;
    };

    float x(){
        return elements[0];
    }

    float y(){
        return elements[1];
    }

    float z(){
        return elements[2];
    }

    // const修飾子をつけるとメンバ変数が変更されないことが保証される
    // コードが明確になるため利用を推奨
    float length() const {
        return std::sqrt(elements[0] * elements[0] + elements[1] * elements[1] + elements[2] * elements[2]);
    };

    float squared_length() const {
        return elements[0] * elements[0] + elements[1] * elements[1] + elements[2] * elements[2];
    };

    Vec3 normalize() const {
        return {elements[0] / length(), elements[1] / length(), elements[2] / length()};
    }

    // operatorは演算子のオーバーロードに用いる
    Vec3 operator-() const {
        return {-elements[0], -elements[1], -elements[2]};
    }

    // &をつけることで引数の参照渡しを実現している
    // 値渡しと異なりコピーを作成しないため処理が効率的
    // 返り値は*をつけている
    // クラス内で定義しているからx, y, z, thisが利用できている
    // ここで利用されているthisはthisポインタでオブジェクト自身のアドレスを表している（Pythonのself）
    // クラス内では単項演算子の代入演算子が定義されている
    // https://qiita.com/eierapfel/items/60939808c9fafb3f31df
    // 代入演算子は自身を返すので*thisを返す
    // https://monozukuri-c.com/langcpp-this-pointer/
    // 例えばthisポインタを用いれば、メンバ変数とローカル変数の名前の衝突を避けることができる
    Vec3 &operator+=(const Vec3 &v) {
        elements[0] += v.elements[0];
        elements[1] += v.elements[1];
        elements[2] += v.elements[2];
        return *this;
    }

    Vec3 &operator-=(const Vec3 &v) {
        elements[0] -= v.elements[0];
        elements[1] -= v.elements[1];
        elements[2] -= v.elements[2];
        return *this;
    }
};

/*
 * operator: vector and vector
 * inline展開: 高速化のため関数の内容を直接呼び出し元に展開すること
 * inline展開を用いない場合は、関数呼び出しには関数の定義元のアドレスまで参照するため時間がかかる
 * 明示的にinline修飾子をつけることでコンパイラにinline展開を強制させる
 * https://qiita.com/omuRice/items/9e31d9ba17b32703b3b1
 */

inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2) {
    return {v1.elements[0] + v2.elements[0], v1.elements[1] + v2.elements[1], v1.elements[2] + v2.elements[2]};
}

inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
    return {v1.elements[0] - v2.elements[0], v1.elements[1] - v2.elements[1], v1.elements[2] - v2.elements[2]};
}

inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2) {
    return {v1.elements[0] * v2.elements[0], v1.elements[1] * v2.elements[1], v1.elements[2] * v2.elements[2]};
}

inline bool operator==(const Vec3 &v1, const Vec3 &v2) {
    return v1.elements[0] == v2.elements[0] && v1.elements[1] == v2.elements[1] && v1.elements[2] == v2.elements[2];
}

inline float dot(const Vec3 &v1, const Vec3 &v2) {
    return v1.elements[0] * v2.elements[0] + v1.elements[1] * v2.elements[1] + v1.elements[2] * v2.elements[2];
}

inline Vec3 cross(const Vec3 &v1, const Vec3 &v2) {
    return {v1.elements[1] * v2.elements[2] - v1.elements[2] * v2.elements[1], v1.elements[2] * v2.elements[0] - v1.elements[0] * v2.elements[2],
            v1.elements[0] * v2.elements[1] - v1.elements[1] * v2.elements[0]};
}

/*
 * operator: vector and scalar
 */

inline Vec3 operator+(const Vec3 &v, const float k) {
    return {v.elements[0] + k, v.elements[1] + k, v.elements[2] + k};
}

inline Vec3 operator+(const float k, const Vec3 &v) {
    return v + k;
}

inline Vec3 operator-(const Vec3 &v, const float k) {
    return {v.elements[0] - k, v.elements[1] - k, v.elements[2] - k};
}

inline Vec3 operator-(const float k, const Vec3 &v) {
    return -(v - k);
}


inline Vec3 operator*(const Vec3 &v, const float k) {
    return {v.elements[0] * k, v.elements[1] * k, v.elements[2] * k};
}

inline Vec3 operator*(const float k, const Vec3 &v) {
    return v * k;
}

inline Vec3 operator/(const Vec3 &v, const float k) {
    return {v.elements[0] / k, v.elements[1] / k, v.elements[2] / k};
}

inline Vec3 operator/(const float k, const Vec3 &v) {
    return v / k;
}

/*
 *　コンソール出力
 * C++では入出力に関数は用いず入出力演算子を用いる
 * 出力演算子: <<
 * Usage: "出力先 << 出力内容"
 * example: std::cout << v1 << std::endl;
 * endlはマニピュレータで改行文字を出力してバッファをフラッシュする
 * http://kaitei.net/cpp/iostream/
 */

inline std::ostream &operator<<(std::ostream &stream, const Vec3 &v) {
    stream << "(" << v.elements[0] << ", " << v.elements[1] << ", " << v.elements[2] << ")";
    return stream;
}

inline Vec3 unit_vec(Vec3 v) {
    return v / v.length();
}

/*
void orthonormalBasis(const Vec3 &v1, Vec3 &v2, Vec3 &v3) {
    //Vec3は(0, 1, 0)か(1, 0, 0)のいずれか
    if (std::abs(v1.x) > 0.9f)
        v2 = Vec3(0.0f, 1.0f, 0.0f);
    else
        v2 = Vec3(1.0f, 0.0f, 0.0f);

    v2 = (v2 - dot(v1, v2) * v1).normalize();
    v3 = cross(v1, v2);
}
*/

/*
Vec3 worldToLocal(const Vec3 &v, const Vec3 &s, const Vec3 &n, const Vec3 &t) {
    return {dot(v, s), dot(v, n), dot(v, t)};
}

Vec3 localToWorld(const Vec3 &v, const Vec3 &s, const Vec3 &n, const Vec3 &t) {
    Vec3 a = Vec3(s.x, n.x, t.x);
    Vec3 b = Vec3(s.y, n.y, t.y);
    Vec3 c = Vec3(s.z, n.z, t.z);

    return {dot(v, a), dot(v, b), dot(v, c)};
}
*/

#endif //PRACTICEPATHTRACING_VEC3_H