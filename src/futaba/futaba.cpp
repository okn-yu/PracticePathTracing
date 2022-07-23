//
// Created by okn-yu on 2022/05/06.
//

#include <iostream>
#include <string>
#include "futaba/core/util.h"

using namespace std;

int main() {

    util_test();
    float n = clamp(0.0f, 10.0f, 50.0f);
    std::cout << "n is ..." << std::to_string(n) << std::endl;
    std::cout << "rnd is ..." << std::to_string(rnd()) << std::endl;
    std::cout << "futaba called!" << std::endl;

}



