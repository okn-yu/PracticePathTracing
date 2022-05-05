//
// Created by okn-yu on 2022/05/05.
//

#include "vec3.h"
#include "ray.h"
#include "hit.h"
#include "sphere.h"

using namespace std;

int main() {
    Sphere s(Vec3(0, 0, 0), 1);
    Ray ray(Vec3(0, 0, -3), Vec3(0, 0, 1));
    Hit res;

    if(s.intersect(ray, res)) {
        cout << res.hit_pos << endl;
    }

    return 0;
}

