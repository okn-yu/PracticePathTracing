//
// Created by okn-yu on 2022/05/04.
//

#include <iostream>
#include <fstream>
#include "stb_image_write.h"

using namespace std;

int main() {
    //出力ファイル
    ofstream file("ppm_test.ppm");

    //512x512の画像を作成
    file << "P3" << endl;
    file << 512 << " " << 512 << endl;
    file << 255 << endl;
    for(int i = 0; i < 512; i++) {
        for(int j = 0; j < 512; j++) {
            int r = i/512.0 * 255;
            int g = j/512.0 * 255;
            int b = 255;
            file << r << " " << g << " " << b << endl;
        }
    }

    file.close();
    return 0;
}
