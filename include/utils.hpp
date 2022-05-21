//
// Created by okn-yu on 2022/05/19.
//

#ifndef PRACTICEPATHTRACING_UTILS_HPP
#define PRACTICEPATHTRACING_UTILS_HPP

bool is_index_safe(int index, int max_index) {

    if (index < 0 || max_index < index) {
        throw std::runtime_error("invalid index");
    } else {
        return true;
    }
}

#endif //PRACTICEPATHTRACING_UTILS_HPP