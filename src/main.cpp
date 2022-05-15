//
// Created by okn-yu on 2022/05/06.
//

#include <iostream>
#include <pixel.hpp>

using namespace std;


int main() {
    Pixel p1 = Pixel(10, 0, 1);
    p1.getPixel();
    Pixel p2 = Pixel(3, 0, 1);
    p2.getPixel();
    Pixel p3 = Pixel(3.14, 2, 3);
    p3.getPixel();
}



