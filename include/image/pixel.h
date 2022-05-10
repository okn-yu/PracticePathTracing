//
// Created by okn-yu on 2022/05/08.
//

#ifndef PRACTICEPATHTRACING_PIXEL_H
#define PRACTICEPATHTRACING_PIXEL_H

#include <cassert>
#include <limits.h>

struct Pixel {
private:
    //TODO:
    //0から255までの整数を取る
    //uint8_tで宣言しコンストラクタで型変換されているかチェックをしたい
    //ただしuint8_tだとUCHAR_MAX255以上のチェックができない!
    //256は0と解釈されてしまう
    //そのため一時的にint型で宣言し0から255の値に収まっているかを確認する
    //以下で回避できないかを確認すること
    //https://ez-net.jp/article/7D/XrRDo8VO/_4QfAkRTO-Or/
    //TODO:
    //暗黙の型変換を検出したらエラーを発生させる
    //しかし組み込み型の暗黙の型変換を防ぐのは難しい
    //浮動小数点型の3.14が代入された場合はどう処理させるべきなのか?
    //C++はタイプセーフではない模様
    //dynamic_cast等で解決ができないかは要件等
    //https://docs.microsoft.com/ja-jp/cpp/cpp/user-defined-type-conversions-cpp?view=msvc-170
    //Piexlのコンストラクタの引数をユーザ定義の独自の型に変換し、explicit指定子を利用すれば解決できる可能性がある
    //しかしわざわざPiexlのインスタンス作成時に明示的に独自の型に変換しなおすのは面倒である
    int r;
    int g;
    int b;

    static void pix_val_check(int n) {
        if (n < 0) {
            throw std::runtime_error("val is less than 0.");
        }
        if (UCHAR_MAX < n) {
            throw std::runtime_error("val is grater than UCHAR_MAX");
        }
    }

public:
    Pixel(int _r, int _g, int _b) : r(_r), g(_g), b(_b) {
        pix_val_check(r);
        pix_val_check(g);
        pix_val_check(b);
    }
};

#endif //PRACTICEPATHTRACING_PIXEL_H