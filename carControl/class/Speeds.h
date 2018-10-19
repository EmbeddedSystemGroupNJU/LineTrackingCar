//
// Created by leich on 2018/10/19.
//

#ifndef LINETRACKINGCAR_SPEEDS_H
#define LINETRACKINGCAR_SPEEDS_H

#include <iostream>

class Speeds {
public:
    //左轮速度
    double left;
    //右轮速度
    double right;

public:
    Speeds(double l = 0, double r = 0);

    friend std::ostream & operator<<(std::ostream & os, const Speeds & speeds);
};


#endif //LINETRACKINGCAR_SPEEDS_H
