#include "GPIO/GPIOlib.h"
#include <iostream>

using namespace GPIO;

const int LEFT_SPEED = 10;
const int RIGHT_SPEED = 10;

void initControl() {
    init();
    controlLeft(FORWARD, LEFT_SPEED);
    controlRight(FORWARD, RIGHT_SPEED);
}

void stopCar() {
    stopLeft();
    stopRight();
}