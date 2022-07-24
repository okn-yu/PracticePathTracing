/*
 * Created by okn-yu on 2022/05/04.
 */

#ifndef PRACTICEPATHTRACING_IMAGE_H
#define PRACTICEPATHTRACING_IMAGE_H

#include <memory>
#include <vector>
#include "futaba/core/pixel.h"

/*
 * ヘッダファイルでで宣言と実装を分離するとプログラムの見通しがよくなる
 * リファクタリングで実装が変わったとしても、原則的にはヘッダファイルにまで影響は及ばない
 * ただし処理速度が遅くなるというデメリットがあるらしい
 */

class Image {
public:
    int width;
    int height;
    std::vector<std::shared_ptr<RGBPixel>> pixels;

    Image(int _height, int _width);

    RGBPixel read_pixel(int x, int y) const;

    void write_pixel(int x, int y, const RGBPixel &p);

    void png_output(const std::string &filename, int comp) const;
};

#endif //PRACTICEPATHTRACING_IMAGE_H