//
// Created by okn-yu on 2022/07/24.
//

/*
 * 調べた結果以下の結論に達した
 * オブジェクト型のポイントを扱う場合は、生のポイントの代わりにstdのスマートポインタを用いるとよい
 * 組み込み型の配列を扱う場合は、配列の代わりにstdのvectorを用いる
 * オブジェクト型の配列を扱う場合は、stdのvectorとstdのスマートポインタを組み合わせて用いる
 * これらを用いることでポインタの開放忘れによる弊害を防ぐことができる
 * new演算子とdelete演算子を利用する必要性は基本的になく、デストラクタの実装も不要
 */

#include <memory>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"
#include "futaba/core/image.h"
#include "futaba/core/pixel.h"

Image::Image(int _height, int _width) : height(_height), width(_width) {
    for (int i = 0; i < width * height; i++) {
        pixels.push_back(std::make_shared<RGBPixel>());
    }
}


RGBPixel Image::read_pixel(int x, int y) const {
    int index = y * width + x;
    is_index_safe(index, static_cast<int>(pixels.size()));
    return static_cast<RGBPixel>(*pixels[index]);
};

void Image::write_pixel(int x, int y, const RGBPixel &p) {
    int index = y * width + x;
    is_index_safe(index, static_cast<int>(pixels.size()));
    *pixels[index] = p;
}

// comp:1=Y, 2=YA, 3=RGB, 4=RGBA.
void Image::png_output(const std::string &filename, int comp) const {

    int pixel_size = (*pixels[0]).data.size();
    assert(comp == pixel_size);

    std::vector<uint8_t> output(width * height * pixel_size);
    for (int i = 0; i < width * height; i++) {
        for (int j = 0; j < pixel_size; j++) {
            output[i * pixel_size + j] = (*pixels[i]).data[j];
        }
    }
    stbi_write_png(filename.data(), width, height, comp, output.data(), width * pixel_size);
}