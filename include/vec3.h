//
// Created by okn-yu on 2022/05/02.
//

#ifndef PRACTICEPATHTRACING_VEC3_H
#define PRACTICEPATHTRACING_VEC3_H

#include <iostream>
#include <cmath>

class Vec3 {
public:
    double x;
    double y;
    double z;

    //引数なしのコンストラクタ
    //呼び出し時は以下のように宣言する
    // Vec3 v0;
    //()付きで呼び出すとエラーとなる
    // Vec3 v0();
    Vec3() { x = y = z = 0; };

    Vec3(double _x) { x = y = z = _x; };

    //初期化子リストを用いたコンストラクタ
    Vec3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {};

    double length() const {
        return std::sqrt(x * x + y * y + z * z);
    };

    double length2() const {
        return x * x + y * y + z * z;
    };

    // operatorは演算子のオーバーロードに用いる
    // -は演算子に引数は不要
    Vec3 operator-() const {
        return Vec3(-x, -y, -z);
    }

    // &をつけることで引数の参照渡しを実現している
    // 値渡しと異なりコピーを作成しないため処理が効率的
    // 返り値は*をつけている
    // クラス内で定義しているからx, y, z, thisが利用できている
    // クラス内では単項演算子の代入演算子が定義されている
    // https://qiita.com/eierapfel/items/60939808c9fafb3f31df
    // 代入演算子は*thisを返すのがお作法らしい
    Vec3 &operator+=(const Vec3 &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vec3 &operator*=(const Vec3 &v) {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    Vec3 &operator/=(const Vec3 &v) {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }
};

// operator: vector and vector
// ここからはクラス外で演算子のオーバーロードしている
Vec3 operator+(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vec3 operator*(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

Vec3 operator/(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

//operator: vector and scalar
Vec3 operator+(const Vec3 &v, const double k) {
    return Vec3(v.x + k, v.y + k, v.z + k);
}

Vec3 operator+(const double k, const Vec3 &v) {
    return v + k;
}

Vec3 operator-(const Vec3 &v, const double k) {
    return Vec3(v.x - k, v.y - k, v.z - k);
}

Vec3 operator-(const double k, const Vec3 &v) {
    return v - k;
}

Vec3 operator*(const Vec3 &v, const double k) {
    return Vec3(v.x * k, v.y * k, v.z * k);
}

Vec3 operator*(const double k, const Vec3 &v) {
    return v * k;
}

Vec3 operator/(const Vec3 &v, const double k) {
    return Vec3(v.x / k, v.y / k, v.z / k);
}

Vec3 operator/(const double k, const Vec3 &v) {
    return Vec3(k / v.x, k / v.y, k / v.z);
}

double dot(const Vec3 &v1, const Vec3 &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vec3 cross(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

Vec3 normalize(const Vec3 &v) {
    return v / v.length();
}

//コンソール出力
//C++では入出力に関数は用いず入出力演算子を用いる
//出力演算子: <<
//Usage: "出力先 << 出力内容"
//example: std::cout << v1 << std::endl;
//endlはマニピュレータで改行文字を出力してバッファをフラッシュする
//http://kaitei.net/cpp/iostream/
std::ostream &operator<<(std::ostream &stream, const Vec3 &v) {
    stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return stream;
}

void orthonormalBasis(const Vec3 &v1, Vec3 &v2, Vec3 &v3) {
    if (std::abs(v1.x) > 0.9) v2 = Vec3(0, 1, 0);
    else v2 = Vec3(1, 0, 0);

    v2 = normalize(v2 - dot(v1, v2) * v1);
    v3 = cross(v1, v2);
}

Vec3 worldToLocal(const Vec3 &v, const Vec3 &s, const Vec3 &n, const Vec3 &t) {
    return Vec3(dot(v, s), dot(v, n), dot(v, t));
}

Vec3 localToWorld(const Vec3 &v, const Vec3 &s, const Vec3 &n, const Vec3 &t) {
    Vec3 a = Vec3(s.x, n.x, t.x);
    Vec3 b = Vec3(s.y, n.y, t.y);
    Vec3 c = Vec3(s.z, n.z, t.z);

    return Vec3(dot(v, a), dot(v, b), dot(v, c));

}

#endif //PRACTICEPATHTRACING_VEC3_H
