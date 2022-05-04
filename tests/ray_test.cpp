//
// Created by okn-yu on 2022/05/04.
//

#include <iostream>
#include "../src/include/ray.h"

using namespace std;

int main() {
    Ray r(Vec3(0, 0, 0), Vec3(0, 0, 1));

    cout << r << endl;
    cout << r(10) << endl;

    return 0;
}