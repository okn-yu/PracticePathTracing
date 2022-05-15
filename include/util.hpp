//
// Created by okn-yu on 2022/05/04.
//

#ifndef PRACTICEPATHTRACING_UTIL_H
#define PRACTICEPATHTRACING_UTIL_H

template <typename T>
T clamp(T x, T xmin, T xmax) {
    if(x < xmin) return xmin;
    else if(x > xmax) return xmax;
    else return x;
}

#endif //PRACTICEPATHTRACING_UTIL_H
