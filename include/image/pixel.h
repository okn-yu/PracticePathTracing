//
// Created by okn-yu on 2022/05/08.
//

#ifndef PRACTICEPATHTRACING_PIXEL_H
#define PRACTICEPATHTRACING_PIXEL_H

#include "../vec3.h"
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
    int r;
    int g;
    int b;
    float a;

    static void pix_val_check(int n) {
        if (n < 0) {
            throw std::runtime_error("val is less than 0.");
        }
        if (UCHAR_MAX < n) {
            throw std::runtime_error("val is grater than UCHAR_MAX");
        }
    }

public:
    
    Pixel(int _r, int _g, int _b) {
        r = _r;
        g = _g;
        b = _b;
        //TODO:
        //暗黙の型変換を検出したらエラーを発生させる
        //しかし組み込み型の暗黙の型変換を防ぐのは難しい
        //浮動小数点型の3.14が代入された場合はどう処理させるべきなのか?
        pix_val_check(r);
        pix_val_check(g);
        pix_val_check(b);
    }

    Pixel(int _r, int _g, int _b, float _a) {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
        //TODO:
        //暗黙の型変換を検出したらエラーを発生させる
        //しかし組み込み型の暗黙の型変換を防ぐのは難しい
        //浮動小数点型の3.14が代入された場合はどう処理させるべきなのか?
        pix_val_check(r);
        pix_val_check(g);
        pix_val_check(b);

    }
};

#endif //PRACTICEPATHTRACING_PIXEL_H