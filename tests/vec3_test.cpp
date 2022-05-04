//
// Created by okn-yu on 2022/05/02.
//

# include <iostream>
# include "vec3.h"

using namespace std; //std::を省略する


int main(){
    Vec3 v0; //引数なしコンストラクタに（）は不要
    Vec3 v1(1, 2, 3);
    Vec3 v2(4, 5, 6);
    v2 += v1;

    cout << v0.x << endl;
    cout << v0.y << endl;
    cout << v0.z << endl;
    cout << v0.length() << endl;
    cout << v0.length2() << endl;

    cout << -v1 << endl;
    cout << v1 << endl;
    cout << v1 + v2 << endl;

    cout << v1 << endl;
    cout << v2 << endl;

    cout << dot(v1, v2) << endl;

}