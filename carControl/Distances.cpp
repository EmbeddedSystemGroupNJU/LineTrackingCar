//
// Created by leich on 2018/10/19.
//

#include "Distances.h"

Distances::Distances(double l, double r)
{
    this->left = l;
    this->right = r;
}

std::ostream & operator<<(std::ostream & os, const Distances & distances)
{
    os << "left distance:  " << distances.left << " right distance: " << distances.right;
    return os;
}