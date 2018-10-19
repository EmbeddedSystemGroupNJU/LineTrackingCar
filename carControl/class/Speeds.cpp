//
// Created by leich on 2018/10/19.
//

#include "Speeds.h"

Speeds::Speeds(double l, double r)
{
    this->left = l;
    this->right = r;
}

std::ostream & operator<<(std::ostream & os, const Speeds & speeds)
{
    os << "left speed:  " << speeds.left << " right speed: " << speeds.right;
    return os;
}