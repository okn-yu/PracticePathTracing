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
    float x;
    float y;
    float z;

    // 引数なしのコンストラクタ
    // 呼び出し時は以下のように宣言する
    // Vec3 v0;
    // 以下のように()付きで呼び出すとエラーとなる
    // Vec3 v0();
    Vec3() { x = y = z = 0.0f; };

    // コンストラクタにexpicitを付与すると暗黙的な型変換とコピーコンストラクタを防ぐことができる
    // コピーコンストラクタ: インスタンスの代入時に実行されるコンストラクタ
    // コピーコンストラクタは引数に(const クラス名& 引数名)を取る
    // TODO: explicitを付与することで初期化子リストを用いたコンストラクタのみが実現されることを試験する
    explicit Vec3(float _x) { x = y = z = _x; };

    //初期化子リストを用いたコンストラクタ
    Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};

    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    };

    float squared_length() const {
        return x * x + y * y + z * z;
    };

    Vec3 normalize() const {
        return {x / length(), y / length(), z / length()};
    }

    // operatorは演算子のオーバーロードに用いる
    Vec3 operator-() const {
        return {-x, -y, -z};
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
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vec3 &operator-=(const Vec3 &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }
};

/*
operator: vector and vector
*/

Vec3 operator+(const Vec3 &v1, const Vec3 &v2) {
    return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
    return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

Vec3 operator*(const Vec3 &v1, const Vec3 &v2) {
    return {v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
}

bool operator==(const Vec3 &v1, const Vec3 &v2) {
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

float dot(const Vec3 &v1, const Vec3 &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vec3 cross(const Vec3 &v1, const Vec3 &v2) {
    return {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x};
}

/*
operator: vector and scalar
*/

Vec3 operator*(const Vec3 &v, const float k) {
    return {v.x * k, v.y * k, v.z * k};
}

Vec3 operator*(const float k, const Vec3 &v) {
    return v * k;
}

Vec3 operator/(const Vec3 &v, const float k) {
    return {v.x / k, v.y / k, v.z / k};
}

Vec3 operator/(const float k, const Vec3 &v) {
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

std::ostream &operator<<(std::ostream &stream, const Vec3 &v) {
    stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return stream;
}

void orthonormalBasis(const Vec3 &v1, Vec3 &v2, Vec3 &v3) {
    //Vec3は(0, 1, 0)か(1, 0, 0)のいずれか
    if (std::abs(v1.x) > 0.9f)
        v2 = Vec3(0.0f, 1.0f, 0.0f);
    else
        v2 = Vec3(1.0f, 0.0f, 0.0f);

    v2 = (v2 - dot(v1, v2) * v1).normalize();
    v3 = cross(v1, v2);
}

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