/*
 * Created by okn-yu on 2022/05/08.
 *
 * RGBPixel構造体
 * uint8_tは0未満や256以上の整数値に対しては不適切な値に変換されてしまう
 * この事象を防ぐために受け取る値はint型で受けて値が適切な範囲内かを確認している
 * float型の変数も3.14が3のようにキャストされるためint型以外はすべて実行時例外を送出している
 * RGBはarray<uint8_t>型のdataを用いて定義したほうがすっきりするかもしれない
 * その場合serializeは単にpublicなdataを返せば済むのでそもそも定義する必要すらない
 * 上記を満たすように実装を修正した(5/29)
 *
 *  解像度
 *  解像度は2つの解像度（A.画面解像度(1280x960)とB.画像解像度(dpi)）が混在して使われている
 *  A.画面解像度:画面に存在する画素の総数
 *   1280x960なら画面の横に1280画素/縦に720画素存在している
 *   ハイビジョン: 1,280×720
 *   フルハイビジョン:1,920×1,080
 *   4K:3,840×2,160
 *   8K:7,680×4,320
 *
 *  B.画像解像度:単位長さ(1inch)あたりに含まれる画素の総数
 *   画面解像度が与えられた場合、画像解像度がいくつであるかはディスプレイのサイズに依存する
 *
 *  ビット深度
 *   RGBの各色に割り当てられるビット数
 *   8bitの場合は256階調を表示ができる
 *   ビット深度に関しては以下を参照のこと
 *   https://aviutl.info/color-depth/
 *   https://shuffle.genkosha.com/products/eizo/serial/motegi/2537.html
 *   https://allabout.co.jp/gm/gc/63756/
 *   そういやもののけ姫の原画？では緑の種類がすごく多かったような...
 *   あれもある意味ディープカラーなのか？
 *
 */

#ifndef PRACTICEPATHTRACING_PIXEL_CPP
#define PRACTICEPATHTRACING_PIXEL_CPP

#include <iostream>
#include <stack>
#include <cmath>
#include <array>
#include "config.hpp"

std::map<uint8_t, uint8_t> LUT{
        {0,   0},
        {1,   11},
        {2,   17},
        {3,   21},
        {4,   25},
        {5,   28},
        {6,   31},
        {7,   34},
        {8,   37},
        {9,   39},
        {10,  42},
        {11,  44},
        {12,  46},
        {13,  48},
        {14,  50},
        {15,  52},
        {16,  54},
        {17,  56},
        {18,  58},
        {19,  60},
        {20,  61},
        {21,  63},
        {22,  65},
        {23,  67},
        {24,  68},
        {25,  70},
        {26,  71},
        {27,  73},
        {28,  74},
        {29,  76},
        {30,  77},
        {31,  79},
        {32,  80},
        {33,  81},
        {34,  83},
        {35,  84},
        {36,  85},
        {37,  87},
        {38,  88},
        {39,  89},
        {40,  91},
        {41,  92},
        {42,  93},
        {43,  94},
        {44,  96},
        {45,  97},
        {46,  98},
        {47,  99},
        {48,  100},
        {49,  101},
        {50,  103},
        {51,  104},
        {52,  105},
        {53,  106},
        {54,  107},
        {55,  108},
        {56,  109},
        {57,  110},
        {58,  112},
        {59,  113},
        {60,  114},
        {61,  115},
        {62,  116},
        {63,  117},
        {64,  118},
        {65,  119},
        {66,  120},
        {67,  121},
        {68,  122},
        {69,  123},
        {70,  124},
        {71,  125},
        {72,  126},
        {73,  127},
        {74,  128},
        {75,  129},
        {76,  130},
        {77,  131},
        {78,  132},
        {79,  132},
        {80,  133},
        {81,  134},
        {82,  135},
        {83,  136},
        {84,  137},
        {85,  138},
        {86,  139},
        {87,  140},
        {88,  141},
        {89,  142},
        {90,  142},
        {91,  143},
        {92,  144},
        {93,  145},
        {94,  146},
        {95,  147},
        {96,  148},
        {97,  149},
        {98,  149},
        {99,  150},
        {100, 151},
        {101, 152},
        {102, 153},
        {103, 154},
        {104, 154},
        {105, 155},
        {106, 156},
        {107, 157},
        {108, 158},
        {109, 159},
        {110, 159},
        {111, 160},
        {112, 161},
        {113, 162},
        {114, 163},
        {115, 163},
        {116, 164},
        {117, 165},
        {118, 166},
        {119, 166},
        {120, 167},
        {121, 168},
        {122, 169},
        {123, 170},
        {124, 170},
        {125, 171},
        {126, 172},
        {127, 173},
        {128, 173},
        {129, 174},
        {130, 175},
        {131, 176},
        {132, 176},
        {133, 177},
        {134, 178},
        {135, 179},
        {136, 179},
        {137, 180},
        {138, 181},
        {139, 182},
        {140, 182},
        {141, 183},
        {142, 184},
        {143, 184},
        {144, 185},
        {145, 186},
        {146, 187},
        {147, 187},
        {148, 188},
        {149, 189},
        {150, 189},
        {151, 190},
        {152, 191},
        {153, 191},
        {154, 192},
        {155, 193},
        {156, 194},
        {157, 194},
        {158, 195},
        {159, 196},
        {160, 196},
        {161, 197},
        {162, 198},
        {163, 198},
        {164, 199},
        {165, 200},
        {166, 200},
        {167, 201},
        {168, 202},
        {169, 202},
        {170, 203},
        {171, 204},
        {172, 204},
        {173, 205},
        {174, 206},
        {175, 206},
        {176, 207},
        {177, 208},
        {178, 208},
        {179, 209},
        {180, 210},
        {181, 210},
        {182, 211},
        {183, 212},
        {184, 212},
        {185, 213},
        {186, 214},
        {187, 214},
        {188, 215},
        {189, 215},
        {190, 216},
        {191, 217},
        {192, 217},
        {193, 218},
        {194, 219},
        {195, 219},
        {196, 220},
        {197, 220},
        {198, 221},
        {199, 222},
        {200, 222},
        {201, 223},
        {202, 224},
        {203, 224},
        {204, 225},
        {205, 225},
        {206, 226},
        {207, 227},
        {208, 227},
        {209, 228},
        {210, 228},
        {211, 229},
        {212, 230},
        {213, 230},
        {214, 231},
        {215, 231},
        {216, 232},
        {217, 233},
        {218, 233},
        {219, 234},
        {220, 234},
        {221, 235},
        {222, 236},
        {223, 236},
        {224, 237},
        {225, 237},
        {226, 238},
        {227, 239},
        {228, 239},
        {229, 240},
        {230, 240},
        {231, 241},
        {232, 241},
        {233, 242},
        {234, 243},
        {235, 243},
        {236, 244},
        {237, 244},
        {238, 245},
        {239, 245},
        {240, 246},
        {241, 247},
        {242, 247},
        {243, 248},
        {244, 248},
        {245, 249},
        {246, 249},
        {247, 250},
        {248, 251},
        {249, 251},
        {250, 252},
        {251, 252},
        {252, 253},
        {253, 253},
        {254, 254},
        {255, 255}
};


struct GrayPixel {
    std::array<uint8_t, 1> data{};

    GrayPixel() {
        data[0] = 0;
    }

    template<typename T>
    explicit GrayPixel(T n) {
        throw std::runtime_error("invalid range");
    }

    explicit GrayPixel(int n) {
        if (n < 0 || 255 < n) {
            throw std::runtime_error("invalid range");
        }
        data[0] = n;
    }

    uint8_t n() {
        return data[0];
    }

    // 代入操作の定義
    GrayPixel &operator=(const GrayPixel &src) = default;
};

bool operator==(const GrayPixel &src, const GrayPixel &dst) {
    return src.data == dst.data;
}

bool operator!=(const GrayPixel &src, const GrayPixel &dst) {
    return src.data != dst.data;
}

std::ostream &operator<<(std::ostream &stream, const GrayPixel &pixel) {
    stream << "(" << pixel.data[0] << ")";
    return stream;
}

struct RGBPixel {
    /*
     * data[0]: r
     * data[1]: g
     * data[2]: b
     */
    std::array<uint8_t, 3> data{};

    RGBPixel() {
        data[0] = 0;
        data[1] = 0;
        data[2] = 0;
    }

    template<typename T, typename U, typename F>
    RGBPixel(T r, U g, F b) {
        throw std::runtime_error("not integer argument");
    }

    RGBPixel(int r, int g, int b) {

        if (r < 0 || 255 < r) {
            throw std::runtime_error("r is invalid range: " +  std::to_string(r));
        }

        if (g < 0 || 255 < g) {
            throw std::runtime_error("g is invalid range: " + std::to_string(g));
        }

        if (b < 0 || 255 < b) {
            throw std::runtime_error("b is invalid range: " + std::to_string(b));
        }

        data[0] = LUT[r];//gamma_correction(r);
        data[1] = LUT[g];//gamma_correction(g);
        data[2] = LUT[b];//gamma_correction(b);

    }

    uint8_t r() {
        return data[0];
    }

    uint8_t g() {
        return data[1];
    }

    uint8_t b() {
        return data[2];
    }

/*    static uint8_t gamma_correction(int pixel){
        float color = pixel/255.0f;
        uint8_t gamma_val =  255*std::pow(color, 1/ConstParam::GAMMA_VALUE);
        return gamma_val;
    }*/

    // 代入操作の定義
    RGBPixel &operator=(const RGBPixel &src) = default;
};

bool operator==(const RGBPixel &src, const RGBPixel &dst) {
    return src.data == dst.data;
}

bool operator!=(const RGBPixel &src, const RGBPixel &dst) {
    return src.data != dst.data;
}

std::ostream &operator<<(std::ostream &stream, const RGBPixel &pixel) {
    stream << "(" << pixel.data[0] << ", " << pixel.data[1] << ", " << pixel.data[2] << ")";
    return stream;
}

static uint8_t gamma_correction(int pixel) {
    float color = pixel / 255.0f;
    uint8_t gamma_val = 255 * std::pow(color, 1 / GAMMA_VALUE);
    return gamma_val;
}

#endif //PRACTICEPATHTRACING_PIXEL_CPP