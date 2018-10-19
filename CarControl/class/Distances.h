//
// Created by leich on 2018/10/19.
//

#ifndef LINETRACKINGCAR_DISTANCES_H
#define LINETRACKINGCAR_DISTANCES_H

#include <iostream>

class Distances {
public:
    //左边线距离
    double left;
    //右边线距离
    double right;

public:
    Distances(double l = 0, double r = 0);

    friend std::ostream & operator<<(std::ostream & os, const Distances & distances);
};


#endif //LINETRACKINGCAR_DISTANCES_H
