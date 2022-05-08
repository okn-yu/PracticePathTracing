//
// Created by okn-yu on 2022/05/08.
//

//https://qiita.com/yumetodo/items/5886b2c0c421c24c909b
//https://www.jonki.net/entry/2016/06/15/220029
//http://opencv.jp/googletestdocs/primer.html

#include <gtest/gtest.h>
#include "pixel.h"

TEST(PixelTest, TestNoThrow) {
    EXPECT_NO_THROW(Pixel(1, 2, 3));
}
