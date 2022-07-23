/*
 * Created by okn-yu on 2022/05/05.
 * extern修飾子
 *
 */

#ifndef PRACTICEPATHTRACING_CONFIG_H
#define PRACTICEPATHTRACING_CONFIG_H

const float HIT_DISTANCE_MAX = 10000.0f;
const float HIT_DISTANCE_MIN = 0.001f;

const float GAMMA_VALUE = 1.8f;

//const int SUPER_SAMPLING = 1000;
const int SUPER_SAMPLING = 100;

const int MAX_DEPTH = 100;

//const float ROULETTE = 0.99;
const float ROULETTE = 0.9;


#endif //PRACTICEPATHTRACING_CONFIG_H
