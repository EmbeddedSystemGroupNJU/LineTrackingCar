#!/bin/bash
#sudo g++ $1 -o test `pkg-config --cflags --libs opencv` -IimageProcess/*.h -LtestL/*.cpp

sudo g++ $1 -std=c++11 -o test `pkg-config --cflags --libs opencv` -IcarControl/*.h carControl/class/*.h -L. carControl/*.cpp carControl/class/*.cpp
